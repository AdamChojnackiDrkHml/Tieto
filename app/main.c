#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

static int fd;
static pthread_t Reader;

static void*  _task_reader(void *arg);
static void*  _task_reader(void *arg)
{
    char* parameter = (char*)arg;
    write(0, "Reader started with paramter ", 29);
    write(0, parameter, 1);
    write(0, "\n", 1);
    
    while(1)
    {
        fd = open("/proc/stat", O_RDONLY);
        char c;
        long bytes;
        while((bytes = read(fd, &c, sizeof(c))) > 0) {
            write(0, &c, sizeof(char));
        }
        sleep(1);
        close(fd);
    }
}

static void handler(int n)
{
    n += 0x30;
    close(fd);
    write(0, "\nProgram End\n", 13);
    write(0, &n, 1);
    pthread_cancel(Reader);
}

int main(void)
{
    signal(SIGTERM, *handler);

    pthread_create(&Reader, NULL, &_task_reader, NULL);
    pthread_join(Reader, NULL);
    
    return 0;
}
