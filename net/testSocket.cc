#include <sys/types.h>  
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    listen(listenfd, 0);

    for(;;);
}