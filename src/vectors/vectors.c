#include <vectors/vectors.h>

char_vector_t *newCharVector() {
     char_vector_t *vec = (char_vector_t *)malloc(sizeof(char_vector_t));

     vec->data = NULL;

     vec->size = 0;
     vec->capacity = 0;

     return vec;
}

char_vector_t *charVectorFromString(const char *string) {
     char_vector_t *vec = newCharVector();

     while (*string != '\0') {
          char c = *string;
          charVectorPush(vec, c);
          string++;
     }

     return vec;
}

void resetCharVector(char_vector_t *vector) {
     vector->size = 0;
}

void charVectorPush(char_vector_t *vector, char val) {
     if (vector->data == NULL) {
          vector->data = (char *)malloc(sizeof(char));

          vector->capacity = 1;
     }
     else if (vector->size >= vector->capacity) {
          vector->capacity *= 2;
          vector->data = (char *)realloc(vector->data, sizeof(char) * vector->capacity);
     }

     vector->data[vector->size] = val;
     vector->size++;
}

char charVectorPop(char_vector_t *vector) {
     if (vector->size > 0) {
          char c = vector->data[vector->size - 1];

          vector->size--;
          return c;
     }

     return '\0';
}

char charVectorPeek(char_vector_t *vector, size_t index) {
     if (index > vector->size)
          return '\0';

     return vector->data[index];
}


token_vector_t *newTokenVector() {
     token_vector_t *vec = (token_vector_t *)malloc(sizeof(token_vector_t));

     vec->data = NULL;

     vec->size = 0;
     vec->capacity = 0;

     return vec;
}

void tokenVectorPush(token_vector_t *vector, token_t val) {
     if (vector->data == NULL) {
          vector->data = (token_t *)malloc(sizeof(token_t));

          vector->capacity = 1;
     }
     else if (vector->size >= vector->capacity) {
          vector->capacity *= 2;
          vector->data = (token_t *)realloc(vector->data, sizeof(token_t) * vector->capacity);
     }

     vector->data[vector->size] = val;
     vector->size++;
}

token_t tokenVectorPop(token_vector_t *vector) {
     if (vector->size > 0) {
          token_t t = vector->data[vector->size - 1];

          vector->size--;
          return t;
     }

     return (token_t){ .type = KSCRIPT_TOKEN_TYPE_EOF };
}

token_t tokenVectorPeek(token_vector_t *vector, size_t index) {
     if (index > vector->size) {
          return (token_t){ .type = KSCRIPT_TOKEN_TYPE_EOF };
     }

     return vector->data[index];
}

ast_node_t *newNode() {
     ast_node_t *node = (ast_node_t *)malloc(sizeof(ast_node_t));

     node->left                    = NULL;
     node->right                   = NULL;

     return node;
}