#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

int fd;
pthread_t Reader;

void * _task_reader()
{
    
    
    while(1)
    {
        fd = open("/proc/stat", O_RDONLY);
        char c;
        int bytes;
        while((bytes = read(fd, &c, sizeof(c))) > 0) {
            write(0, &c, sizeof(char));
        }
        sleep(1);
        close(fd);
    }
}

void handler()
{
    close(fd);
    write(0, "\nProgram End\n", 13);
    pthread_cancel(Reader);
}

int main(void)
{
    signal(SIGTERM, handler);

    pthread_create(&Reader, NULL, *_task_reader, NULL);
    pthread_join(Reader, NULL);
    
    return 0;
}