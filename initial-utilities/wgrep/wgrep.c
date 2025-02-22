#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    } else if (argc == 2) {
        // Read stdin
        printf("Not implemented\n");
        exit(1);
    }
    char* target = argv[1];

    for (int i = 2; i < argc; ++i) {
        FILE* file = fopen(argv[i], "r");
        if (file == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        char* line = NULL;
        size_t bufsize = 0;
        size_t characters;
        int target_len = strlen(target);
        while ((characters = getline(&line, &bufsize, file))) {
            int found = 0; // Flag to track if the target is found

            for (int j = 0; j < characters; ++j) {
                if (found) break;
                int l = j; // To track line character matching target character
                for (int k = 0; k < target_len; ++k) {
                    if (target[k] == '\0') {
                        // Print the line
                        printf("%s", line);
                        found = 1;
                    } else if (line[l] != target[k]) break;
                }
            }
        }

    }
}