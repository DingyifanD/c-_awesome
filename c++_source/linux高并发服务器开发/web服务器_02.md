# 1. HTML

## 1.1 html简介

> 超文本标记语言(**H**yper **T**ext **M**arkup **L**anguage)，标准通用标记语言下的一个应用。HTML 不是一种编程语言，而是一种标记语言 (markup language)，是网页制作所必备的。
>
> 超文本就是指页面内可以包含图片、链接，甚至音乐、程序等非文字元素。
>
> 超文本标记语言的结构包括**“**头”部分（英语：Head）、和“主体”部分（英语：Body），其中“头”部提供关于网页的信息，“主体”部分提供网页的具体内容。

- html特点

  - 语法非常简洁、比较松散，以相应的英语单词关键字进行组合
  - html标签不区分大小写
  - 大多数标签是成对出现的, 有开始, 有结束
  - 不成对出现的称之为短标签

- 注释

  ```html
  <!--  我是一个html注释  -->
  <!--xxxx -->
  
  
  xml
  ```

## 1.2 文字和标题标签

```html
<!--  标题  -->
<h1></h1>
<h2></h2>
<h3></h3>
......
<h6></h6>

<!--  文字  -->
<font color="blue" size="5">hello,world</font>
属性: 
	color: 文字颜色
		□ 表示方式:
			® 英文单词: red green blue......
			® 使用16进制的形式表示颜色: #ffffff  -- (rgb)
			® 使用rgb(255, 255, 0) -> 红, 绿, 蓝
	size: 文字大小
		□  范围 1 -- 7
			® 1最小, 7最大	

<!--  文本格式  -->
加粗:
	<strong></strong> 
	<b></b> 

文本倾斜标签 
	<em></em> 
	<i></i> 

删除线标签 
	<del></del> 
	<s></s> 

下划线标签
	<ins></ins> 
	<u></u> 


<!-- 段落 -->
<p></p>

<!-- 换行 -->
<br/>  or <br>

<!-- 水平线 -->
<hr/>  or <hr>
```

## 1.3 列表标签

```html
1. 无序列表
	○ 标签
        <ul>
            <li></li>
            <li></li>
        </ul>
    ○ 属性: type
        § 实心圆圈: disc -> 默认
        § 空心圆圈: circle
        § 小方块: square

2. 有序列表
    ○ 标签
        <ol>
            <li></li>  列表项
            <li></li>
        </ol>
	○ 属性: 
        ○ type -- 序号
            □ 1 
            □ a
            □ A
            □ i 
            □ I  

3. 自定义列表
    ○ 标签
        <dl>
            <dt></dt> 
            <dd></dd> 
            <dd></dd> 
        </dl>
第一章
	1.1 序
	1.2 序1
第二章
	2.1 开始
	2.2 结束
```

## 1.4 图片标签

```html
<img src="3.gif" alt="小岳岳" title="我的天呐！" width="300" height="200" />
	○ 属性: 
		§ src: 图片的来源 必写属性
		§ alt: 替换文本 图片不显示的时候显示的文字
		§ title: 提示文本 鼠标放到图片上显示的文字
		§ width: 图片宽度
		§ height: 图片高度
	○ 注意：
		§ 图片没有定义宽高的时候，图片按照百分之百比例显示
		§ 如果只更改图片的宽度或者高度，图片等比例缩放。
```

## 1.5 超链接标签

```html
<a href="http://jd.com" title="A dog" target="_blank">超链接</a>
	○ 属性:
		○ href: 去往的路径（跳转的页面）必写属性
		○ title: 提示文本, 鼠标放到链接上显示的文字
		○ target
			□ _self:   默认值 在自身页面打开（关闭自身页面，打开链接页面）
			□ _blank: 打开新页面 （自身页面不关闭，打开一个新的链接页面）
```

## 1.6 表格标签

