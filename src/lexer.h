#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

// Função principal do analisador léxico
TokenClassPair getNextTokenClass(FILE *file, int *pos);

#endif // LEXER_H
