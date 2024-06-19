#ifndef TOKEN_H
#define TOKEN_H

// Tipos de token
typedef enum {
    CONST, VAR, PROCEDURE, IDENTIFIER, NUMBER, 
    PLUS, MINUS, TIMES, DIVIDE, ASSIGN, LPAREN, RPAREN,
    SEMICOLON,
    BEGIN, END, IF, THEN, WHILE, DO, CALL, ODD,
    EQ, LT, LTE, GT, GTE,
    END_OF_PROGRAM, ERROR,
} TokenType;

// Struct do token
typedef struct {
    // Tipo do token
    TokenType type;

    // Lexema do token
    char lexeme[100];
} Token;

// Struct do par token-classe
typedef struct {
    // Token
    Token token;

    // Classe associada ao token
    char classe[100];

    // Numero da linha
    int line_number;
} TokenClassPair;

TokenClassPair getNextTokenClass(FILE *file, int *pos, int *line_number);

#endif // TOKEN_H
