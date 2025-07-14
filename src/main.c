#include "include/cfg.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    cfg_Tokens *tokens_list = cfg_lexer("test input");
    cfg_ParserError *error = cfg_parser(tokens_list);

    if (error != NULL) {
        printf("line: %d, column: %d: %s\n", error->token.line,
               error->token.column, error->message);
    }

    return 0;
}
