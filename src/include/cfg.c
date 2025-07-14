#include "cfg.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

cfg_Tokens *cfg_lexer(char *text) {
    cfg_Tokens *tokens = malloc(sizeof(cfg_Tokens));

    int cursor = 0;
    int line = 1;
    int column = 1;

    while (cursor != strlen(text) && text[cursor] != '\0') {
        printf("char: %c\n", text[cursor]);
        cursor += 1;
    }

    // TODO: insert EOF Token

    return tokens;
}

cfg_ParserError *cfg_parser(cfg_Tokens *tokens_list) { return NULL; }
