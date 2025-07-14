#include "cfg.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cfg_Tokens *cfg_lexer(char *text) {
    cfg_Tokens *tokens = malloc(sizeof(cfg_Tokens));

    size_t cursor = 0;
    int line = 1;
    int column = 0;

    while (cursor != strlen(text) && text[cursor] != '\0') {
        column += 1;
        printf("char(line: %d, column: %d): %c\n", line, column, text[cursor]);

        // NEWLINE,
        // EQUALS,
        // COMMENT,
        // INLINE_COMMENT,
        // IDENTIFIRE,
        // STRING,
        // NUMBER,
        // BOOLEAN,
        // EOF,

        switch (text[cursor]) {
        case '\n':
            line += 1;
            column = 0;
            break;

        default:
            break;
        }

        cursor += 1;
    }

    // TODO: insert EOF Token

    return tokens;
}

cfg_ParserError *cfg_parser(cfg_Tokens *tokens_list) { return NULL; }
