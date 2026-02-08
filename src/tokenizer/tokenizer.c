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

        case KSCRIPT_TOKEN_TYPE_OPEN_PAREN:         printf("( "); break;
        case KSCRIPT_TOKEN_TYPE_CLOSED_PAREN:       printf(") "); break;
        case KSCRIPT_TOKEN_TYPE_SEMICOLON:          printf("; "); break;
        case KSCRIPT_TOKEN_TYPE_EQUALS:             printf("= "); break;
        case KSCRIPT_TOKEN_TYPE_EXMARK:             printf("! "); break;
        case KSCRIPT_TOKEN_TYPE_QMARK:              printf("? "); break;
        case KSCRIPT_TOKEN_TYPE_DOT:                printf(". "); break;
        case KSCRIPT_TOKEN_TYPE_COMMA:              printf(", "); break;
        case KSCRIPT_TOKEN_TYPE_CBRACKET_OPEN:      printf("{ "); break;
        case KSCRIPT_TOKEN_TYPE_CBRACKET_CLOSED:    printf("} "); break;
        case KSCRIPT_TOKEN_TYPE_LESS_THAN:          printf("< "); break;
        case KSCRIPT_TOKEN_TYPE_MORE_THAN:          printf("> "); break;
        case KSCRIPT_TOKEN_TYPE_STAR:               printf("* "); break;
        case KSCRIPT_TOKEN_TYPE_MINUS:              printf("- "); break;
        case KSCRIPT_TOKEN_TYPE_COLON:              printf(": "); break;
        case KSCRIPT_TOKEN_TYPE_SBRACKET_OPEN:      printf("[ "); break;
        case KSCRIPT_TOKEN_TYPE_SBRACKET_CLOSED:    printf("] "); break;
        case KSCRIPT_TOKEN_TYPE_SLASH:              printf("/ "); break;
        case KSCRIPT_TOKEN_TYPE_BSLASH:             printf("\\ "); break;
        case KSCRIPT_TOKEN_TYPE_IF:                 printf("if "); break;
        case KSCRIPT_TOKEN_TYPE_ELIF:               printf("elif "); break;
        case KSCRIPT_TOKEN_TYPE_ELSE:               printf("else "); break;
        case KSCRIPT_TOKEN_TYPE_ARROW:              printf("-> "); break;
        case KSCRIPT_TOKEN_TYPE_EQUALS_EQUALS:      printf("== "); break;

        case KSCRIPT_TOKEN_TYPE_ARRAY:              printf("array "); break;
        case KSCRIPT_TOKEN_TYPE_PLUS:               printf("+ "); break;

        case KSCRIPT_TOKEN_TYPE_PLUS_EQ:            printf("+= "); break;
        case KSCRIPT_TOKEN_TYPE_MINUS_EQ:           printf("-= "); break;
        case KSCRIPT_TOKEN_TYPE_MUL_EQ:             printf("*= "); break;
        case KSCRIPT_TOKEN_TYPE_DIV_EQ:             printf("/= "); break;

        case KSCRIPT_TOKEN_TYPE_PLUS_PLUS:          printf("++ "); break;
        case KSCRIPT_TOKEN_TYPE_MINUS_MINUS:        printf("-- "); break;

        case KSCRIPT_TOKEN_TYPE_EOF:                printf("EOF "); break;

        default:
            printf("Unknown token: %d", token.type);
            break;
    }
    printf("\n");
}

