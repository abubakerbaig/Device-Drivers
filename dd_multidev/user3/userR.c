#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, const char *argv[]) {
    int fd, rt;
    char Kbuff[16] = "";
    
    printf("user aplication\n");
    fd=open("/dev/mydev2",O_RDWR);

    if(fd <= 0) {
        perror("Error opening file.\n");
        return -1;
    }

    rt= read(fd,Kbuff,32);
    
    printf("Number of bytes read from kernel is %d\n",rt);
    printf("DATA read from KERNEL IS \"%s\"\n", Kbuff);

    close(fd);

    return 0;
}