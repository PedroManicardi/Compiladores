//"VAR a,b,c; BEGIN a:=2; b:=3 c:=@+b; END."

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Token types
typedef enum {
    CONST,
    VAR,
    PROCEDURE,
    IDENTIFIER,
    NUMBER,
    PLUS,
    MINUS,
    TIMES,
    DIVIDE,
    ASSIGN,
    LPAREN,
    RPAREN,
    SEMICOLON,
    BEGIN,
    END,
    IF,
    THEN,
    WHILE,
    DO,
    CALL,
    ODD,
    EQ,
    NEQ,
    LT,
    LTE,
    GT,
    GTE,
    END_OF_PROGRAM,
    ERROR,
    RESERVED
} TokenType;

typedef struct {
    TokenType type;
    char lexeme[100];
} Token;

typedef struct {
    Token token;
    char classe[100];
} TokenClassPair;

TokenClassPair getNextTokenClass(char *program, int *pos) {
    TokenClassPair pair;
    Token token;
    int i = *pos;
    char c = program[i];
    memset(token.lexeme, 0, sizeof(token.lexeme));

    while (isspace(c)) {
        c = program[++i];
    }

    if (c == '\0') {
        token.type = END_OF_PROGRAM;
        pair.token = token;
        strcpy(pair.classe, "END_OF_PROGRAM");
        return pair;
    }

    switch (c) {
    case ';':
        token.type = SEMICOLON;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_ponto_virgula");
        break;
    case '.':
        token.type = SEMICOLON;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_ponto");
        break;
    case '+':
        token.type = PLUS;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_mais");
        break;
    case '-':
        token.type = MINUS;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_menos");
        break;
    case '*':
        token.type = TIMES;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_vezes");
        break;
    case '/':
        token.type = DIVIDE;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_divisao");
        break;
    case '(':
        token.type = LPAREN;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_abre_parenteses");
        break;
    case ')':
        token.type = RPAREN;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_fecha_parenteses");
        break;
    case '=':
        token.type = EQ;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_igual");
        break;
    case ':':
        if (program[i + 1] == '=') {
            token.type = ASSIGN;
            token.lexeme[0] = ':';
            token.lexeme[1] = '=';
            token.lexeme[2] = '\0'; 
            strcpy(pair.classe, "simbolo_atribuicao");
            i++;
        }
        break;
    case '<':
        token.type = LT;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_menor");
        if (program[i + 1] == '=') {
            token.type = LTE;
            token.lexeme[1] = program[++i];
            strcpy(pair.classe, "simbolo_menor_igual");
        }
        break;
    case '>':
        token.type = GT;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_maior");
        if (program[i + 1] == '=') {
            token.type = GTE;
            token.lexeme[1] = program[++i];
            strcpy(pair.classe, "simbolo_maior_igual");
        }
        break;
    default:
        if (isalpha(c) && isupper(c)){
            int j = 0;
            while (isupper(c) && program[i] != '\0') { 
                token.lexeme[j++] = c;
                c = program[++i];
            }
            token.lexeme[j] = '\0'; 

            if (j > 0 && !isalpha(c)) {
                token.type = RESERVED;
                strcpy(pair.classe, token.lexeme); 
                i--;
            }
            else {
                token.type = IDENTIFIER;
                strcpy(pair.classe, "ident");
                i--;
            }
        }
        else if (isalpha(c) && islower(c)) {
            int j = 0;
            while (isalnum(c) && program[i] != '\0') {
                token.lexeme[j++] = c;
                c = program[++i];
            }
            token.type = IDENTIFIER;
            strcpy(pair.classe, "ident");
            i--;
        }
        else if (isdigit(c)) {
            int j = 0;
            while (isdigit(c) && program[i] != '\0') {
                token.lexeme[j++] = c;
                c = program[++i];
            }
            token.type = NUMBER;
            strcpy(pair.classe, "numero");
            i--;

            if (isalpha(program[i + 1])) {
                token.type = ERROR;
                strcpy(pair.classe, "<ERRO_LEXICO: numero mal formatado ou identificar invalido>");
            }
        }
        else {
            token.lexeme[0] = c;
            token.type = ERROR;
            strcpy(pair.classe, "<ERRO_LEXICO: caracter invalido>");
        }    
    }

    *pos = i + 1;
    pair.token = token;
    return pair;
}

int main() {
    char program[] = "VAR a,3b,c; BEGIN a:=2; b:=3 c:=@+b; END.";
    int pos = 0;
    TokenClassPair pair;

    do {
        pair = getNextTokenClass(program, &pos);
        printf("%s, %s\n", pair.token.lexeme, pair.classe);
    } while (pair.token.type != END_OF_PROGRAM);

    return 0;
}
