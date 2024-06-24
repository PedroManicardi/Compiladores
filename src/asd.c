        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>

        #define MAX_TOKENS 100

        // Estrutura para armazenar token e tipo de token
        typedef struct {
            char token[50];
            char tipo[100];
            char lineInfo[20];
        } TokenInfo;

        int expressao(char *token){
            if (!strcmp(token, "numero") || !strcmp(token, "ident") || !strcmp(token, "simbolo_vezes") || !strcmp(token, "simbolo_menos") || !strcmp(token, "simbolo_mais") || !strcmp(token, "<ERRO_LEXICO:identificadorinvalido>") || !strcmp(token, "<ERRO_LEXICO:_caracter_invalido>")){
                return 1;
            }
            else{
                return 0;
            }
        }

        int expressao_cond(char *token){
            if (!strcmp(token, "numero") || !strcmp(token, "ident") || !strcmp(token, "simbolo_maior") || !strcmp(token, "simbolo_menor") || !strcmp(token, "simbolo_menor_igual") || !strcmp(token, "simbolo_maior_igual") || !strcmp(token, "simbolo_igual") || !strcmp(token, "<ERRO_LEXICO:identificadorinvalido>") || !strcmp(token, "<ERRO_LEXICO:_caracter_invalido>")){
                return 1;
            }
            else{
                return 0;
            }
        }

        int ident(char *token){
            if (!strcmp(token, "numero") || !strcmp(token, "ident") || !strcmp(token, "<ERRO_LEXICO:_numero_mal_formatado_ou_identificador_invalido>") || !strcmp(token, "<ERRO_LEXICO:_identificador_invalido>")){
                return 1;
            }
            else{
                return 0;
            }
        }

        int sintatic() {
            FILE *arquivo;
            char linha[200];  // assumindo que nenhuma linha do arquivo terá mais de 100 caracteres
            TokenInfo tokens[MAX_TOKENS];
            int num_tokens = 0;

            // Abre o arquivo para leitura
            arquivo = fopen("saida.txt", "r");
            if (arquivo == NULL) {
                perror("Erro ao abrir o arquivo");
                return EXIT_FAILURE;
            }

            char *outputFileName = "relatoriodeerro.txt"; 
            FILE *outputFile = fopen(outputFileName, "w");
            if (outputFile == NULL) {
                perror("Erro ao abrir/criar arquivo de saida");
                fclose(arquivo);
                return 1;
            }

            // Lê o arquivo linha por linha
            while (fgets(linha, sizeof(linha), arquivo)) {
                // Remove o caractere de nova linha, se houver
                linha[strcspn(linha, "\n")] = '\0';

                // Usa strtok para separar o token e o tipo de token
                char *token = strtok(linha, ",");
                char *tipo = strtok(NULL, ",");
                char *lineInfo = strtok(NULL, ",");

                if (token != NULL && tipo != NULL && num_tokens < MAX_TOKENS) {
                    // Remove espaços em branco ao redor dos tokens
                    sscanf(token, " %s", tokens[num_tokens].token);
                    sscanf(tipo, " %s", tokens[num_tokens].tipo);
                    sscanf(lineInfo, " %s", tokens[num_tokens].lineInfo);
                    num_tokens++;
                }
            }

            // Fecha o arquivo após a leitura
            fclose(arquivo);

            // ; após var a, b, c: OK
            // begin end: OK
            // if then: OK
            // while do: OK
            // ; procedure ident: OK
            // . ao fim do programa: OK
            // ; após atribuição: OK

            
            int j = 1;
            for (int i = 0; i < num_tokens; i++){
                char error[100] = "";
                if (ident(tokens[i].tipo) && !strcmp(tokens[i-j].tipo, "VAR")){
                    //printf("%s ", tokens[i].token);
                    if (ident(tokens[i+1].tipo)){
                        //printf("OK\n");
                        j = j + 1;
                    }
                    else if (!strcmp(tokens[i+1].tipo, "simbolo_ponto_virgula")){
                        //printf("OK \n");
                        j = 1;
                    }
                    else{
                        //printf("Erro: ponto e virgula faltando.\n");
                        strcpy(error, "ponto e virgula faltando\n");
                        j = 1;
                    }
                }

                else if (!strcmp(tokens[i].tipo, "PROCEDURE")){
                    //printf("%s ", tokens[i].tipo);
                    if (!strcmp(tokens[i+2].tipo, "simbolo_ponto_virgula")){
                        printf("OK\n");
                    }
                    else{
                        //printf("Erro: ponto e virgula faltando.\n");
                        strcpy(error, "ponto e virgula faltando\n");
                    }
                }

                else if (!strcmp(tokens[i].tipo, "WHILE")){
                    //printf("%s ", tokens[i].tipo);
                    int k = 1;
                    while(expressao_cond(tokens[i+k].tipo)){
                        k++;
                    }

                    if (!strcmp(tokens[i+k].tipo, "DO")){
                        //printf("OK\n");
                    }
                    else{
                        //printf("Erro: DO faltando.\n");
                        strcpy(error, "DO faltando\n");
                    }

                }
                    
                else if (!strcmp(tokens[i].tipo, "IF")){
                    //printf("%s ", tokens[i].tipo);
                    int k = 1;
                    while(expressao_cond(tokens[i+k].tipo)){
                        k++;
                    }

                    if (!strcmp(tokens[i+k].tipo, "THEN")){
                        //printf("OK\n");
                    }
                    else{
                        //printf("Erro: THEN faltando.\n");
                        strcpy(error, "THEN faltando\n");
                    }

                }

                else if (!strcmp(tokens[i].tipo, "BEGIN")){
                    //printf("%s ", tokens[i].token);
                    char estado[20] = "ERRO: END faltando.\n";
                    int begin = 1;
                    int end = 0;
                    for (int k = i + 1; k < num_tokens; k++){
                        if (!strcmp(tokens[k].tipo, "BEGIN")){
                            begin++;
                        }
                        if (!strcmp(tokens[k].tipo, "END")){
                            end++;
                        }
                        if (end == begin){
                            strcpy(estado, "OK");
                            break;
                        }
                    }

                    //printf("%s\n", estado);
                    if (strcmp(estado, "OK")){
                        strcpy(error, "END faltando\n");
                    }

                }

                else if (!strcmp(tokens[i].tipo, "simbolo_atribuicao")){
                    //printf("%s ", tokens[i].tipo);
                    int k = 1;
                    while(expressao(tokens[i+k].tipo)){
                        k++;
                    }
                    
                    if (!strcmp(tokens[i+k].tipo, "simbolo_ponto_virgula")){
                        //printf("OK!\n");
                    }
                    else{
                        //printf("Erro: ponto e virgula faltando.\n");
                        strcpy(error, "ponto e virgula faltando\n");
                    }
                    
                }

                if (i == num_tokens - 1){
                    //printf("%s ", tokens[i].tipo);
                    if (!strcmp(tokens[i].tipo, "simbolo_ponto")){
                        //printf("OK\n");
                    }
                    else{
                        //printf("Erro: programa encerrado sem ponto.\n");
                        strcpy(error, "programa encerrado sem ponto\n");
                    }
                }

                if (tokens[i].tipo[0] == '<'){
                    char lex_error[100];

                    if (!strcmp(tokens[i].tipo, "<ERRO_LEXICO:_numero_mal_formatado_ou_identificador_invalido>")){
                        strcpy(lex_error, "numero mal formatado ou identificador invalido");
                    }

                    if (!strcmp(tokens[i].tipo, "<ERRO_LEXICO:_identificador_invalido>")){
                        strcpy(lex_error, "identificador inválido");
                    }

                    if (!strcmp(tokens[i].tipo, "<ERRO_LEXICO:_caracter_invalido>")){
                        strcpy(lex_error, "caracter inválido");
                    }

                    if (!strcmp(tokens[i].tipo, "<ERRO_LEXICO:_palavra_reservada_mal_formatada>")) {
                        strcpy(lex_error, "palavra reservada mal formatada");
                    }
                    
                    fprintf(outputFile, "%s %s%s %s %s%s%s\n", "Erro léxico na linha", tokens[i].lineInfo, ":", lex_error, "(", tokens[i].token, ")");
                }

                if(strlen(error) > 0){
                    fprintf(outputFile, "%s %s%s %s", "Erro sintático na linha", tokens[i].lineInfo, ":", error);
                }
                
            }

            fclose(outputFile);
            return EXIT_SUCCESS;
        }
