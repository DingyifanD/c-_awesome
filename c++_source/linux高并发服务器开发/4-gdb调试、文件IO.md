# 1. GDB调试

> gdb 是由 GNU 软件系统社区提供的调试器，同 gcc 配套组成了一套完整的开发环境，可移植性很好，支持非常多的体系结构并被移植到各种系统中（包括各种类 Unix 系统与 Windows 系统里的 MinGW 和 Cygwin ）。此外，除了 C 语言之外，gcc/gdb 还支持包括 C++、Objective-C、Ada 和 Pascal 等各种语言后端的编译和调试。 gcc/gdb 是 Linux 和许多类 Unix 系统中的标准开发环境，Linux 内核也是专门针对 gcc 进行编码的。
>
> gdb 的吉祥物是专门捕杀 bug 的射手鱼:

![](assets/GNU_Debugger.png)

> *For a fish, the archer fish is known to shoot down bugs from low hanging plants by spitting water at them.*

## 1.1 调试准备

> 通常，在为调试而编译时，我们会(在尽量不影响程序行为的情况下)关掉编译器的优化选项(`-O`)， 并打开调试选项(`-g`)。另外，`-Wall`选项打开所有 warning，也可以发现许多问题，避免一些不必要的 bug:

```shell
$ gcc -g -Wall program.c -o program
```

> `-g`选项的作用是在可执行文件中加入源代码的信息，比如可执行文件中第几条机器指令对应源代码的第几行，但并不是把整个源文件嵌入到可执行文件中，所以在调试时必须保证gdb能找到源文件。

## 1.2 gdb调试命令

- gdb启动和退出

  ```shell
  # 启动, shell命令
  gdb 可执行程序
  # 给程序传递参数
  (gdb) set args 10 9
  (gdb) show args
  Argument list to give program being debugged when it is started is "10 9".
  # 退出gdb
  (gdb) quit
  ```

- 查看代码
  - 当前文件
  
    ```shell
    # 从默认位置显示代码
    (gdb) l
    (gdb) list
    # 从指定的行显示
    (gdb) l 行号
    # 从指定的函数开始显示
    (gdb) l 函数名
    ```
  
  - 非当前文件
  
    ```shell
    # 指定文件的指定的行
    (gdb) l 文件名:行号
    # 指定文件的指定的函数
    (gdb) l 文件名:函数名
    ```
  
  - 设置显示的行数
  
    ```shell
    # 查看默认显示的行数
    # list == listsize
    (gdb) show list
    Number of source lines gdb will list by default is 10.
    (gdb) show listsize
    Number of source lines gdb will list by default is 10.
    # 更改显示的函数
    (gdb) set list 行数
    (gdb) set listsize 行数
    ```
  
- 断点操作
  - 设置断点
  
    ```shell
    # 命令: break == b
    # 在当前文件设置断点
    (gdb) b 行号
    Breakpoint 1 at 0x400c23: file test.cpp, line 13.
    # b 函数名
    (gdb) b main
    Breakpoint 2 at 0x400bb8: file test.cpp, line 10.
    # 在非当前文件设置断点
    # b 文件名:行号
    (gdb) b insert.cpp:15
    Breakpoint 3 at 0x400991: file insert.cpp, line 15
    # b 文件名:函数名
    (gdb) b insert.cpp:insertionSort
    Breakpoint 4 at 0x400951: file insert.cpp, line 7.
    ```
  
  - 查看断点
  
    ```shell
    # i == info
    (gdb) i b
    Num     Type           Disp Enb Address            What
    1       breakpoint     keep y   0x0000000000400c23 in main() at test.cpp:13
    2       breakpoint     keep y   0x0000000000400bb8 in main() at test.cpp:10
    3       breakpoint     keep y   0x0000000000400991 in insertionSort(int*, int) at insert.cpp:15
    4       breakpoint     keep y   0x0000000000400951 in insertionSort(int*, int) at insert.cpp:7
    ```
  
  - 删除断点
  
    ```shell
    # d = del = delete
    # d 断点的编号 Num
    (gdb) d 4
    ```
  
  - 设置断点无效
  
    ```shell
    # dis == disable
    # dis 断点编号
    (gdb) dis 1
    (gdb) i b
    Num     Type           Disp Enb Address            What
    1       breakpoint     keep n   0x0000000000400c23 in main() at test.cpp:13
    2       breakpoint     keep y   0x0000000000400bb8 in main() at test.cpp:10
    3       breakpoint     keep y   0x0000000000400991 in insertionSort(int*, int) at insert.cpp:15
    ```
  
  - 无效断点生效
  
    ```shell
    # ena == enable
    # ena 断点的编号
    (gdb) ena 2
    (gdb) i b
    Num     Type           Disp Enb Address            What
    1       breakpoint     keep n   0x0000000000400c23 in main() at test.cpp:13
    2       breakpoint     keep y   0x0000000000400bb8 in main() at test.cpp:10
    3       breakpoint     keep y   0x0000000000400991 in insertionSort(int*, int) at insert.cpp:15
    ```
  
  - 设置条件断点
  
    ```shell
    # 一般用在循环的位置
    # b 行号 if 变量==某个值
    (gdb) b 18 if i==6    
    Breakpoint 5 at 0x400c52: file test.cpp, line 18.
    ```
  