```html
<table>
    <tr>
        <td></td>  第一列
        <td></td>  第二列
    </tr>
    <tr>
        <td></td>
        <td></td>
    </tr>
    <tr>
        <td></td>
        <td></td>
    </tr>
</table>

属性设置:
	○ <table></table>
		§ 属性:
			□ border -- 表格线, 宽度1-7
			□ bordercolor -- 表格线颜色
			□ width
			□ height 
	○ <tr> -- 行 
		§ 属性
			□ align -- 对齐方式
				® center
				® left
				® right
	○ <td> -- 单元格(列)
		§ 对其属性设置同tr

```



# 2. HTTP协议

字符串换行使用的是: `\r\n`

## 2.1 http请求

请求消息(Request)  - 客户端(浏览器)发送给服务器的数据格式

> 四部分: 请求行, 请求头, 空行, 请求数据 
>
> - 请求行: 说明请求类型, 要访问的资源, 以及使用的http版本
>   - GET /  HTTP/1.1
>     - 请求的类型:
>       - get
>       - post
>     - 请求的资源 -> /index.html
>       - / 表示要访问服务器的资源根目录
>     - HTTP/1.1
>       - http -> 应用层协议名
>       - 1.1 -> 协议的版本号
> - 请求头: 说明服务器要使用的附加信息
>   - 由n个键值对构成的
>     - key:value
> - 空行: 空行是必须要有的, 即使没有请求数据
> - 请求数据: 也叫主体, 可以添加任意的其他数据
>   - 如果的get请求, 这部分是空的, 请求的内容在请求行的第二部分
>   - 如果是post请求, 这个位置才有数据

- Get方式提交数据

  > 第一行: 请求行
  >
  > 第2-8行: 请求头, 键值对
  >
  > 第9行: 空行
  >
  > 请求数据为空
  >
  > 提交的数据在请求行的第二部分, 这部分数据会显示在浏览器的地址栏中

  ```shell
  使用场景:
  	- 请求静态资源使用get
  		从服务器上获取一个固定的文件(部署服务器的时候就准备好的)
  			网页 xxx.html  图片  音频/视频
  		如果使用get提交数据: 提交的数据会显示在浏览器的地址栏中 -> 提交的信息不保密
  		如果get发送数据, 有可能丢失数据, 这取决于浏览器 的地址栏的缓存大小
  		
  	- 提交动态资源使用post
  		- 用户的数据信息
  			登录的用户名和密码
  			用户提交的文件(上传文件)
  ```

  

  ```http
  GET /?username=subwen%40qq.com&phone=11223344&email=11%40aa.com&date=2019-01-01&sex=male&class=3&rule=on HTTP/1.1
  Host: 192.168.36.58:6789
  Connection: keep-alive
  Upgrade-Insecure-Requests: 1
  User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.75 Safari/537.36
  Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3
  Accept-Encoding: gzip, deflate
  Accept-Language: zh,zh-CN;q=0.9,en;q=0.8
  
  第一行的第二部分: 包含了用户提交的数据, 从请求行的第二部分的?开始
  ```

- Post方式提交数据

  > 第一行: 请求行
  >
  > 第2-12行: 请求头
  >
  > 第13行: 空行
  >
  > 第14行: 用户提交的数据

  ```http
  POST / HTTP/1.1
  Host: 192.168.36.58:6789
  Connection: keep-alive
  Content-Length: 98
  Cache-Control: max-age=0
  Upgrade-Insecure-Requests: 1
  Origin: null
  Content-Type: application/x-www-form-urlencoded
  User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/73.0.3683.75 Safari/537.36
  Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3
  Accept-Encoding: gzip, deflate
  Accept-Language: zh,zh-CN;q=0.9,en;q=0.8
  
  username=subwen%40qq.com&phone=11223344&email=11%40aa.com&date=2019-01-01&sex=male&class=3&rule=on
  ```

- 请求头

  ```http
  Content-Type: 提交的数据(http请求的第四部分的数据)的格式
  Content-Length: 提交的数据(http请求的第四部分的数据)的长度
  User-Agent:带表客户端使用的浏览器的类型
  ```

  

## 2.2 http响应

