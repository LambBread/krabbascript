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
     node->left_nodes_capacity     = 0;
     node->left_nodes_size         = 0;

     node->right                   = NULL;
     node->right_nodes_capacity    = 0;
     node->right_nodes_size        = 0;

     return node;
}

void nodePushLeft(ast_node_t *node, ast_node_t *val) {
     if (node->left == NULL) {
          node->left = (ast_node_t **)malloc(sizeof(ast_node_t *));

          node->left_nodes_capacity = 1;
     }
     else if (node->left_nodes_size >= node->left_nodes_capacity) {
          node->left_nodes_capacity *= 2;
          node->left = (ast_node_t **)realloc(node->left, sizeof(ast_node_t *) * node->left_nodes_capacity);
     }

     node->left[node->left_nodes_size] = val;
     node->left_nodes_size++;
}

void nodePushRight(ast_node_t *node, ast_node_t *val) {
     if (node->right == NULL) {
          node->right = (ast_node_t **)malloc(sizeof(ast_node_t *));

          node->right_nodes_capacity = 1;
     }
     else if (node->right_nodes_size >= node->right_nodes_capacity) {
          node->right_nodes_capacity *= 2;
          node->right = (ast_node_t **)realloc(node->right, sizeof(ast_node_t *) * node->right_nodes_capacity);
     }

     node->right[node->right_nodes_size] = val;
     node->right_nodes_size++;
}

ast_node_t *nodePopLeft(ast_node_t *node) {
     if (node->left_nodes_size > 0) {
          ast_node_t *n = node->left[node->left_nodes_size - 1];

          node->left_nodes_size--;
          return n;
     }

     ast_node_t *empty = (ast_node_t *)malloc(sizeof(ast_node_t));
     empty->type = KSCRIPT_AST_NODE_TYPE_NONE;

     return empty;
}

ast_node_t *nodePopRight(ast_node_t *node) {
     if (node->right_nodes_size > 0) {
          ast_node_t *n = node->right[node->right_nodes_size - 1];

          node->right_nodes_size--;
          return n;
     }

     ast_node_t *empty = (ast_node_t *)malloc(sizeof(ast_node_t));
     empty->type = KSCRIPT_AST_NODE_TYPE_NONE;

     return empty;
}