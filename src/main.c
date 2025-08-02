#include "include/cfg.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *filename = "example.config";
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL) {
        fprintf(stderr, "ERROR: Failed to open file %s", filename);
        fclose(fptr);
        exit(1);
    }

    if (fseek(fptr, 0, SEEK_END) != 0) {
        fprintf(stderr, "ERROR: Failed to seek to end of file %s", filename);
        fclose(fptr);
        exit(1);
    }

    size_t file_size = ftell(fptr);
    if (file_size == -1) {
        fprintf(stderr, "ERROR: Failed to get file size %s", filename);
        fclose(fptr);
        exit(1);
    }

    rewind(fptr);

    char *buffer = (char *)malloc(file_size + 1);
    if (buffer == NULL) {
        fprintf(stderr, "ERROR: Failed to allocate memory for file %s",
                filename);
        fclose(fptr);
        exit(1);
    }

    size_t bytes_read = fread(buffer, 1, file_size, fptr);
    if (bytes_read != file_size) {
        fprintf(stderr, "ERROR: Failed to read file %s", filename);
        free(buffer);
        fclose(fptr);
        exit(1);
    }

    buffer[file_size] = '\0';

    fclose(fptr);

    cfg_Tokens *tokens_list = cfg_lexer(buffer);
    cfg_ParserError *error = cfg_parser(tokens_list);

    if (error != NULL) {
        printf("ERROR: Parsing error at line: %d, column: %d: %s\n",
               error->token.line, error->token.column, error->message);
    }

    return 0;
}
