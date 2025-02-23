#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

void searchForTarget(char* target, FILE* file) {
    char* line = NULL;
    size_t bufsize = 0;
    ssize_t characters;
    int target_len = strlen(target);
    while ((characters = getline(&line, &bufsize, file)) != -1) {
        int found = 0; // Flag to track if the target is found
        //printf("Checking line: %s\n", line);

        for (int j = 0; j < characters; ++j) {
            if (found) break;
            int l = j; // To track line character matching target character
            for (int k = 0; k <= target_len; ++k) {
                //printf("Comparing line char: %c to target char: %c\n", line[l], target[k]);
                if (target[k] == '\0') {
                    // Print the line
                    printf("%s", line);
                    found = 1;
                } else if (line[l] != target[k]) {
                    //printf("Not equal, breaking\n");
                    break;
                }
                l++;
                if (l > characters) {
                    //printf("l exceeding characters length, breaking\n");
                    break;
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    } else if (argc == 2) {
        // Read stdin
        searchForTarget(argv[1], stdin);
    }
    char* target = argv[1];
    //printf("argv[0] is: %s\n", argv[0]);
    //printf("Our target/argv[1] is: %s\n", target);

    for (int i = 2; i < argc; ++i) {
        FILE* file = fopen(argv[i], "r");
        //printf("Opening file / argv[%d]: %s\n", i, argv[i]);
        if (file == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        searchForTarget(target, file);
    }
    return 0;
}