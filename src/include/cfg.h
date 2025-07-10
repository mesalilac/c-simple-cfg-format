#ifndef H_CONFIG
#define H_CONFIG

typedef enum {
    KEY,
    VALUE,
    COMMENT,
    EQUALS,
    QUOTATION,
    INLINE_COMMENT,
    NEW_LINE,
    EOL,
} cfg_TokenType;

typedef struct {
    cfg_TokenType key;
    char *value;
} cfg_Token;

#endif // !H_CONFIG
