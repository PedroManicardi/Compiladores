#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stdio.h>

// Funcao principal do analisador lexico
TokenClassPair getNextTokenClass(FILE *file, int *pos, int *line_count);

#endif // LEXER_H
