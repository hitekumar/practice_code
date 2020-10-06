#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define MESSAGE_SIZE    256
#define DEVICE_FILE     "/dev/simplechardev"
static char rx_buf[MESSAGE_SIZE];
static char tx_buf[MESSAGE_SIZE];


int main(int ragc, char** argv) {
    int fd;
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
    printf("closing ....\n");
    close(fd);

    return 0;
}
