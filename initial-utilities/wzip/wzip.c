#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    int charCount = 0;
    int prevChar = EOF;
    
    for (int i = 1; i < argc; ++i) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wzip: cannot open file\n");
            exit(1);
        }
        int c;

        if (prevChar == EOF) {
            if ((prevChar = fgetc(file)) == EOF) {
                fclose(file);
                continue;
            }
            charCount = 1;
        }

        while((c = fgetc(file)) != EOF) {
            if (c == prevChar) {
                ++charCount;
            } else {
                fwrite(&charCount, sizeof(charCount), 1, stdout);
                char ch = (char)prevChar;
                fwrite(&ch, sizeof(ch), 1, stdout);
                prevChar = c;
                charCount = 1;
            }
        }
        fclose(file);

    }

    if (prevChar != EOF) {
        fwrite(&charCount, sizeof(charCount), 1, stdout);
        char ch = (char)prevChar;
        fwrite(&ch, sizeof(ch), 1, stdout);
    }
    return 0;
}