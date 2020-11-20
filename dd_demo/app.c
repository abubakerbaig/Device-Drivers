#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



int main(int argc, const char *argv[])  {
    
    int fd,rd;
    char Kbuff[32];
    char Ubuff[32] = "USERdata";
    fd = open("/dev/mydev", O_RDWR);
    if(fd<0)    {
        perror("Error Opening\n");
        return fd;
    }

    rd=read(fd,Kbuff,sizeof(Kbuff));

    printf("read bytes: %d\n", rd);

    rd=write(fd, Ubuff, sizeof(Ubuff));

    printf("written bytes: %d\n", rd);
    
    close(fd);

    return 0;
}