#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <immintrin.h>
#include <unistd.h>

int count_newlines_avx512(const char *filename) {
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

    close(fd);

    __m512i newline_vector = _mm512_set1_epi8('\n');
    size_t newline_count = 0;

    size_t i;
    for (i = 0; i + 64 <= filesize; i += 64) {
        __m512i data_vector = _mm512_loadu_si512((__m512i *)(filedata + i));
        __mmask64 compare_mask = _mm512_cmpeq_epi8_mask(data_vector, newline_vector);
        newline_count += _mm_popcnt_u64(compare_mask);
    }

    while (i < filesize) {
        newline_count += (filedata[i++] == '\n');
    }

    if (munmap(filedata, filesize) < 0) {
        perror("munmap");
        return -1;
    }

    return newline_count + 1;
}

int main(int argc, char *argv[]) {
    int line_count = count_newlines_avx512(argv[1]);
    printf("%d\n", line_count);
    return 0;
}


