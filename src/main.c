
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
int main(int argc, char *argv[]) {
    // Verificacao se o arquivo de entrada foi passado
    if (argc != 2) {
        printf("Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return 1;
    }

    // Abre o arquivo de entrada
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    // Define o arquivo de saida
    char *outputFileName = "saida.txt"; 
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Erro ao abrir/criar arquivo de saida");
        fclose(file);
        return 1;
    }

    int line_number = 1;

    // Inicializa a posicao do arquivo e o par
    int pos = 0;
    TokenClassPair pair;

    // Chama a funcao do analisador lexico para cada token do arquivo de entrada
    do {
        pair = getNextTokenClass(file, &pos, &line_number);
        if (pair.token.type != END_OF_PROGRAM) {
            // Escreve no arquivo de saida
            fprintf(outputFile, "%s, %s, Linha %d\n", pair.token.lexeme, pair.classe, pair.line_number);
        }
    } while (pair.token.type != END_OF_PROGRAM);

    // Fecha os arquivos
    fclose(file);
    fclose(outputFile);

    return 0;
}
