#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

int main(void) {
    srand(time(NULL));
    int a = rand() % 100;
    int b = rand() % 100;
    int ans;

    printf("%d x %d = ? ", a, b);
    scanf("%d", &ans);

    if (ans == a * b) {
        int fd = open("/flag", O_RDONLY);
        if (fd >= 0) {
            char buf[256];
            int n = read(fd, buf, sizeof(buf) - 1);
            if (n > 0) write(1, buf, n);
            close(fd);
        }
    } else {
        puts("Wrong!");
    }
    return 0;
}
