#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include "token.h"

// Funcao principal do analisador lexico
TokenClassPair getNextTokenClass(FILE *file, int *pos, int *line_number);

#endif // LEXER_H
