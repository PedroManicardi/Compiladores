#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
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

int pertence(char c) {
    char caracteres_especiais[] = {'!', '"', '#', '$', '%', '&', '\'', '?', '@', '[', '\\', ']', '^', '_', '`', '|', '~'};
    for (int i = 0; i < sizeof(caracteres_especiais) / sizeof(caracteres_especiais[0]); i++) {
        if (caracteres_especiais[i] == c) {
            return 1; // Retorna verdadeiro se o caractere estiver no vetor
        }
    }
    return 0; 
}

TokenClassPair getNextTokenClass(FILE *file, int *pos) {
    TokenClassPair pair;
    Token token;
    int i = *pos;
    char c = fgetc(file);
    memset(token.lexeme, 0, sizeof(token.lexeme));
    bool e = false;
    

    // Ignora espaços em branco, vírgulas e comentários
    while (isspace(c) || c == ',' || c == '{') {
        if (c == '{') { // Se encontrar um '{', ignora até encontrar um '}'
            while (c != '}' && c != EOF) {
                c = fgetc(file);
            }
        }
        c = fgetc(file);
    }

    if (c == EOF) {
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
        if (fgetc(file) == '=') {
            token.type = ASSIGN;
            token.lexeme[0] = ':';
            token.lexeme[1] = '=';
            token.lexeme[2] = '\0'; 
            strcpy(pair.classe, "simbolo_atribuicao");
        }
        else {
            fseek(file, -1, SEEK_CUR); // Volta o caractere lido para o arquivo
        }
        break;
    case '<':
        token.type = LT;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_menor");
        if (fgetc(file) == '=') {
            token.type = LTE;
            token.lexeme[1] = fgetc(file);
            strcpy(pair.classe, "simbolo_menor_igual");
        }
        else {
            fseek(file, -1, SEEK_CUR); // Volta o caractere lido para o arquivo
        }
        break;
    case '>':
        token.type = GT;
        token.lexeme[0] = c;
        strcpy(pair.classe, "simbolo_maior");
        if (fgetc(file) == '=') {
            token.type = GTE;
            token.lexeme[1] = fgetc(file);
            strcpy(pair.classe, "simbolo_maior_igual");
        }
        else {
            fseek(file, -1, SEEK_CUR); // Volta o caractere lido para o arquivo
        }
        break;


    default:
        if (isalpha(c)) {
            int j = 0;
            while ((isalnum(c) || pertence(c)) && c != EOF) {
                token.lexeme[j++] = c;
                c = fgetc(file);

                if (pertence(c)) {
                    e = true;
                    strcpy(pair.classe, "Erro");
                }
            }
            token.lexeme[j] = '\0'; 

            if (strcmp(token.lexeme, "VAR") == 0) {
                token.type = VAR;
                strcpy(pair.classe, "VAR");
            }
            else if (strcmp(token.lexeme, "BEGIN") == 0) {
                token.type = BEGIN;
                strcpy(pair.classe, "BEGIN");
            }
            else if (strcmp(token.lexeme, "END") == 0) {
                token.type = END;
                strcpy(pair.classe, "END");
            }
            else if (strcmp(token.lexeme, "CALL") == 0) {
                token.type = CALL;
                strcpy(pair.classe, "CALL");
            }
            else if (strcmp(token.lexeme, "PROCEDURE") == 0) {
                token.type = PROCEDURE;
                strcpy(pair.classe, "PROCEDURE");
            }
            else if (strcmp(token.lexeme, "CONST") == 0) {
                token.type = CONST;
                strcpy(pair.classe, "CONST");
            }
            else if (strcmp(token.lexeme, "IF") == 0) {
                token.type = IF;
                strcpy(pair.classe, "IF");
            }
            else if (strcmp(token.lexeme, "THEN") == 0) {
                token.type = THEN;
                strcpy(pair.classe, "THEN");
            }
            else if (strcmp(token.lexeme, "WHILE") == 0) {
                token.type = WHILE;
                strcpy(pair.classe, "WHILE");
            }
            else if (strcmp(token.lexeme, "DO") == 0) {
                token.type = DO;
                strcpy(pair.classe, "DO");
            }
            else if (strcmp(token.lexeme, "ODD") == 0) {
                token.type = ODD;
                strcpy(pair.classe, "ODD");
            }
            else {
                if (e) {
                    token.type = ERROR;
                    strcpy(pair.classe, "<ERRO_LEXICO: numero mal formatado ou identificador invalido>");
                } else {
                    token.type = IDENTIFIER;
                    strcpy(pair.classe, "ident");
                }
            }

            if (!isalpha(c) && !isdigit(c)) {
                fseek(file, -1, SEEK_CUR); // Volta o caractere lido para o arquivo
            }
        }
        else if (isdigit(c)) {
            int j = 0;
            while ((isalnum(c) || pertence(c)) && c != EOF) {
                token.lexeme[j++] = c;
                c = fgetc(file);

                if (isalpha(c)) {
                    e = true;
                }

                if(pertence(c)) {
                    e = true;
                }
            }
            token.lexeme[j] = '\0'; 
            if (e == true) {
                token.type = ERROR;
                strcpy(pair.classe, "<ERRO_LEXICO: numero mal formatado ou identificador invalido>");
            }
            else {
                token.type = NUMBER;
                strcpy(pair.classe, "numero");
                fseek(file, -1, SEEK_CUR);
            }
            
        }
        else {
            token.lexeme[0] = c;
            token.type = ERROR;
            strcpy(pair.classe, "<ERRO_LEXICO: caracter invalido>");
        }
    }

    *pos = ftell(file);
    pair.token = token;
    return pair;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    int pos = 0;
    TokenClassPair pair;

    do {
        pair = getNextTokenClass(file, &pos);
        printf("%s, %s\n", pair.token.lexeme, pair.classe);
    } while (pair.token.type != END_OF_PROGRAM);

    fclose(file);
    return 0;
}
