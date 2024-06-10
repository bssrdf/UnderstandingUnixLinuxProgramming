#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void count_file(const char *filename, int *lines) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int ch;
    *lines =  0;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            (*lines)++;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int lines;
    count_file(argv[1], &lines);

    printf("%d %s\n", lines, argv[1]);

    return EXIT_SUCCESS;
}

