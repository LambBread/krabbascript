#include <tokenizer/tokenizer.h>

char_vector_t *fileToCharVector(const char *path) {
    FILE *file_ptr = fopen(path, "r");

    if (file_ptr == NULL) {
        perror("\e[1;31mERROR\e[0m: Failed to open file");
        exit(1);            
    }

    char_vector_t *vector = newCharVector();

    int c;
    while ((c = fgetc(file_ptr)) != EOF) {
        charVectorPush(vector, (char)c);
    }

    fclose(file_ptr);
    return vector;
}

token_vector_t *tokenize(char_vector_t *vector) {

    char_vector_t  *buffer = newCharVector();
    token_vector_t *tokens = newTokenVector();

    (void)buffer;

    size_t i = 0;
    while (i < vector->size) {
        // Handle symbols
        switch(vector->data[i]) {

            case '(':

        }
    }

    return tokens;
}
