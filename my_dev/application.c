#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

int main()  {
    int fd;
    char Ubuff[]="This is the User buffer sending datat to KERNEL....";
    char Kbuff[100];
    
    fd=open("/dev/MycharDevice", O_RDWR, 0777);

    if(fd < 0)  {
        
        printf("\n Error Opening Device\n");
        //exit(1);
        return -1;

    }

    write(fd, Ubuff, sizeof(Ubuff));

    read(fd, Kbuff, sizeof(Kbuff));

    printf("\n the data read form the kernel is \n>>>>> %s <<<<<<", Kbuff);
    
    close(fd);
    return 0;
}