- 调试命令
  - 运行gdb程序
  
    ```shell
    # 通过start, 只运一行, 就停止了
    (gdb) start
    # 通过run, 一直运行, 直到遇到了断点
    (gdb) run
    ```
  
  - 从断点的位置继续运行, 停到下一个断点的位置
  
    ```shell
    # c = continue
    (gdb) c
    ```
  
  - 打印变量
  
    ```shell
    # p == print 变量名
    (gdb) print i
    $1 = 6
    # 进制转换: p/x p/o 
    (gdb) print/x i
    $1 = 0x6
    ```
  
    
  
  - 打印变量类型
  
    ```shell
    # ptype 变量名
    (gdb) ptype array
    type = int [12]
    ```
  
  - 向下单步调试
    - 进入函数体
    
      ```shell
      # s == step向下执行一行, 遇到函数, 进入函数体内部
      (gdb) s
      ```
    
      
    
    - 跳出函数体
    
      ```shell
      # 要跳出的函数中不能有断点, 如果有要删除或者设置为无效的断点
      (gdb) finish
      ```
    
      
    
    - 不进入函数体
    
      ```shell
      # next == n 向下执行一行, 遇到函数, 不进入函数体内部
      (gdb) n
      ```
    
  - 变量自动显示
  
    ```shell
    # 自动打印指定变量的值
    # display 变量名
    (gdb) display num
    
    # 查看自动打印哪些变量的值
    # i == info
    (gdb) i display
    Auto-display expressions now in effect:
    Num Enb Expression
    1:   y  i
    
    # 取消自动跟踪打印
    # undisplay 编号(通过 i display 可以查看)
    (gdb) undisplay 1
    ```
  
  - 设置变量等于某一个值
  
    ```shell
    # 一般在循环中用的比较多
    # set var 变量名=变量值
    (gdb) set var i=9
    ```
  
    
  
  - 跳出循环
  
    ```shell
    # until
    # 要跳出的循环代码块中不能有断点, 如果有要删除或者设置为无效的断点
    # 执行完循环体的最后一行 == 循环的开始位置 才能跳出
    ```
  
    

# 2. 文件IO

## 2.1 Linux系统IO和C标准库IO

- 标准C库IO函数

  ![1557069755830](assets/1557069755830.png)

  ```c
  fopen -> open
  // linux c FILE结构体定义： /usr/include/libio.h
  
  struct _IO_FILE {
    int _flags;		/* High-order word is _IO_MAGIC; rest is flags. */
  #define _IO_file_flags _flags
   
    /* The following pointers correspond to the C++ streambuf protocol. */
    /* Note:  Tk uses the _IO_read_ptr and _IO_read_end fields directly. */
    char* _IO_read_ptr;	/* Current read pointer */
    char* _IO_read_end;	/* End of get area. */
    char* _IO_read_base;	/* Start of putback+get area. */
    char* _IO_write_base;	/* Start of put area. */
    char* _IO_write_ptr;	/* Current put pointer. */
    char* _IO_write_end;	/* End of put area. */
    char* _IO_buf_base;	/* Start of reserve area. */
    char* _IO_buf_end;	/* End of reserve area. */
    /* The following fields are used to support backing up and undo. */
    char *_IO_save_base; /* Pointer to start of non-current get area. */
    char *_IO_backup_base;  /* Pointer to first valid character of backup area */
    char *_IO_save_end; /* Pointer to end of non-current get area. */
   
    struct _IO_marker *_markers;
   
    struct _IO_FILE *_chain;
   
    int _fileno;
  #if 0
    int _blksize;
  #else
    int _flags2;
  #endif
    _IO_off_t _old_offset; /* This used to be _offset but it's too small.  */
   
  #define __HAVE_COLUMN /* temporary */
    /* 1+column number of pbase(); 0 is unknown. */
    unsigned short _cur_column;
    signed char _vtable_offset;
    char _shortbuf[1];
   
    /*  char* _save_gptr;  char* _save_egptr; */
   
    _IO_lock_t *_lock;
  #ifdef _IO_USE_OLD_IO_FILE
  };
  
  // 在文件: /usr/include/stdio.h
  typedef struct _IO_FILE FILE;
  ```

- 标准C 库IO和 Linux系统IO的关系

  ![](assets/未命名图片.png)

