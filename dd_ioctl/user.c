#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include "ioctl.h"

int main (int argc, const char *argv[]) {

    int fd,rt;
    
    char Kbuff[32];
  
    fd=open("/dev/mydev1",O_RDWR);

    if(!fd) {
        perror("Error opening file.\n");
        return -1;
    }  

    ioctl(fd,CMD_1);
    ioctl(fd,CMD_2);

    rt=read(fd,Kbuff,32);
    
    printf("Number of bytes read from kernel is %d\n",rt);    
    printf("DATA READ FROM KERNEL IS \"%s\"\n", Kbuff);

    close(fd);
    return 0;
}