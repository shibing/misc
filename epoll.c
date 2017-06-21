#include <sys/types.h>
#define __USE_GNU
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

int create_server(const char *ip, int port)
{
    int lfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    int option = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR,
                    (const void *)&option , sizeof(int));
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    inet_aton(ip, &addr.sin_addr);
    addr.sin_port = htons(port);
    bind(lfd, (struct sockaddr *)&addr, sizeof(addr));
    listen(lfd, 50);
    return lfd;
}

int main(int argc, char *argv[])
{
    int server_fd = create_server("127.0.0.1", atoi(argv[1]));

    int efd = epoll_create(128);

    struct epoll_event e;
    e.events = EPOLLIN;
    e.data.fd = server_fd;
    epoll_ctl(efd, EPOLL_CTL_ADD, server_fd, &e);

    struct epoll_event events[128];

    for ( ;; ) {

        int n = epoll_wait(efd, events, 128, -1);

        if (n == -1) {
            perror("epoll_wait failed");
            close(server_fd);
            close(efd);
            return 1;
        }

        for (int  i = 0; i < n; ++i) {
            int revents = events[i].events;
            int fd = events[i].data.fd;

            if (revents & EPOLLIN) {
                if (fd == server_fd) {
                    struct sockaddr_in addr;
                    int addrlen;
                    int cfd = accept4(server_fd, (struct sockaddr *)&addr, &addrlen, SOCK_NONBLOCK);
                    struct epoll_event e ;
                    e.data.fd = cfd;
                    e.events = EPOLLIN | EPOLLET | EPOLLRDHUP;
                    epoll_ctl(efd, EPOLL_CTL_ADD, cfd, &e);
                } else {
                    if (revents & EPOLLRDHUP) {
                        printf("client :%d closed", fd);
                        close(fd);
                        continue;
                    }
                }
            }

            if (revents & EPOLLOUT) {

            }
        }
    }
}
