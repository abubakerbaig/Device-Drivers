#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, const char *argv[]) {

    int fd,rt;
    
    char Kbuff[32];
    char *Ubuff;

    fd=open("/dev/mydev1",O_RDWR);

    if(!fd) {
        perror("Error opening file.\n");
        return -1;
    }  
    
    Ubuff = (char*)malloc(32*sizeof(char)+1);
    if(!Ubuff)   {
        printf("failed to allocate memory.\n");
        close(fd);
        return -1;
    }

    printf("Enter String to send to the driver:\n");
    scanf(" %[^\n]s",Ubuff);

    printf("size of Ubuff: %ld\n",strlen(Ubuff));

    rt=write(fd,Ubuff,strlen(Ubuff));
    
    printf("Number of bytes written to kernel is %d\n",rt);
    
    printf("DATA written to KERNEL IS \"%s\"\n", Ubuff);

    close(fd);
    free(Ubuff);
    return 0;
}