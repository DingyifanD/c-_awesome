#include "ServerOP.h"
#include <pthread.h>
#include "RequestFactory.h"
#include "RespondFactory.h"
#include <json/json.h>	// jsoncpp的头文件
#include <fstream>
#include <unistd.h>
#include "RsaCrypto.h"
#include <fstream>
#include <string.h>
#include "Hash.h"

ServerOP::ServerOP(string jsonfile)
{
	// 加载配置文件
	// 1. 从磁盘读文件内容
	ifstream ifs(jsonfile);
	Json::Reader rd;
	Json::Value root;
	rd.parse(ifs, root);
	// 将数据从Value中取出
	m_info.dbPasswd = root["dbPasswd"].asString();
	m_info.dbSid = root["dbSID"].asString();
	m_info.dbUser = root["dbUser"].asString();
	m_info.maxNode = root["maxnode"].asInt();
	m_info.port = root["port"].asInt();
	m_info.serverID = root["serverID"].asString();
	m_info.shmKey = root["shmkey"].asString();

	// 创建共享内存对象
	m_shm = new SecKeyShm(m_info.shmKey, m_info.maxNode);
	m_shm->shmInit();

	// 连接数据库
	// dbIP:dbprot/dbinstance
	bool bl = m_occi.connectDB(m_info.dbUser, m_info.dbPasswd, m_info.dbSid);
	if (bl)
	{
		cout << "数据连接成功..." << endl;
	}
	else
	{
		cout << "数据连接失败..." << endl;
	}
}


ServerOP::~ServerOP()
{
	delete m_server;
}

void ServerOP::startServer()
{
	// 创建tcpServer对象
	m_server = new TcpServer();
	m_server->setListen(m_info.port);
	// 接收连接请求
	while (true)
	{
		TcpSocket* pSocket = m_server->acceptConn();
		if (pSocket == NULL)
		{
			cout << "accept 错误, 继续监测..." << endl;
			continue;
		}
		cout << "accept sucess" << endl;
		// 通信
		pthread_t tid;
		pthread_create(&tid, NULL, working, this);
		pthread_detach(tid);
		// 通信的套接字放到容器中
		m_socket.insert(make_pair(tid, pSocket));
	}
}

