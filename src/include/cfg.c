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
    case VALUE:
        return "VALUE";
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
            cfg_Token *token = malloc(sizeof(cfg_Token));
            token->type = NEWLINE;
            token->string_value = NULL;
            token->line = line;
            token->column = column;
            tokens->list[tokens->last_index++] = token;

            line += 1;
            column = 0;
        } break;
        case '#': {
            cursor += 1; // skip #

            if (text[cursor] == ' ') {
                cursor += 1;
            }

            char *tmp_string = malloc(sizeof(char) * 128);
            int idx = 0;
            while (cursor != strlen(text) && text[cursor] != '\0' &&
                   text[cursor] != '\n') {
                tmp_string[idx] = text[cursor];

                cursor += 1;
                idx += 1;
            }
            if (text[cursor] == '\n')
                cursor -= 1;
            tmp_string[idx] = '\0';

            cfg_Token *token = malloc(sizeof(cfg_Token));
            token->type = COMMENT;
            token->string_value = tmp_string;
            token->line = line;
            token->column = column;
            tokens->list[tokens->last_index++] = token;
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
