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

void deTokenize(token_vector_t *vector) {
    for (size_t i = 0; i < vector->size; i++) {
        deTokenizeToken(vector->data[i]);
    }
}

void deTokenizeToken(token_t token) {
    switch (token.type) {
        case KSCRIPT_TOKEN_TYPE_I64:     printf("i64 "); break;
        case KSCRIPT_TOKEN_TYPE_I32:     printf("i32 "); break;
        case KSCRIPT_TOKEN_TYPE_I16:     printf("i16 "); break;
        case KSCRIPT_TOKEN_TYPE_I8:      printf("i8 "); break;
        case KSCRIPT_TOKEN_TYPE_U64:     printf("u64 "); break;
        case KSCRIPT_TOKEN_TYPE_U32:     printf("u32 "); break;
        case KSCRIPT_TOKEN_TYPE_U16:     printf("u16 "); break;
        case KSCRIPT_TOKEN_TYPE_U8:      printf("u8 "); break;
        case KSCRIPT_TOKEN_TYPE_F64:     printf("f64 "); break;
        case KSCRIPT_TOKEN_TYPE_F32:     printf("f32 "); break;
        case KSCRIPT_TOKEN_TYPE_PTR:     printf("ptr "); break;
        case KSCRIPT_TOKEN_TYPE_STR:     printf("str "); break;
        case KSCRIPT_TOKEN_TYPE_BOOL:    printf("bool "); break;

        case KSCRIPT_TOKEN_TYPE_LITERAL: 
            printf("Literal: %s ", token.s); break;
        case KSCRIPT_TOKEN_TYPE_INT_LITERAL: 
            printf("Int literal: %d ", token.i); break;
        case KSCRIPT_TOKEN_TYPE_STR_LITERAL: 
            printf("String literal: \"%s\" ", token.s); break;
        case KSCRIPT_TOKEN_TYPE_BOOL_LITERAL:
            printf("Bool literal: %s", token.b == true ? "true" : "false"); break;

        case KSCRIPT_TOKEN_TYPE_FUNCTION: printf("function "); break;
        case KSCRIPT_TOKEN_TYPE_VAR:      printf("var "); break;
        case KSCRIPT_TOKEN_TYPE_VAL:      printf("val "); break;
        case KSCRIPT_TOKEN_TYPE_IMPORT:   printf("import "); break;
        case KSCRIPT_TOKEN_TYPE_FROM:     printf("from "); break;
        case KSCRIPT_TOKEN_TYPE_MODULE:   printf("module "); break;
        case KSCRIPT_TOKEN_TYPE_WHILE:    printf("while "); break;
        case KSCRIPT_TOKEN_TYPE_TRUE:     printf("true "); break;
        case KSCRIPT_TOKEN_TYPE_FALSE:    printf("false "); break;
        case KSCRIPT_TOKEN_TYPE_FOR:      printf("for "); break;

        case KSCRIPT_TOKEN_TYPE_OPEN_PAREN:    printf("( "); break;
        case KSCRIPT_TOKEN_TYPE_CLOSED_PAREN:  printf(") "); break;
        case KSCRIPT_TOKEN_TYPE_SEMICOLON:     printf("; "); break;
        case KSCRIPT_TOKEN_TYPE_EQUALS:        printf("= "); break;
        case KSCRIPT_TOKEN_TYPE_EXMARK:        printf("! "); break;
        case KSCRIPT_TOKEN_TYPE_QMARK:         printf("? "); break;
        case KSCRIPT_TOKEN_TYPE_DOT:           printf(". "); break;
        case KSCRIPT_TOKEN_TYPE_COMMA:         printf(", "); break;
        case KSCRIPT_TOKEN_TYPE_CBRACKET_OPEN: printf("{ "); break;
        case KSCRIPT_TOKEN_TYPE_CBRACKET_CLOSED: printf("} "); break;
        case KSCRIPT_TOKEN_TYPE_LESS_THAN:     printf("< "); break;
        case KSCRIPT_TOKEN_TYPE_MORE_THAN:     printf("> "); break;
        case KSCRIPT_TOKEN_TYPE_STAR:          printf("* "); break;
        case KSCRIPT_TOKEN_TYPE_MINUS:         printf("- "); break;

        default:
            printf("Unknown token: %d", token.type);
            break;
    }
    printf("\n");
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

                printf("%s:%d:%d: \e[1;31mOVERFLOW ERROR\e[0m: Number is too large\n", debug_path, line, col);
            }
            resetCharVector(buffer);

            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_INT_LITERAL, .i = value });
        }
        else if (current == '(') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_OPEN_PAREN });
        }
        else if (current == ')') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_CLOSED_PAREN });
        }
        else if (current == ';') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_SEMICOLON });
        }
        else if (current == '=') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_EQUALS });
        }
        else if (current == '!') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_EXMARK });
        }
        else if (current == '?') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_QMARK });
        }
        else if (current == '.') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_DOT });
        }
        else if (current == ',') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_COMMA });
        }
        else if (current == '{') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_CBRACKET_OPEN });
        }
        else if (current == '}') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_CBRACKET_CLOSED });
        }
        else if (current == '<') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_LESS_THAN });
        }
        else if (current == '>') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_MORE_THAN });
        }
        else if (current == '"') {
            i++;
            current = vector->data[i];

            while (i < vector->size && current != '"') {
                charVectorPush(buffer, current);

                i++;
                col++;
                current = vector->data[i];
            }

            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_STR_LITERAL, .s = strdup(buffer->data) });
            resetCharVector(buffer);
        }
        else if (current == '*') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_STAR });
        }
        else if (current == '-') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_MINUS });
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
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_BOOL_LITERAL, .b = true });
            }
            else if (strcmp(buffer->data, "false") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_BOOL_LITERAL, .b = false });
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
            else if (strcmp(buffer->data, "ptr") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_PTR });
            }
            else if (strcmp(buffer->data, "str") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_STR });
            }
            else if (strcmp(buffer->data, "bool") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_BOOL });
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

            printf("%s:%d:%d: \e[1;31mSYNTAX ERROR\e[0m: Unknown token '%c'\n", debug_path, line, col, current);
        }
    }

    return tokens;
}
