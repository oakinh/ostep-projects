#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

#define MAXLINE 1000    // Longest line we'll accept
#define START_CAP 16    // How many pointers to allocate up-front

typedef struct {
    char** lines;
    size_t count;
} SaveLinesResult;

SaveLinesResult saveLines(FILE* input) {
    if (!input) input = stdin;
    size_t cap = START_CAP;
    char** lines = malloc(cap * sizeof *lines);
    if (!lines) { perror("malloc"); exit(EXIT_FAILURE); }

    char* buffer = NULL;
    size_t n = 0;
    ssize_t len;
    size_t count = 0;

    while ((len = getline(&buffer, &n, input)) != -1) {
        if (count == cap) {
            cap *=2;
            char **tmp = realloc(lines, cap * sizeof *lines);
            if (!tmp) { perror("realloc"); exit(EXIT_FAILURE); }
            lines = tmp;
        }

        lines[count++] = buffer;
        buffer = NULL;
        n = 0;
    }
    return (SaveLinesResult){ .lines = lines, .count = count };
}

int main(int argc, char** argv) {
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    } 
    
    if (argc >= 1) {
        FILE* input;
        SaveLinesResult r;
        if (argc >= 2) {
            input = fopen(argv[1], "r");
            if (!input) {
                fprintf(stderr, "reverse: cannot open file '%s'\n", argv[1]);
                exit(EXIT_FAILURE);
            }
        } else {
            input = stdin;
        } 
        r = saveLines(input);

        if (argc >= 3) {
            if (!strcmp(argv[1], argv[2])) {
                fprintf(stderr, "reverse: input and output file must differ\n");
                exit(EXIT_FAILURE);
            }

            FILE* output = fopen(argv[2], "w");
            if (!output) {
                fprintf(stderr, "reverse: cannot open file '%s'\n", argv[2]);
                exit(EXIT_FAILURE);
            }

            for (ssize_t i = (ssize_t)r.count - 1; i >= 0; --i) {
                fprintf(output, "%s", r.lines[i]);
                free(r.lines[i]);
            }
            free(r.lines);
            fclose(output);
            return 0;
        }
        
        for (ssize_t i = (ssize_t)r.count - 1; i >= 0; --i) {
            printf("%s", r.lines[i]);
            free(r.lines[i]);
        }
        free(r.lines);
        fclose(input);
    } 
    return 0;
}