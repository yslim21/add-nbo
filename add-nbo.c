#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Error handling function
void error_exit(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

uint32_t my_ntohl(uint32_t n) {
    uint32_t n1, n2, n3, n4;
    // n : 78 56 34 12
    n1 = (n & 0xff000000) >> 24;
    n2 = (n & 0x00ff0000) >> 8;
    n3 = (n & 0x0000ff00) << 8;
    n4 = (n & 0x000000ff) << 24;

    return n1 | n2 | n3 | n4;
}

// read file
uint32_t read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        error_exit("Error opening file");
    }

    uint32_t number;
    size_t read_size = fread(&number, 1, sizeof(number), file);
    if (read_size != sizeof(number)) {
        fclose(file);
        error_exit("Error reading file or file too small");
    }

    fclose(file);

    // NBO to HBO
    uint32_t hbo_number = my_ntohl(number);

    return hbo_number;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        error_exit("Usage: add-nbo <file1> <file2>");
    }

    const char *file1 = argv[1];
    const char *file2 = argv[2];

    uint32_t num1 = read_file(file1);
    uint32_t num2 = read_file(file2);
    uint32_t sum = num1 + num2;

    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", num1, num1, num2, num2, sum, sum);

    return 0;
}





