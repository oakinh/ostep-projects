#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("wzip: [files...]\n");
        exit(1);
    }
    for (int i = 1; i < argc; ++i) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
    }
}