string ServerOP::seckeyArgee(RequestMsg* msg)
{
#if 0
	// 1. 将得到的公钥写入服务器磁盘
	// 写文件, 文件名: 客户端ID
	cout << "接收的公钥文件内容: " << endl;
	cout << msg->data() << endl;
	string fileaName = msg->clientid() + ".pem";
	ofstream ofs(fileaName);
	ofs << msg->data();
	// 数据刷到磁盘 flush();
	ofs.close();


	cout << "磁盘上生成了公钥文件..." << endl;
	RsaCrypto rsa(fileaName, false);
#else
	RsaCrypto rsa;
	rsa.parseKeyString(msg->data());
#endif
	// 2. 校验签名
	// 保证rsa对象中公钥是可用的
	RespondInfo info;
	Hash sha1(T_SHA1);
	sha1.addData(msg->data());
	bool bl = rsa.rsaVerify(sha1.result(), msg->sign());
	if (bl == false)
	{
		cout << "签名校验失败..." << endl;
		info.status = false;
	}
	else
	{
		info.status = true;
		cout << "签名校验成功..." << endl;
		// 3. 生成一个随机字符串-> 16/24/32byte -> 对称加密的秘钥
		string seckey = getRandStr(LenNormal);
		// 4. 回复数据 -> 结构体
		// 5. 数据初始化 -> 秘钥使用公钥加密
		info.clientID = msg->clientid();
		info.serverID = m_info.serverID;
		// 需要数据操作, 目前直接赋值即可
		info.seckeyID = 123;	// 对称加密的秘钥的ID 
		// 对称加密的秘钥, 使用公钥加密
		cout << "对称加密秘钥: " << seckey << endl;
		info.data = rsa.rsaPubKeyEncrypt(seckey);

		// 6. 生成的秘钥写入到秘钥信息表
		// clientID, serverID, keyID(秘钥编号), 创建时间, 
		// 秘钥状态(是否可用), 秘钥详细信息
		// keyID(秘钥编号) -> 读keysn表中ikeysn字段的值
		// insert into seckeyinfo(x, x,x,x,x) values()
		NodeSHMInfo shmNode;
		strcpy(shmNode.clientID, msg->clientid().data());
		strcpy(shmNode.serverID, m_info.serverID.data());
		// 需要新的密钥对, 使用公钥加密

		strcpy(shmNode.seckey, seckey.data());
		// 可用1, 不可用0, 秘钥注销之后设置为不可用
		shmNode.status = 1;	// 秘钥是否可用
		shmNode.seckeyID = m_occi.getKeyID();	// 从数据库中读
		// 将新的秘钥写入数据库
		bool bl = m_occi.writeSecKey(&shmNode);
		if(bl)
		{
			cout << "写数据库成功 -> 秘钥信息..." << endl;
			// 更新秘钥的编号
			m_occi.updataKeyID(shmNode.seckeyID + 1);
		}
		else
		{
			cout << "写数据库失败 -> 秘钥信息..." << endl;
		}

		// 7. 将对此加密的秘钥写入到共享内存中
		m_shm->shmWrite(&shmNode);
	}
	// 生成序列化对象
	CodecFactory* factory = new RespondFactory(&info);
	Codec* codec = factory->createCodec();
	// 6. 通过工厂函数创建编码对象 -> 编码
	string sendMsg = codec->encodeMsg();
	// 7. 释放资源
	delete factory;
	// delete codec;

	return sendMsg;
}

// 参数: num == 16, 24, 32
// 改成枚举
// 字符串中都有什么?
// 0-9, a-z, A-Z, 特殊字符
string ServerOP::getRandStr(KeyLen num)
{
	srand(time(NULL));	// 以当前时间为种子
	string retStr = string();
	char* buf = "~`@#$%^&*()_+=-{}[];':";
	for (int i = 0; i < num; ++i)
	{
		int flag = rand() % 4;
		switch (flag)
		{
		case 0:	// 0-9
			retStr.append(1, rand() % 10 + '0');
			break;
		case 1:	// a-z
			retStr.append(1, rand() % 26 + 'a');
			break;
		case 2:	// A-Z
			retStr.append(1, rand() % 26 + 'A');
			break;
		case 3:	// 特殊字符
			retStr.append(1, buf[rand() % strlen(buf)]);
			break;
		}
	}
	return retStr;
}

void * working(void * arg)
{
	usleep(100);
	// 得到通信的套接字
	ServerOP* op = (ServerOP*)arg;
	// 得到通信的套接字对象
	TcpSocket* pSocket = op->m_socket[pthread_self()];
	// 接收数据 -> 编码之后的
	string recvMsg = pSocket->recvMsg();
	// 对接收的数据解码
	CodecFactory* factory = new RequestFactory(recvMsg);
	Codec* codec = factory->createCodec();
	RequestMsg* reqMsg = (RequestMsg*)codec->decodeMsg();
	
	// 根据cmd判断客户端的请求
	string str;
	switch (reqMsg->cmdtype())
	{
	case 1:
		// 秘钥协商
		str = op->seckeyArgee(reqMsg);
		break;
	case 2:
		// 秘钥检验
		break;
	case 3:
		// 秘钥注销
		break;
	}
	pSocket->sendMsg(str);
	cout << "数据已经发送给了客户端..." << endl;
	pSocket->disConnect();
	// 将psocket对象从map中删除
	op->m_socket.erase(pthread_self());
	// 资源释放
	delete factory;
	delete codec;
	delete pSocket;

	return NULL;
}
