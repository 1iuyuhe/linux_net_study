# Linux中网络I/O复用并发模型
## 什么是epoll
- 与select, poll一样，对I/O多路复用的技术
- 只关心“活跃”的连接，无需遍历全部描述符集合
- 能够处理大量的连接请求（系统可以打开的文件数目）

## epoll API

1、创建epoll
```c
/**
 * @param size 告诉内核监听的数目
 *
 * @returns 返回一个epoll句柄（即一个文件描述符）
 */
int epoll_create(int size);
```

2、控制epoll
```c
/**
 * @param epfd 用epoll_create所创建的epoll句柄
 * @param op 表示对epoll监控描述符控制的动作
 *          EPOLL_CTL_ADD(注册新的fd到epfd)
 *          EPOLL_CTL_MOD(修改已经注册的fd监听事件)
 *          EPOLL_CTL_DEL(epfd删除一个fd)
 *
 * @param fd 需要监听的文件描述符
 * @param event 告诉内核需要监听的事件
 *
 * @returns 成功返回0，失败返回-1,errno查看错误信息
 */
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
```

3、等待epoll
```c
/**
 * @param epfd 用epoll_create所创建的
 * @param event 从内核得到的事件集合
 * @param maxevents 告知内核这个events有多大
 * @param timeout 超时时间
 *                -1: 永久阻塞
 *                 0: 立即返回，非阻塞
 *                >0: 制定微秒
 *
 * @returns 成功: 有多少文件描述符就绪，时间到时返回0
 *          失败: -1, errno 查看错误 
 */
int epoll_wait(int epfd, struct epoll_event *event, int maxevents, int timeout);
```

## epoll 编程架构

```c
// 创建epoll
int epfd = epoll_create(1000);
// 将listen_fd 添加进epoll中
epoll_ctl(epfd, EPOLL_CTL_ADD, listen_fd, &listen_event);
while (1) {
    // 阻塞等待epoll中的fd触发
    int active_cnt = epoll_wait(epfd, events, 1000, -1);
    for (int i = 0; i < active_cnt; i++) {
        if (events[i].data.fd == listen_fd) {
            // accept, 并且将新accept的fd加入epoll中
        } else if (events[i].events & EPOLLIN) {
            // 对此fd进行读操作
        } else if (events[i].events & EPOLLOUT) {
            // 对此fd进行写操作
        }
    }
}
```
## epoll触发模式

### 水平触发（Level Triggered） LT

水平触发的主要特点是，如果用户在监听epoll事件，当内核有事件的时候，会拷贝给用户态事件，但是如果用户只处理了一次，那么剩下没有处理的会在下一次epoll_wait再次返回该事件

默认情况下是水平触发

### 边缘触发（Edge Triggered）  ET

边缘触发的主要特点是，当内核有事件到达，只会通知用户一次，至于用户处理还是不处理，以后将不会再通知。这样就减少了拷贝过程，增加了性能，但是相对来说，如果用户马虎忘记处理，将会产生事件丢失的情况

## 常见多路I/O复用并发模型

模型一：单线程Accept（无IO复用）


模型二：单线程Accept+多线程读写业务（无IO复用）


模型三：单线程多路IO复用


模型四：单线程多路IO复用+多线程读写业务（业务工作池）


模型五：单线程多路IO复用+多线程IO复用（线程池）


模型六：单进程多路IO复用+多进程多路IO复用（进程池）


模型七：单线程多路IO复用+多线程多路IO复用+多线程