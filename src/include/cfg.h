#ifndef H_CONFIG
#define H_CONFIG

typedef enum {
    IDENTIFIRE,
    STRING,
    NUMBER,
    BOOLEAN,
    EQUALS,
    COMMENT,
    INLINE_COMMENT,
    NEWLINE,
    EOF,
} cfg_TokenType;

typedef struct {
    cfg_TokenType type;
    char *string_value;

    int line;   // +1 on newline
    int column; // reset on newline
} cfg_Token;

typedef struct {
    cfg_Token **list;
    int last_index;
} cfg_Tokens;

typedef struct {
    char *key;
    union {
        char *string;
        int number;
        int boolean;
    } value;
} cfg_KVPair;

typedef struct {
    cfg_KVPair **pairs;
    int last_index;
} cfg_KVPairs;

typedef struct {
    cfg_Token token;
    char *message;
} cfg_ParserError;

void cfg_print_token(cfg_Token *token);
char *cfg_get_token_type(cfg_TokenType type);
cfg_Tokens *cfg_lexer(char *text);
cfg_ParserError *cfg_parser(cfg_Tokens *tokens_list);

#endif // !H_CONFIG
