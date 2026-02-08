#pragma once

#include <vectors/vectors.h>
#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>

#include <string.h>
#include <common/common.h>

char_vector_t       *fileToCharVector(const char *path);

void                deTokenize(token_vector_t *vector);
void                deTokenizeToken(token_t token);

void                deTokenizeTokenKeyword(token_t token);

token_vector_t      *tokenize(char_vector_t *vector, const char *debug_path);