void deTokenizeTokenKeyword(token_t token) {
    switch (token.type) {
        case KSCRIPT_TOKEN_TYPE_I64:     printf("i64"); break;
        case KSCRIPT_TOKEN_TYPE_I32:     printf("i32"); break;
        case KSCRIPT_TOKEN_TYPE_I16:     printf("i16"); break;
        case KSCRIPT_TOKEN_TYPE_I8:      printf("i8"); break;
        case KSCRIPT_TOKEN_TYPE_U64:     printf("u64"); break;
        case KSCRIPT_TOKEN_TYPE_U32:     printf("u32"); break;
        case KSCRIPT_TOKEN_TYPE_U16:     printf("u16"); break;
        case KSCRIPT_TOKEN_TYPE_U8:      printf("u8"); break;
        case KSCRIPT_TOKEN_TYPE_F64:     printf("f64"); break;
        case KSCRIPT_TOKEN_TYPE_F32:     printf("f32"); break;
        case KSCRIPT_TOKEN_TYPE_PTR:     printf("ptr"); break;
        case KSCRIPT_TOKEN_TYPE_STR:     printf("str"); break;
        case KSCRIPT_TOKEN_TYPE_BOOL:    printf("bool"); break;

        case KSCRIPT_TOKEN_TYPE_LITERAL: 
            printf("%s", token.s); break;
        case KSCRIPT_TOKEN_TYPE_INT_LITERAL: 
            printf("%d", token.i); break;
        case KSCRIPT_TOKEN_TYPE_STR_LITERAL: 
            printf("\"%s\"", token.s); break;
        case KSCRIPT_TOKEN_TYPE_BOOL_LITERAL:
            printf("%s", token.b == true ? "true" : "false"); break;

        case KSCRIPT_TOKEN_TYPE_FUNCTION: printf("function"); break;
        case KSCRIPT_TOKEN_TYPE_VAR:      printf("var"); break;
        case KSCRIPT_TOKEN_TYPE_VAL:      printf("val"); break;
        case KSCRIPT_TOKEN_TYPE_IMPORT:   printf("import"); break;
        case KSCRIPT_TOKEN_TYPE_FROM:     printf("from"); break;
        case KSCRIPT_TOKEN_TYPE_MODULE:   printf("module"); break;
        case KSCRIPT_TOKEN_TYPE_WHILE:    printf("while"); break;
        case KSCRIPT_TOKEN_TYPE_TRUE:     printf("true"); break;
        case KSCRIPT_TOKEN_TYPE_FALSE:    printf("false"); break;
        case KSCRIPT_TOKEN_TYPE_FOR:      printf("for"); break;

        case KSCRIPT_TOKEN_TYPE_OPEN_PAREN:         printf("("); break;
        case KSCRIPT_TOKEN_TYPE_CLOSED_PAREN:       printf(")"); break;
        case KSCRIPT_TOKEN_TYPE_SEMICOLON:          printf(";"); break;
        case KSCRIPT_TOKEN_TYPE_EQUALS:             printf("="); break;
        case KSCRIPT_TOKEN_TYPE_EXMARK:             printf("!"); break;
        case KSCRIPT_TOKEN_TYPE_QMARK:              printf("?"); break;
        case KSCRIPT_TOKEN_TYPE_DOT:                printf("."); break;
        case KSCRIPT_TOKEN_TYPE_COMMA:              printf(","); break;
        case KSCRIPT_TOKEN_TYPE_CBRACKET_OPEN:      printf("{"); break;
        case KSCRIPT_TOKEN_TYPE_CBRACKET_CLOSED:    printf("}"); break;
        case KSCRIPT_TOKEN_TYPE_LESS_THAN:          printf("<"); break;
        case KSCRIPT_TOKEN_TYPE_MORE_THAN:          printf(">"); break;
        case KSCRIPT_TOKEN_TYPE_STAR:               printf("*"); break;
        case KSCRIPT_TOKEN_TYPE_MINUS:              printf("-"); break;
        case KSCRIPT_TOKEN_TYPE_COLON:              printf(":"); break;
        case KSCRIPT_TOKEN_TYPE_SBRACKET_OPEN:      printf("["); break;
        case KSCRIPT_TOKEN_TYPE_SBRACKET_CLOSED:    printf("]"); break;
        case KSCRIPT_TOKEN_TYPE_SLASH:              printf("/"); break;
        case KSCRIPT_TOKEN_TYPE_BSLASH:             printf("\\"); break;
        case KSCRIPT_TOKEN_TYPE_IF:                 printf("if"); break;
        case KSCRIPT_TOKEN_TYPE_ELIF:               printf("elif"); break;
        case KSCRIPT_TOKEN_TYPE_ELSE:               printf("else"); break;
        case KSCRIPT_TOKEN_TYPE_ARROW:              printf("->"); break;
        case KSCRIPT_TOKEN_TYPE_EQUALS_EQUALS:      printf("=="); break;

        case KSCRIPT_TOKEN_TYPE_ARRAY:              printf("array"); break;
        case KSCRIPT_TOKEN_TYPE_PLUS:               printf("+"); break;

        case KSCRIPT_TOKEN_TYPE_PLUS_EQ:            printf("+="); break;
        case KSCRIPT_TOKEN_TYPE_MINUS_EQ:           printf("-="); break;
        case KSCRIPT_TOKEN_TYPE_MUL_EQ:             printf("*="); break;
        case KSCRIPT_TOKEN_TYPE_DIV_EQ:             printf("/="); break;

        case KSCRIPT_TOKEN_TYPE_PLUS_PLUS:          printf("++"); break;
        case KSCRIPT_TOKEN_TYPE_MINUS_MINUS:        printf("--"); break;

        case KSCRIPT_TOKEN_TYPE_EOF:                printf("EOF"); break;

        default:
            printf("??");
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
            col++;
        }
        else if (current == ')') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_CLOSED_PAREN });
            col++;
        }
        else if (current == ';') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_SEMICOLON });
            col++;
        }
        else if (current == '=') {
            if (i + 1 < vector->size && vector->data[i + 1] == '=') {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_EQUALS_EQUALS });
                i++;
                col += 2;
            }
            else {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_EQUALS });
                col++;
            }
        }
        else if (current == '!') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_EXMARK });
            col++;
        }
        else if (current == '?') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_QMARK });
            col++;
        }
        else if (current == '.') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_DOT });
            col++;
        }
        else if (current == ',') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_COMMA });
            col++;
        }
        else if (current == '{') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_CBRACKET_OPEN });
            col++;
        }
        else if (current == '}') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_CBRACKET_CLOSED });
            col++;
        }
        else if (current == '<') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_LESS_THAN });
            col++;
        }
        else if (current == '>') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_MORE_THAN });
            col++;
        }
        else if (current == '"') {
            resetCharVector(buffer);
            i++; 
            col++;
    
            while (i < vector->size) {
                current = vector->data[i];

                if (current == '\\' && i + 1 < vector->size) {
                    char next = vector->data[i + 1];
                    if (next == '"') {
                        charVectorPush(buffer, '"');
                        i += 2; 
                        col += 2;
                        continue;
                    }
                }

                if (current == '"') break;

                charVectorPush(buffer, current);
                if (current == '\n') { line++; col = 1; }
                else col++;
                i++;
            }

            charVectorPush(buffer, '\0');
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_STR_LITERAL, .s = strdup(buffer->data) });
    
            resetCharVector(buffer);
        }
        else if (current == '*') {
            if (i + 1 < vector->size && vector->data[i + 1] == '=') {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_MUL_EQ });

                i++;
                col += 2;
            }
            else {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_STAR });
                col++;
            }
        }
        else if (current == '-') {
            // Handle ->
            if (i + 1 < vector->size && vector->data[i + 1] == '>') {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_ARROW });
                i++;
                col += 2;
            }
            // Handle -=
            else if (i + 1 < vector->size && vector->data[i + 1] == '=') {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_MINUS_EQ });
                i++;
                col += 2;
            }
            // Handle --
            else if (i + 1 < vector->size && vector->data[i + 1] == '-') {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_MINUS_MINUS });
                i++;
                col += 2;
            }
            else {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_MINUS });
                col++;
            }
        }
        else if (current == ':') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_COLON });
            col++;
        }
        else if (current == '[') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_SBRACKET_OPEN });
            col++;
        }
        else if (current == ']') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_SBRACKET_CLOSED });
            col++;
        }
        else if (current == '/') {
            // Handle /=
            if (i + 1 < vector->size && vector->data[i + 1] == '=') {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_DIV_EQ });
                i++;

                col += 2;
            }
            else {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_SLASH });
                col++;
            }
        }
        else if (current == '\\') {
            tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_BSLASH });
            col++;
        }
        else if (current == '#') {
            while (i < vector->size && current != '\n') {
                i++;
                col++ ;;
                
                current = vector->data[i];
            }

            if (i < vector->size && vector->data[i] == '\n') {
                line++;
                col = 1;
            }
        }
        else if (current == '+') {
            // Handle +=
            if (i + 1 < vector->size && vector->data[i + 1] == '=') {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_PLUS_EQ });

                i++;
                col += 2;
            }
            // Handle ++
            if (i + 1 < vector->size && vector->data[i + 1] == '+') {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_PLUS_PLUS });

                i++;
                col += 2;
            }
            else {
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_PLUS });
                col++;
            }
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
            else if (strcmp(buffer->data, "array") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_ARRAY });
            }
            else if (strcmp(buffer->data, "if") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_IF });
            }
            else if (strcmp(buffer->data, "elif") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_ELIF });
            }
            else if (strcmp(buffer->data, "else") == 0) {
                resetCharVector(buffer);
                tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_ELSE });
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

            printf("%s:%d:%d: \e[1;31mLEXICAL ERROR\e[0m: Unexpected character '%c'\n", debug_path, line, col, current);
        }
    }
    tokenVectorPush(tokens, (token_t){ .type = KSCRIPT_TOKEN_TYPE_EOF });

    return tokens;
}
