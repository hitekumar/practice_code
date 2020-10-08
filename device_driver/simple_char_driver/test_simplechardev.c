#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>


#define MESSAGE_SIZE    256
#define DEVICE_FILE     "/dev/simplechardev"

#define IOCTL_READ      _IOR('a', 0, int32_t *) 
#define IOCTL_WRITE     _IOW('a', 1, int32_t *) 

static char rx_buf[MESSAGE_SIZE];
static char tx_buf[MESSAGE_SIZE];


int main(int ragc, char** argv) {
    int fd;
    int value = 98;
    memset(rx_buf,0, MESSAGE_SIZE);
    memset(tx_buf,0, MESSAGE_SIZE);
    fd = open(DEVICE_FILE, O_RDWR);
    if (fd < 0) {
        perror("Error in file open:");
        return -1;
    }
    printf("Type a short string to pass to driver\n");
    scanf("%[^\n]s", tx_buf);
    printf("Sending string \"%s\" \n", tx_buf);
    if (write(fd, tx_buf, strlen(tx_buf)) < 0 ) {
        perror("Error in write:");
        return -1;
    }

    printf("Press enter to read back from device\n");
    getchar();

    printf("Reading from device...\n");
    if (read(fd, rx_buf,MESSAGE_SIZE) < 0) {
        perror("Error in read:");
        return -1;
    }
    printf("Received message from device: %s\n", rx_buf);
    
    printf("Writing %d using ioctl\n", value);
    ioctl(fd, IOCTL_WRITE, (int32_t *) &value);

    printf("Reading value back from driver ...\n");
    ioctl(fd, IOCTL_READ, (int32_t *) &value);

    printf("Reading value %d using ioctl\n", value);


    printf("closing ....\n");
    close(fd);

    return 0;
}
