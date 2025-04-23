#include <stdio.h>
#define MAXLINE 1000


int main(int argc, char* argv) {
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    } else if (argc == 1) {
        char** lines = malloc(sizeof(char) * MAXLINE);

        if (lines == NULL) {
            fprintf(stderr, "Failed to allocate memory for lines\n");
            exit(1);
        }

        // Allocate the first line
        lines[0] = malloc(MAXLINE * sizeof(char));
        if (lines[0] == NULL) {
            fprintf(stderr, "Failed to allocate memory for a line\n");
            exit(1);
        }
        int len;
        int i = 0;
        while ((len = getline(lines[i], MAXLINE, stdin)) > 0) {
            ++i;
            lines[i] = malloc(MAXLINE * sizeof(char));
            if (lines[i] == NULL) {
                fprintf(stderr, "Failed to allocate memory for a line\n");
                exit(1);
            }
        }

        
    }
}