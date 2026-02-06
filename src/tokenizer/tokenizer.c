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

token_vector_t *tokenize(char_vector_t *vector, const char *debug_path) {

    char_vector_t  *buffer = newCharVector();
    token_vector_t *tokens = newTokenVector();

    int line = 1;
    int col = 1;
    for (size_t i = 0; i < vector->size; i++) {
        char current = vector->data[i];

        if (isdigit(current)) {
            while (i < vector->size && isdigit(current)) {
                charVectorPush(buffer, current);

                i++;
                col++;
                current = vector->data[i];
            }

            charVectorPush(buffer, '\0');
            i--;

            int value = atoi(buffer->data);

            if (value == -1) {
                errors_generated++;

                printf("\e[1;31mERROR in %s:%d:%d:\e[0m: Number is too large!\n", debug_path, line, col);
                printf("\e[1;31m==== BUILD FAILED with %d %s ====\e[0m\n", errors_generated, 
                    errors_generated == 1 ? "error" : "errors");

                exit(1);
            }
            resetCharVector(buffer);
        }
        else if (isalnum(current)) {
            while (i < vector->size && isalnum(current)) {
                charVectorPush(buffer, current);

                i++;
                col++;
                current = vector->data[i];
            }
            charVectorPush(buffer, '\0');
            i--;

            if (strcmp(buffer->data, "function") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_FUNCTION });
            }
            else if (strcmp(buffer->data, "var") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_VAR });
            }
            else if (strcmp(buffer->data, "val") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_VAL });
            }
            else if (strcmp(buffer->data, "import") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_IMPORT });
            }
            else if (strcmp(buffer->data, "from") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_FROM });
            }
            else if (strcmp(buffer->data, "module") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_MODULE });
            }
            else if (strcmp(buffer->data, "while") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_WHILE });
            }
            else if (strcmp(buffer->data, "true") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_LITERAL, .b = true });
            }
            else if (strcmp(buffer->data, "false") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_FALSE, .b = false });
            }
            else if (strcmp(buffer->data, "for") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_FOR });
            }
            else if (strcmp(buffer->data, "i64") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_I64 });
            }
            else if (strcmp(buffer->data, "i32") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_I32 });
            }
            else if (strcmp(buffer->data, "i16") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_I16 });
            }
            else if (strcmp(buffer->data, "i8") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_I8 });
            }
            else if (strcmp(buffer->data, "u64") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_U64 });
            }
            else if (strcmp(buffer->data, "u32") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_U32 });
            }
            else if (strcmp(buffer->data, "u16") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_U16 });
            }
            else if (strcmp(buffer->data, "u8") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_U8 });
            }
            else if (strcmp(buffer->data, "f64") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_F64 });
            }
            else if (strcmp(buffer->data, "f32") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_F32 });
            }
            else if (strcmp(buffer->data, "i8") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_I8 });
            }
            else {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_LITERAL, .s = strdup(buffer->data)});
                resetCharVector(buffer);
            }
        }
        else if (isspace(current)) {
            if (current == '\n') {
                line++;
                col = 1;
            }
            continue;
        }
        else {
            errors_generated++;

            printf("%s:%d:%d: \e[1;31mSYNTAX ERROR\e[0m: Unknown token\n", debug_path, line, col);
            printf("\e[1;31m==== BUILD FAILED with %d %s ====\e[0m\n", errors_generated, 
                errors_generated == 1 ? "error" : "errors");

            exit(1);
        }
    }

    return tokens;
}
