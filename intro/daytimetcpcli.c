#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/errno.h>
#include <netinet/in.h>

#define MAXLINE 100

int main(int argc, char **argv)
{
    int sockfd, n;
    int rdcount = 0;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        printf("Usage: %s <ipaddr>\n", argv[0]);
        return -1;
    }

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket error: %s\n", strerror(errno));
        return -1;
    }
 
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9999);
    
    if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        printf("inet_pton error\n");
        return -1;
    }

    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        printf("connect error\n");
        return -1;
    }
    
    while((n = read(sockfd, recvline, MAXLINE)) > 0)
    { 
        recvline[n] = 0;
        rdcount++;
        fputs(recvline, stdout);
    }
    
    printf("rdcount = %d\n", rdcount);

    return 0;
}
