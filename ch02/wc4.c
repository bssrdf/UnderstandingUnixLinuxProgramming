#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <immintrin.h>
#include <unistd.h>

void count_file(const char *filename, int *lines) {

    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    struct stat sb;
    if (fstat(fd, &sb) < 0) {
        perror("fstat");
        close(fd);
        return -1;
    }

    size_t filesize = sb.st_size;
    if (filesize == 0) {
        close(fd);
        return 0;
    }

    char *filedata = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, fd, 0);
    if (filedata == MAP_FAILED) {
        perror("mmap");
        close(fd);
        return -1;
    }

    int ch;
    *lines = 0;

    size_t i = 0;
    while (i < filesize) {
        (*lines) += (filedata[i++] == '\n');
    }

}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int lines;
    count_file(argv[1], &lines);

    printf("%d %d %d %s\n", lines, argv[1]);

    return EXIT_SUCCESS;
}

