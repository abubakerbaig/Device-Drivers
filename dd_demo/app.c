#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char *argv[])  {
    
    int fd,rd;
    char Kbuff[32];
    char Ubuff[32] = "USER data";
    fd = open("/dev/mydev", O_RDWR);
    if(fd<0)    {
        perror("Error Opening\n");
        return fd;
    }

    rd=read(fd,Kbuff,12);

    printf("read bytes: %d\nRead data: %s\n", rd, Kbuff);

    rd=write(fd, Ubuff, sizeof(Ubuff));

    printf("written bytes: %d\n", rd);
    
    close(fd);

    return 0;
}