响应消息(Response) -> 服务器给客户端发送的数据

> - 四部分: 状态行, 消息报头/响应头, 空行, 响应正文(服务器回复给客户端的数据)
>   - 状态行: 包括http协议版本号, 状态码, 状态信息
>     - HTTP/1.1 200 Ok
>   - 消息报头: 说明客户端要使用的一些附加信息
>     - 服务器准备好的, 要发送给客户端使用的信息
>   - 空行: 空行是必须要有的
>   - 响应正文: 服务器返回给客户端的文本信息
>
> 第一行:状态行
>
> 第2 -11行: 响应头(消息报头)
>
> 第12行: 空行
>
> 第13-18行: 服务器给客户端回复的数据

```http
HTTP/1.1 200 Ok
Server: micro_httpd
Date: Fri, 18 Jul 2014 14:34:26 GMT
/* 告诉浏览器发送的数据是什么类型 */
Content-Type: text/plain; charset=iso-8859-1 (必选项) 西欧编码->不支持中文
/* 发送的数据的长度 */
Content-Length: 32  
Location:url
Content-Language: zh-CN
Last-Modified: Fri, 18 Jul 2014 08:36:36 GMT
Connection: close

#include <stdio.h>
int main(void)
{
    printf("hello world!\n");
    return 0;
}
```

1. http状态码

   > 状态代码有三位数字组成，第一个数字定义了响应的类别，共分五种类别:
   >
   > - 1xx：指示信息--表示请求已接收，继续处理
   > - 2xx：成功--表示请求已被成功接收、理解、接受
   > - 3xx：重定向--要完成请求必须进行更进一步的操作
   > - 4xx：客户端错误--请求有语法错误或请求无法实现
   > - 5xx：服务器端错误--服务器未能实现合法的请求

   > 常见状态码：
   >
   > - 200 OK                       客户端请求成功
   > - 400 Bad Request       客户端请求有语法错误，不能被服务器所理解
   > - 401 Unauthorized     请求未经授权，这个状态代码必须和WWW-Authenticate报头域一起使用 
   > - 403 Forbidden            服务器收到请求，但是拒绝提供服务
   > - 404 Not Found           请求资源不存在，eg：输入了错误的URL
   > - 500 Internal Server Error     服务器发生不可预期的错误
   > - 503 Server Unavailable        服务器当前不能处理客户端的请求，一段时间后可能恢复正常

# 3. web服务端实现

```c
// 每个函数<100行代码 -> 每个函数的功能单一
// 使用epoll实现
// 入口函数
```

```c
// main.c
// ./a.out 8989
int main(int argc, char** argv)
{
    int port = atoi(argv[1]);
    // 启动程序
    startServer(port);
}
```

```c
// server.h
void startServer(int port);
// 初始化监听的套接字
int initListenFd(int port);
// 启动epoll
int epollRun(int lfd);
// 接受客户端连接请求
int acceptClient(int lfd, int epfd);
// 得到请求行
int getRequestLine(int connfd, char* line);
// 解析请求行
int parseRequestLine(const char* line);
// 发送响应头
int send_respond_head();
// 发送文件
int sendFile(int connfd, const char* fileName);
// 发送目录
int sendDir(int connfd, const char* fileName);
```

