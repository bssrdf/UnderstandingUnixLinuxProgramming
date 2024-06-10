#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void count_file(const char *filename, int *lines, int *words, int *bytes) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    int ch;
    *lines = *words = *bytes = 0;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        (*bytes)++;
        if (ch == '\n') {
            (*lines)++;
        }
        if (isspace(ch)) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            (*words)++;
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int lines, words, bytes;
    count_file(argv[1], &lines, &words, &bytes);

    printf("%d %d %d %s\n", lines, words, bytes, argv[1]);

    return EXIT_SUCCESS;
}

