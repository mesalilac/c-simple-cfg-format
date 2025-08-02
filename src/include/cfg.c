#include "cfg.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cfg_print_token(cfg_Token *token) {
    printf("type: %s", cfg_get_token_type(token->type));
    printf(" string_value: '%s'", token->string_value);
    printf(" line: %d", token->line);
    printf(" column: %d", token->column);
    printf("\n");
}

char *cfg_get_token_type(cfg_TokenType type) {
    switch (type) {
    case IDENTIFIRE:
        return "IDENTIFIRE";
    case STRING:
        return "STRING";
    case NUMBER:
        return "NUMBER";
    case BOOLEAN:
        return "BOOLEAN";
    case EQUALS:
        return "EQUALS";
    case COMMENT:
        return "COMMENT";
    case INLINE_COMMENT:
        return "INLINE_COMMENT";
    case NEWLINE:
        return "NEWLINE";
    case EOF:
        return "EOF";
    default:
        return NULL;
    }
}

cfg_Tokens *cfg_lexer(char *text) {
    cfg_Tokens *tokens = malloc(sizeof(cfg_Tokens));
    tokens->list = malloc(sizeof(cfg_Token) * 128);
    tokens->last_index = 0;

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
        case '\n': {
            line += 1;
            column = 0;
        } break;

        default:
            break;
        }

        cursor += 1;
    }

    // TODO: insert EOF Token

    return tokens;
}

cfg_ParserError *cfg_parser(cfg_Tokens *tokens_list) { return NULL; }