## 2.2 虚拟地址空间

![1557071719103](assets/1557071719103.png)

![1557071976192](assets/1557071976192.png)

```shell
# 文件描述符表默认大小: 1024
# 每个进程启动之后, 都有一个文件描述符表
# 所以每个进程默认能打开的文件个数: 1024
# 前三个文件文件描述符是默认被使用了的:
# 	- 标准输入 -> 0, 标准输出 -> 1, 标准错误 -> 2

# 文件描述符如果被占用, 需要使用其他没有被占用的(选最小的), 
```

## 2.3 Linux系统IO函数

```shell
# errno -> 属于Linux系统函数库, 库里边的一个全局变量, 记录的是错误号
#include <stdio.h>
# perror打印的是errno对应的错误描述
void perror(const char *s);
	- s参数: 用户描述, 比如:hello
# 实际输出: hello: xxxxx(实际的错误描述)

```

- open/close

  ```c
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <fcntl.h>
  // open函数
  // 打开一个已经存在文件
  int open(const char *pathname, int flags);
  	参数:
          - pathname: 要打开的文件路径
          - flags: 对文件的操作权限设置
              - O_RDONLY,  O_WRONLY,  O_RDWR 这三个设置是互斥的
       返回值: 
  // 使用open创建一个新文件
  int open(const char *pathname, int flags, mode_t mode);
  	参数: 
  		- pathname: 要打开的文件路径
          - flags: 对文件的操作权限设置
              - 必选项: O_RDONLY,  O_WRONLY,  O_RDWR 这三个设置是互斥的
              - 可选项: O_CREAT -> 文件不存在, 创建新文件
          - mode: 八进制的数, 表示用户对创建出的新文件的操作权限, 比如: 0775, mode & ~umask
          		0777	-> 111111111
          		0775    -> 111111101
          	&	
                  0775       111111101
         按位与: 0和任何数都为0                    
  
  // close函数
  #include <unistd.h>
  int close(int fd);
  ```

- read

  ```c
  #include <unistd.h>
  ssize_t read(int fd, void *buf, size_t count);
  	参数: 
  		- fd: open得到的, 通过这个fd操作某一个文件
  		- buf: 缓冲区, 存储读到的数据, 数组的地址
  		- count: buf的大小
  	返回值: 
  		- 成功: 
  			>0: 返回实际读到的字节数
  			==0: 文件已经读完了
  		- 失败: -1
  ```

  

- write

  ```c
  #include <unistd.h>
  
  ssize_t write(int fd, const void *buf, size_t count);
  	参数: 
  		- fd: open得到的, 通过这个fd操作某一个文件
  		- buf: 要往磁盘写入的数据
  		- count: 要写的数据的实际大小
  	返回值:
  		成功: 实际写入的字节数
  		失败: -1
              
   # 写个程序: 有一个1M的文件, 通过循环的方式读文件, 读出一部分写入另外一个文件中
  ```

  

- lseek

  ```c
  // fseek
  #include <sys/types.h>
  #include <unistd.h>
  
  off_t lseek(int fd, off_t offset, int whence);
  	参数: 
  		- fd: open得到的, 通过这个fd操作某一个文件
  		- offset: 偏移量
  		- whence: 
  			SEEK_SET
                设置文件指针的偏移量
         		SEEK_CUR
                设置偏移量: 当前位置 + 第二个参数的值
         		SEEK_END
                设置偏移量: 文件大小 + 第二个参数的值
  int fseek(FILE *stream, long offset, int whence);
  
  
  // 1. 移动文件指针到文件头
  lseek(fd, 0, SEEK_SET);
  // 2. 获取当前文件指针的位置
  lseek(fd, 0, SEEK_CUR);
  // 3. 获取文件长度
  lseek(fd, 0, SEEK_END);
  // 4. 拓展问长度, 当前文件10b, 110b, 增加的字节的0
  lseek(fd, 100, SEEK_END);
  // 要进行一次写操作
  write(fd, " ", 1);
  ```

  

# 3. Linux其他系统函数

