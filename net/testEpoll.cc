#include <thread>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sys/epoll.h>
#include <fcntl.h>

//https://blog.csdn.net/zxm342698145/article/details/80524331
const int port = 8088;

void echo(int clifd) {
    printf("into echo\n");
    char buf[1024];
    bzero(buf, sizeof(buf));
    int readcnt = 0;
    while ((readcnt = (read(clifd, buf, sizeof(buf)))) > 0) {
        write(clifd, buf, readcnt);
        bzero(buf, sizeof(buf));
    }
    printf("out echo\n");
}
// https://www.cnblogs.com/liangf27/p/9366348.html
int main() {
    printf("pid:%d\n", getpid());

    int listenfd, clientfd, readcnt, one = 1;
    char buf[1024];
    bzero(buf, 1024);

    struct sockaddr_in sock{};

    listenfd = socket(PF_INET, SOCK_STREAM, 0);

    bzero(&sock, sizeof(sock));
    sock.sin_family = PF_INET;
    sock.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.sin_port = htons(port);

    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    if (-1 == bind(listenfd, (struct sockaddr *) &sock, sizeof(struct sockaddr))) {
        perror("bind");
        exit(-1);
    }

    if (-1 == listen(listenfd, 128)) {
        perror("listen");
        exit(-1);
    }

    printf("listening on port %d.\n", port);


    int epfd;
    if (-1 == (epfd = epoll_create(1))) {
        perror("epoll_create");
        printf("errno=%d\n", errno);
        exit(-1);
    }

    epoll_event ev_ep{};
    ev_ep.events = EPOLLIN | EPOLLET;
    ev_ep.data.fd = listenfd;

    if (-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev_ep)) { // add listenfd
        perror("epoll_ctl");
        exit(-1);
    }

    int evcount = 1024;
    epoll_event events[evcount];
    for (;;) {
        int cnt;
        do {
            cnt = epoll_wait(epfd, events, evcount, -1);
        }
        while (cnt < 0 && errno == EINTR); // 处理 "Interrupted system call"

        if (cnt < 0){
            perror("epoll_wait");
            exit(-1);
        }

        for (int i = 0; i < cnt; ++i) {
            printf("into loop\n");
            /*epoll 错误*/
            if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP)
                || !(events[i].events & EPOLLIN)) {
                perror("epollevents");
                exit(-1);
            }

            if (events[i].data.fd == listenfd) { // listenfd
                printf("listenfd is readable!\n");
                if (-1 == (clientfd = accept(listenfd, nullptr, nullptr))) {
                    perror("accept");
                    exit(-1);
                }

                epoll_event ev_cli{};
                ev_cli.events = EPOLLIN | EPOLLET;
                ev_cli.data.fd = clientfd;

                int cliflag = fcntl(clientfd, F_GETFL);
                fcntl(clientfd, F_SETFL, cliflag | O_NONBLOCK);

                if (-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, clientfd, &ev_cli)) { // add listenfd
                    perror("epoll_ctl");
                    exit(-1);
                }
            }
            else {
                echo(events[i].data.fd);
            }
        }
    }
}

