#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 100

int main(int argc, char **argv)
{
    int listenfd, connfd;
    char buff[MAXLINE];
    time_t ticks;
    struct sockaddr_in servaddr;

   if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error\n");
        return -1;
    }
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(AF_INET);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if((bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr))) < 0)
    {
        printf("bind error\n");
        return -1;
    }

   if( listen(listenfd, 100) < 0)
    {
        printf("listen error\n");
        return -1;
    }

    for(;;)
    {
        if((connfd = accept(listenfd, (struct sockaddr *)NULL, NULL)) < 0)
        {
            printf("accept error\n");
            return -1;
        }
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));

        if(write(connfd, buff, strlen(buff)) < 0)
        {
            printf("write error\n");
            return -1;
        }

        close(connfd);
    }	
}