```c
// server.c
void startServer(int port)
{
    // 创建监听的套接字, 绑定, 监听
    int lfd = initListenFd(port);
    // 准备epoll模型
    epollRun(lfd);
}

int initListenFd(int port)
{
    int fd= socket();
    bind();
    setsockopt();	// 端口复用
    listen();
    return fd;
}

int epollRun(int lfd)
{
    int epfd = epoll_create(100);
    // 将监听的fd挂到树上
    struct epoll_event ev;
    ev.events = epollin;	// read
    ev.data.fd = lfd;
    epoll_ctl(epfd, epoll_ctl_add, lfd, &ev);
    
    // 一直检测
    while(1)
    {
        struct epoll_event events[100];
        int num = epoll_wait(epfd, events, 100, -1);
        for(int i=0; i<num; ++i)
        {
            int curfd = events[i].data.fd;
            if(发送变化的文件fd == lfd)
            {
                // 接受连接请求
                acceptClient(lfd, epfd);
            }
            // 接受客户端发来的数据
            else if(events[i].events & epollin)
            {
                // 接收数据 -> 浏览器 -> http请求
                char line[1024];
                getRequestLine(curfd, line);
                // 解析请求行
            }
        }
    }
}

int acceptClient(int lfd, int epfd)
{
    int cfd = accpet(lfd, cliaddr, len);
    // 打印客户端地址
    inet_ntop(); // -> 得到IP地址
    ntohs(); // 端口
    // 设置非阻塞
    fcntl();
    // cfd 上树
    struct epoll_event ev;
    ev.events = epollin | epollet;	// read
    ev.data.fd = lfd;
    epoll_ctl(epfd, epoll_ctl_add, lfd, &ev);
}

// 接收数据 
int getRequestLine(int connfd, char* line)
{
    // 接收数据
    int len = 0, count= 0;
    while( (len = recv(fd, buf+count, 数组剩余的字节数, 0)) > 0) // 这么写有bug
    {
        count += len;
    }
    // 数据接收完毕
    // 取出第一行 -> 
    char* p = strstr(buf, "\r\n");
    // 计算长度(请求行)
    int linelen = p - buf;
    memcpy(line, buf, linelen)
}

// GET / http/1.1
// GET /index.html HTTP/1.1
// /abc/efg/index.html
int parseRequestLine(const char* line)
{
    // 将请求行拆分为3块, 存储在3个数组中, 打印
    sscanf(line, "%[^ ] %[^ ]", method, path);
    // 判断是不是get请求
    if(strcasecmp(method, "get")==0)
    {
        // path -> /   /xxx
        // 判断用户访问的文件还是目录
        cha*file = path+1;
        struct stat st;
        int ret = stat(file, &st);
        if(ret == -1)
        {
            // 文件不存在
            // 显示404
        }
        // 是不是目录
        if(s_isdir(st.st_mode))
        {
            // 将目录的内容 -> 目录中的文件名发送给客户端(浏览器)
        }
        else if(s_isreg(st.st_mode))
        {
            // 读这个文件, 发送文件内容给浏览器
        }
        
    }
}

int send_respond_head(int connfd, int statusNO, const char* desp, const char* fileType, long fileSize)
{
    char head[1024];
    // 状态行
    sprintf(head, "http/1.1 %d %s\r\n", statusNO, desp);
    // 消息报头
    // 发送的数据格式的描述
    sprintf(head+strlen(head), "content-type: %s\r\n", fileTyep);
    // 不知道长度写-1
    sprintf(head+strlen(head), "content-length: %ld\r\n\r\n", fileSize);
    // 发送出去
    send(connfd, head, strlen(head), 0);
}

int sendFile(int connfd, const char* fileName)
{
    int fd = open(fileName, O_RDONLY);
    int len = 0;
    while( (len = read(fd, buf, size)) > 0)
    {
        // 将读的数据发送出去 -> 客户端
        send(connfd, buf, len, 0);
    }
}

int sendDir(int connfd, const char* fileName)
{
    // 要遍历这个目录 -> fileName
    /*
    	 opendir();
        readdir();
        closedir();
    */
	scandir();
}
```



# 4. 相关操作函数

