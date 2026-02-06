#pragma once

#include <stddef.h>
#include <stdbool.h>

typedef enum {
    // Types
    KSCRIPT_TOKEN_TYPE_I64,
    KSCRIPT_TOKEN_TYPE_I32,
    KSCRIPT_TOKEN_TYPE_I16,
    KSCRIPT_TOKEN_TYPE_I8,

    KSCRIPT_TOKEN_TYPE_U64,
    KSCRIPT_TOKEN_TYPE_U32,
    KSCRIPT_TOKEN_TYPE_U16,
    KSCRIPT_TOKEN_TYPE_U8,

    KSCRIPT_TOKEN_TYPE_F64,
    KSCRIPT_TOKEN_TYPE_F32,

    KSCRIPT_TOKEN_TYPE_PTR,
    KSCRIPT_TOKEN_TYPE_STR,
    KSCRIPT_TOKEN_TYPE_BOOL,

    // Compiler stuff,
    KSCRIPT_TOKEN_TYPE_LITERAL,
    KSCRIPT_TOKEN_TYPE_INT_LITERAL,
    KSCRIPT_TOKEN_TYPE_STR_LITERAL,
    KSCRIPT_TOKEN_TYPE_EOF,

    // Keywords
    KSCRIPT_TOKEN_TYPE_FUNCTION,
    KSCRIPT_TOKEN_TYPE_VAR,
    KSCRIPT_TOKEN_TYPE_VAL,
    KSCRIPT_TOKEN_TYPE_IMPORT,
    KSCRIPT_TOKEN_TYPE_FROM,
    KSCRIPT_TOKEN_TYPE_MODULE,
    KSCRIPT_TOKEN_TYPE_WHILE,
    KSCRIPT_TOKEN_TYPE_TRUE,
    KSCRIPT_TOKEN_TYPE_FALSE,
    KSCRIPT_TOKEN_TYPE_FOR,

    // Symbols
    KSCRIPT_TOKEN_TYPE_OPEN_PAREN,
    KSCRIPT_TOKEN_TYPE_CLOSED_PAREN,

    KSCRIPT_TOKEN_TYPE_SEMICOLON,
    KSCRIPT_TOKEN_TYPE_EQUALS,

    KSCRIPT_TOKEN_TYPE_EXMARK,
    KSCRIPT_TOKEN_TYPE_QMARK,

    KSCRIPT_TOKEN_TYPE_DOT,
    KSCRIPT_TOKEN_TYPE_COMMA,

    KSCRIPT_TOKEN_TYPE_CBRACKET_OPEN,
    KSCRIPT_TOKEN_TYPE_CBRACKET_CLOSED,

    KSCRIPT_TOKEN_TYPE_LESS_THAN,
    KSCRIPT_TOKEN_TYPE_MORE_THAN,

} token_type;

typedef struct {
    token_type      type;

    union {
        int             i;
        float           f;
        double          d;

        char            *s;
        bool            b;
    };
} token_t;

typedef struct {
     char     *data;

     size_t   size;
     size_t   capacity;

} char_vector_t;

typedef struct {
     token_t    *data;

     size_t   size;
     size_t   capacity;

} token_vector_t;
