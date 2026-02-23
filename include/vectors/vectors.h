#pragma once

#include <types/types.h>
#include <stdlib.h>

#include <assert.h>

char_vector_t* newCharVector();
char_vector_t* charVectorFromString(const char* string);
void           resetCharVector(char_vector_t* vector);

void charVectorPush(char_vector_t* vector, char val);
char charVectorPop(char_vector_t* vector);

char charVectorPeek(char_vector_t* vector, size_t index);

token_vector_t* newTokenVector();
void            tokenVectorPush(token_vector_t* vector, token_t val);
token_t         tokenVectorPop(token_vector_t* vector);

token_t tokenVectorPeek(token_vector_t* vector, size_t index);

ast_node_t* newNode();

void nodePushLeft(ast_node_t* node, ast_node_t* val);
void nodePushRight(ast_node_t* node, ast_node_t* val);

ast_node_t* nodePopLeft(ast_node_t* node);
ast_node_t* nodePopRight(ast_node_t* node);