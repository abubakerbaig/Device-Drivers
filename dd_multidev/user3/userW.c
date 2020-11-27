#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc, const char *argv[]) {
    int fd, rt;
    
    char Ubuff[] = "FromUser";
    printf("user aplication\n");
    fd=open("/dev/mydev2",O_RDWR);

    if(fd <= 0) {
        perror("Error opening file.\n");
        return -1;
    }
    rt=write(fd,Ubuff,strlen(Ubuff));
    
    printf("Number of bytes written to kernel is %d\n",rt);
    
    printf("DATA written to KERNEL IS \"%s\"\n", Ubuff);
    close(fd);

    return 0;
}