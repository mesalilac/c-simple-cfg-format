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
    cfg_TokenType key;
    char *value;
} cfg_Token;

#endif // !H_CONFIG
