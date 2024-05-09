#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    CONST, VAR, PROCEDURE, IDENTIFIER, NUMBER,
    PLUS, MINUS, TIMES, DIVIDE, ASSIGN,
    LPAREN, RPAREN, COMMA, SEMICOLON,
    BEGIN, END, IF, THEN, WHILE, DO, CALL,
    ODD, EQ, NEQ, LT, LTE, GT, GTE, // Relational operators
    END_OF_PROGRAM, ERROR
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    char lexeme[100];
} Token;

// Lexical analyzer function
Token getNextToken(char *program, int *pos) {
    Token token;
    int i = *pos;
    char c = program[i];
    memset(token.lexeme, 0, sizeof(token.lexeme));

    // Skip white spaces
    while (isspace(c)) {
        c = program[++i];
    }

    // Check for end of program
    if (c == '\0') {
        token.type = END_OF_PROGRAM;
        return token;
    }

    // Check for keywords and operators
    switch (c) {
        case ',':
            token.type = COMMA;
            token.lexeme[0] = c;
            break;
        case ';':
            token.type = SEMICOLON;
            token.lexeme[0] = c;
            break;
        case '+':
            token.type = PLUS;
            token.lexeme[0] = c;
            break;
        case '-':
            token.type = MINUS;
            token.lexeme[0] = c;
            break;
        case '*':
            token.type = TIMES;
            token.lexeme[0] = c;
            break;
        case '/':
            token.type = DIVIDE;
            token.lexeme[0] = c;
            break;
        case '(':
            token.type = LPAREN;
            token.lexeme[0] = c;
            break;
        case ')':
            token.type = RPAREN;
            token.lexeme[0] = c;
            break;
        case '=':
            token.type = ASSIGN;
            token.lexeme[0] = c;
            break;
        case '<':
            token.type = LT;
            token.lexeme[0] = c;
            if (program[i + 1] == '=') {
                token.type = LTE;
                token.lexeme[1] = program[++i];
            }
            break;
        case '>':
            token.type = GT;
            token.lexeme[0] = c;
            if (program[i + 1] == '=') {
                token.type = GTE;
                token.lexeme[1] = program[++i];
            }
            break;
        default:
            // Check for identifiers and numbers
            if (isalpha(c)) {
                int j = 0;
                while (isalnum(c)) {
                    token.lexeme[j++] = c;
                    c = program[++i];
                }
                token.type = IDENTIFIER;
            } else if (isdigit(c)) {
                int j = 0;
                while (isdigit(c)) {
                    token.lexeme[j++] = c;
                    c = program[++i];
                }
                token.type = NUMBER;
            } else {
                token.type = ERROR;
            }
    }

    *pos = i + 1; // Move to the next character
    return token;
}

// Função principal
void processProgram(char *program) {
    int pos = 0;
    Token token;

    do {
        token = getNextToken(program, &pos);

        switch (token.type) {
            case COMMA:
            case SEMICOLON:
                // Ignora vírgulas e ponto e vírgula na saída
                break;
            case ERROR:
                printf("ERROR: Invalid token\n");
                break;
            case END_OF_PROGRAM:
                printf("END OF PROGRAM\n");
                break;
            default:
                printf("%s, %s\n", token.lexeme, 
                token.type == IDENTIFIER ? "ident" : "VAR");
        }
    } while (token.type != END_OF_PROGRAM);
}

int main() {
    char program[] = "VAR a,b,c; BEGIN a:=2; b:=3 c:=@+b; END.";
    processProgram(program);
    return 0;
}
