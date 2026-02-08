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

    KSCRIPT_TOKEN_TYPE_ARRAY,

    // Compiler stuff,
    KSCRIPT_TOKEN_TYPE_LITERAL,
    KSCRIPT_TOKEN_TYPE_INT_LITERAL,
    KSCRIPT_TOKEN_TYPE_STR_LITERAL,
    KSCRIPT_TOKEN_TYPE_BOOL_LITERAL,
    KSCRIPT_TOKEN_TYPE_NONE,

    KSCRIPT_TOKEN_TYPE_EOF,
    KSCRIPT_TOKEN_TYPE_ARROW,
    KSCRIPT_TOKEN_TYPE_EQUALS_EQUALS,

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
    KSCRIPT_TOKEN_TYPE_COLON,
    KSCRIPT_TOKEN_TYPE_EQUALS,

    KSCRIPT_TOKEN_TYPE_EXMARK,
    KSCRIPT_TOKEN_TYPE_QMARK,

    KSCRIPT_TOKEN_TYPE_DOT,
    KSCRIPT_TOKEN_TYPE_COMMA,

    KSCRIPT_TOKEN_TYPE_CBRACKET_OPEN,
    KSCRIPT_TOKEN_TYPE_CBRACKET_CLOSED,

    KSCRIPT_TOKEN_TYPE_SBRACKET_OPEN,
    KSCRIPT_TOKEN_TYPE_SBRACKET_CLOSED,

    KSCRIPT_TOKEN_TYPE_LESS_THAN,
    KSCRIPT_TOKEN_TYPE_MORE_THAN,
    KSCRIPT_TOKEN_TYPE_STAR,

    KSCRIPT_TOKEN_TYPE_PLUS,
    KSCRIPT_TOKEN_TYPE_MINUS,

    KSCRIPT_TOKEN_TYPE_SLASH,
    KSCRIPT_TOKEN_TYPE_BSLASH,

    KSCRIPT_TOKEN_TYPE_IF,
    KSCRIPT_TOKEN_TYPE_ELIF,
    KSCRIPT_TOKEN_TYPE_ELSE,

    KSCRIPT_TOKEN_TYPE_PLUS_EQ,
    KSCRIPT_TOKEN_TYPE_MINUS_EQ,
    KSCRIPT_TOKEN_TYPE_MUL_EQ,
    KSCRIPT_TOKEN_TYPE_DIV_EQ,

    KSCRIPT_TOKEN_TYPE_PLUS_PLUS,
    KSCRIPT_TOKEN_TYPE_MINUS_MINUS,


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

typedef enum {
    // Arithmetic operators
    KSCRIPT_AST_NODE_TYPE_DIV,
    KSCRIPT_AST_NODE_TYPE_MUL,
    KSCRIPT_AST_NODE_TYPE_PLUS,
    KSCRIPT_AST_NODE_TYPE_MINUS,

    // Logical & bitwise operators
    KSCRIPT_AST_NODE_TYPE_AND,
    KSCRIPT_AST_NODE_TYPE_OR,
    KSCRIPT_AST_NODE_TYPE_NOT,

    KSCRIPT_AST_NODE_TYPE_BWISE_AND,
    KSCRIPT_AST_NODE_TYPE_BWISE_OR,
    KSCRIPT_AST_NODE_TYPE_BWISE_XOR,
    KSCRIPT_AST_NODE_TYPE_BWISE_NOT,

    KSCRIPT_AST_NODE_TYPE_VARIABLE_DEC,
    KSCRIPT_AST_NODE_TYPE_VALUE_DEC,

    KSCRIPT_AST_NODE_TYPE_FUNCTION_DEC,
    KSCRIPT_AST_NODE_TYPE_FUNCTION_DEF,

    KSCRIPT_AST_NODE_TYPE_LITERAL,
    KSCRIPT_AST_NODE_TYPE_BOOL_LITERAL,
    KSCRIPT_AST_NODE_TYPE_STR_LITERAL,
    KSCRIPT_AST_NODE_TYPE_INT_LITERAL,

    KSCRIPT_AST_NODE_TYPE_NONE
} ast_node_type;

typedef struct ast_node_t {
    ast_node_type           type;

    struct ast_node_t       **left;
    size_t                  left_nodes_size;
    size_t                  left_nodes_capacity;

    struct ast_node_t       **right;
    size_t                  right_nodes_size;
    size_t                  right_nodes_capacity;

    union {
        int                 i;
        char                *s;
        bool                b;
    };
} ast_node_t;

typedef ast_node_t ast_parent_t;

typedef struct {
    float       left;
    float       right;

} binding_power_t;