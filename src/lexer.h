#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

// Funcao principal do analisador lexico
TokenClassPair getNextTokenClass(FILE *file, int *pos);

#endif // LEXER_H