- ## sscanf函数

  ```c
  // 函数原型
  // 将参数str的字符串根据参数format字符串来转换并格式化数据，转换后的结果存于对应的参数内。
  sscanf(const char *str, const char *format, ...)。
  
  具体功能如下：
  （1）根据格式从字符串中提取数据。如从字符串中取出整数、浮点数和字符串等。
  （2）取指定长度的字符串
  （3）取到指定字符为止的字符串
  （4）取仅包含指定字符集的字符串
  （5）取到指定字符集为止的字符串
  
  sscanf可以支持格式字符%[]：
  
  (1)-: 表示范围，如：%[1-9]表示只读取1-9这几个数字 %[a-z]表示只读取a-z小写字母，类似地 %[A-Z]只读取大写字母
  (2)^: 表示不取，如：%[^1]表示读取除'1'以外的所有字符 %[^/]表示除/以外的所有字符
  (3),: 范围可以用","相连接 如%[1-9,a-z]表示同时取1-9数字和a-z小写字母 
  (4)原则：从第一个在指定范围内的数字开始读取，到第一个不在范围内的数字结束%s 可以看成%[] 的一个特例 %[^ ](注意^后面有一个空格！)
  ```

  ```c
  const char *s = "http://www.baidu.com:1234";
  char protocol[32] = { 0 };
  char host[128] = { 0 };
  char port[8] = { 0 };
  sscanf(s,"%[^:]://%[^:]:%[1-9]",protocol,host,port);
  
  printf("protocol: %s\n",protocol);
  printf("host: %s\n",host);
  printf("port: %s\n",port);
  
  ///////////////
  sscanf("123456 abcdedf", "%[^ ]", buf);
  printf("%s\n", buf);
  结果为：123456
  ///////////////
  sscanf("123456abcdedfBCDEF", "%[1-9a-z]", buf);
  printf("%s\n", buf);
  结果为：123456abcdedf
  ///////////////
  sscanf("123456abcdedfBCDEF", "%[^A-Z]", buf);
  printf("%s\n", buf);
  结果为：123456abcdedf
  
  ```

  

- ## scandir函数

  ```c
  // 头文件
  #include <dirent.h> 
  //函数定义
  /*
  	函数scandir扫描dir目录下以及dir子目录下满足filter过滤模式的文件，返回的结果是compare函数经过排 
  	序的，并保存在 namelist中。注意namelist是通过malloc动态分配内存的,所以在使用时要注意释放内存。
  	alphasort和versionsort 是使用到的两种排序的函数。 
  	当函数成功执行时返回找到匹配模式文件的个数，如果失败将返回-1。
  */
  struct dirent dirs[xxx];
  struct dirent **namelist;
  int scandir(const char *dir,struct dirent ***namelist,int (*filter)(const void *b),
                    int (* compare)(const struct dirent **, const struct dirent **));
  	参数:
		- dir: 要操作的目录
  		- namelist: 传出, 函数会给这个二级指针分配内存, 指向一个字符串数组
  			["hello", "world", "你好", "shijie"]
  			namelist[i]->d_name
  		- filter: 过滤函数, 根据函数中指定的条件筛选文件名, 如果没有需求-> NULL
  		- compare: 对查找的文件名排序, 直接使用提供好的就可以了
  	返回值:
  		读到当前目录下文件的个数
  		
  int alphasort(const void *a, const void *b);
  int versionsort(const void *a, const void *b);
  ```
  
  ```html
  <!-- 浏览器显示 可以将这些文件名放到table 中 -->
  <!-- 每个文件名占一行, 第一列: 文件名, 第二列: 文件大小 -->
  跳转:
  	文件: 打开这个文件
  	目录: 显示这个目录中的内容
  <html>
      <head><title>目录名: xxxx</title></head>
      <body>
          <table>
              <tr>
                  <td><a href="xxxx.xx">文件名</a></td>
                  <td>filesize</td>
              </tr>
              <tr>
                  <td><a href="xxxx.xx/">文件名</a></td>
                  <td>filesize</td>
              </tr>
          </table>
      </body>
  </html>
  ```
  
  

# 5. 转码

> url在数据传输过程中不支持中文，需要转码。
>
> - 汉字
>
> - 特殊字符
>
> - - 查看manpage
>- - man ascii
>   - 要处理可见字符
>- - 从space开始 - 32
>     - 前0-31个不可见
>- 不需要转换的特殊字符
>   - - .
>     - _
>  - *
>     - /
>  - ~
>     - 0-9
>     - a-z
>     - A-Z
>   - 需要转换的字符使用其16进制的值前加%表示   af

中 -> utf8   %ab % ef %78