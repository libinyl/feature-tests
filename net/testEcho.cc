#include <thread>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

int main() {
    int listenfd, clientfd, readcnt, one = 1;
    char buf[1024];
    bzero(buf, 1024);

    struct sockaddr_in sock{};

    listenfd = socket(PF_INET, SOCK_STREAM, 0);

    bzero(&sock, sizeof(sock));
    sock.sin_family = PF_INET;
    sock.sin_addr.s_addr = htonl(INADDR_ANY);
    sock.sin_port = htons(8088);

    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));

    if (-1 == bind(listenfd, (struct sockaddr *) &sock, sizeof(struct sockaddr))) {
        perror("bind");
        exit(-1);
    }

    if (-1 == listen(listenfd, 128)) {
        perror("listen");
        exit(-1);
    }
    if (-1 == (clientfd = accept(listenfd, nullptr, nullptr))) {
        perror("accept");
        exit(-1);
    }

    while (true) {
        while ((readcnt = read(clientfd, buf, 1024)) > 0) { // 未读完
            write(clientfd, buf, 1024);
            bzero(buf, 1024);
        }
    }
    return 0;
}