- stat/lstat函数

  ```c
  struct stat {
      dev_t          st_dev;        	//文件的设备编号
      ino_t           st_ino;        	//节点
      mode_t      st_mode;      		//文件的类型和存取的权限
      nlink_t        st_nlink;     	//连到该文件的硬连接数目，刚建立的文件值为1
      uid_t           st_uid;       	//用户ID
      gid_t           st_gid;       	//组ID
      dev_t          st_rdev;      	//(设备类型)若此文件为设备文件，则为其设备编号
      off_t            st_size;      	//文件字节数(文件大小)
      blksize_t     st_blksize;   	//块大小(文件系统的I/O 缓冲区大小)
      blkcnt_t      st_blocks;    	//块数
      time_t         st_atime;     	//最后一次访问时间
      time_t         st_mtime;     	//最后一次修改时间
      time_t         st_ctime;     	//最后一次改变时间(指属性)
  };
  关于变量 st_mode: 
  	- st_mode -- 16位整数
  		○ 0-2 bit -- 其他人权限
  			- S_IROTH    00004  读权限
  			- S_IWOTH    00002  写权限
  			- S_IXOTH    00001  执行权限
  			- S_IRWXO    00007  掩码, 过滤 st_mode中除其他人权限以外的信息
  		○ 3-5 bit -- 所属组权限
  			- S_IRGRP    00040  读权限
  			- S_IWGRP    00020  写权限
  			- S_IXGRP    00010  执行权限
  			- S_IRWXG    00070  掩码, 过滤 st_mode中除所属组权限以外的信息
  		○ 6-8 bit -- 文件所有者权限
  			- S_IRUSR    00400    读权限
  			- S_IWUSR    00200    写权限
  			- S_IXUSR    00100    执行权限
  			- S_IRWXU    00700    掩码, 过滤 st_mode中除文件所有者权限以外的信息
  		○ 12-15 bit -- 文件类型
  			- S_IFSOCK   0140000 套接字
  			- S_IFLNK    0120000 符号链接（软链接）
  			- S_IFREG    0100000 普通文件
  			- S_IFBLK    0060000 块设备
  			- S_IFDIR    0040000 目录
  			- S_IFCHR    0020000 字符设备
  			- S_IFIFO    0010000 管道
  			- S_IFMT     0170000 掩码,过滤 st_mode中除文件类型以外的信息
  		(st_mode & S_IFMT) ==  S_IFREG
  
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <unistd.h>
  int stat(const char *pathname, struct stat *buf);
  	参数: 
  		- pathname: 操作的文件的路径
  		- buf: 结构体变量, 传出
  struct stat st;
  stat("hello.txt", &st); 
  ```

  ![1557076082566](assets/1557076082566.png)

- 文件属性函数

  ```c
  int access(const char *pathname, int mode);
  int chmod(const char *filename, int mode);
  int chown(const char *path, uid_t owner, gid_t group);
  int truncate(const char *path, off_t length);
  ```

- 目录操作函数

  ```c
  int rename(const char *oldpath, const char *newpath);
  int chdir(const char *path);
  char *getcwd(char *buf, size_t size);
  int mkdir(const char *pathname, mode_t mode);
  int rmdir(const char *pathname);
  ```

- 目录遍历函数

  ```c
  DIR *opendir(const char *name);
  	参数: 
  		- name: 要打开的目录
  	返回值: DIR * 
  struct dirent
  {
      ino_t d_ino;               // 此目录进入点的inode
      ff_t d_off;                // 目录文件开头至此目录进入点的位移
      signed short int d_reclen; // d_name 的长度, 不包含NULL 字符
      unsigned char d_type;      // d_name 所指的文件类型 
      har d_name[256];	       // 文件名
  };
  d_type
  	DT_BLK 	- 块设备
  	DT_CHR 	- 字符设备
  	DT_DIR 	- 目录
  	DT_LNK 	- 软连接
  	DT_FIFO - 管道
  	DT_REG 	- 普通文件
  	DT_SOCK - 套接字
  	DT_UNKNOWN - 未知
  struct dirent *readdir(DIR *dirp);
  	- 返回一个结构体, 这个对应一个文件
  int closedir(DIR *dirp);
  ```

  ```c
  // 读某个目录下普通文件的个数
  // 需要用到递归, 想明白递归结束的条件
  #include <stdio.h>
  #include <string.h>
  #include <sys/types.h>
  #include <dirent.h>
  
  int getFileNum(const char* path);
  
  int main(int argc, char* argv[])
  {
      int num = getFileNum(argv[1]);
      printf("file num: %d\n", num);
      return 0;
  }
  
  // 读指定目录下文件个数
  int getFileNum(const char* path)
  {
      // 打开指定目录
      DIR* dir = opendir(path);
      if(dir == NULL)
      {
          perror("opendir");
          return -1;
      }
  
      int total = 0;
      // 读打开的目录
      struct dirent* ptr = NULL;
      while( (ptr = readdir(dir)) != NULL )
      {
          // 如果是目录, 需要递归读子目录, 跳过. 和.. 目录
          if(strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0)
          {
              continue;
          }
          // 是一个普通文件
          if(ptr->d_type == DT_REG)
          {
              // 文件个数+1
              total ++;
          }
          // 是一个目录
          if(ptr->d_type == DT_DIR)
          {
              // 进去, 打开目录
              char newpath[1024];
              sprintf(newpath, "%s/%s", path, ptr->d_name);
              total += getFileNum(newpath);
          }
      }
      closedir(dir);
      return total;
  }
  ```

  