#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    for (int i = 1; i < argc; ++i) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wcat: cannot open file\n");
            exit(1);
        }
        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    }


    return 0;
}