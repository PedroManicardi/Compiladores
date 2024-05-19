#include "lexer.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

// Funcao auxiliar para verificar se o caracter eh especial
int pertence(char c) {
    char caracteres_especiais[] = {'!', '"', '#', '$', '%', '&', '\'', '?', '@', '[', '\\', ']', '^', '_', '`', '|', '~'};
    for (size_t i = 0; i < sizeof(caracteres_especiais) / sizeof(caracteres_especiais[0]); i++) {
        if (caracteres_especiais[i] == c) {
            return 1;
        }
    }
    return 0; 
}

// Funcao principal do analisador lexico
TokenClassPair getNextTokenClass(FILE *file, int *pos) {
    // Declaracao das variaveis
    TokenClassPair pair;
    Token token;
    char c = fgetc(file);
    // Inicializa o vetor de lexema
    memset(token.lexeme, 0, sizeof(token.lexeme));

    // Flag de erro
    bool e = false;
    

    // Ignora espaços em branco, virgulas e comentários
    while (isspace(c) || c == ',' || c == '{') {
        if (c == '{') { // Se encontrar um '{', ignora ate encontrar um '}'
            while (c != '}' && c != EOF) {
                c = fgetc(file);
            }
        }
        c = fgetc(file);
    }

    // Verifica o fim do arquivo
    if (c == EOF) {
        token.type = END_OF_PROGRAM;
        pair.token = token;
        return pair;
    }

    // Analisa o caracter atual e define o tipo de token e o par associado
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

        // Verificacao de palavras reservadas, indentificadores e numeros
        default:
            // Verifica se o caracter lido eh uma letra
            if (isalpha(c)) {
                int j = 0;
                // Continua lendo enquanto for alfanumerico ou caracter especial
                while ((isalnum(c) || pertence(c)) && c != EOF) {
                    token.lexeme[j++] = c;
                    c = fgetc(file);

                    // Marca erro se o caracter for especial
                    if (pertence(c)) {
                        e = true;
                        strcpy(pair.classe, "Erro");
                    }
                }
                // Finaliza a string do lexema
                token.lexeme[j] = '\0'; 

                // Verificacao de palavras reservadas
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
                    // Verifica se houve erro, e em caso contrario se trata de um identificador
                    if (e) {
                        token.type = ERROR;
                        strcpy(pair.classe, "<ERRO_LEXICO: identificador invalido>");
                    } else {
                        token.type = IDENTIFIER;
                        strcpy(pair.classe, "ident");
                    }
                }

                if (!isalpha(c) && !isdigit(c)) {
                    fseek(file, -1, SEEK_CUR); // Volta o caractere lido para o arquivo
                }
            }
            // Verificacao de numeros
            else if (isdigit(c)) {
                int j = 0;
                // Continua lendo enquanto for alfanumerico ou caracter especial
                while ((isalnum(c) || pertence(c)) && c != EOF) {
                    token.lexeme[j++] = c;
                    c = fgetc(file);

                    // Caso seja lido uma letra ou caracter especial, aciona a flag de erro
                    if (isalpha(c) || pertence(c)) {
                        e = true;
                    }

                }
                // Finaliza a string do lexema
                token.lexeme[j] = '\0'; 

                // Verifica se houve erro, e em caso contrario se trata de um numero
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

            // Caso em que o caracter lido eh invalido
            else {
                int j = 0;
                // Continua lendo enquanto for alfanumerico ou caracter especial
                while ((isalnum(c) || pertence(c)) && c != EOF) {
                    token.lexeme[j++] = c;
                    c = fgetc(file);
                }
                // Finaliza a string do lexema
                token.lexeme[j] = '\0'; 
                
                token.type = ERROR;
                
                // Verifica se o caracter especial esta sozinho ou se eh o inicio de um ident mal formatado
                if (strlen(token.lexeme) == 1) {
                    strcpy(pair.classe, "<ERRO_LEXICO: caracter invalido>");
                } else {
                    strcpy(pair.classe, "<ERRO_LEXICO: identificador invalido>");
                }

                if (!isalpha(c) && !isdigit(c)) {
                    fseek(file, -1, SEEK_CUR); // Volta o caractere lido para o arquivo
                }

            }
        }

    // Atualiza a posicao do arquivo
    *pos = ftell(file);
    pair.token = token;

    // Retorna o par token-classe
    return pair;
}