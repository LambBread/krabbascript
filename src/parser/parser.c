#include <parser/parser.h>

binding_power_t getBindingPower(token_type type)
{
    switch (type)
    {
        case KSCRIPT_TOKEN_TYPE_STAR:
            return (binding_power_t){2.0f, 2.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_SLASH:
            return (binding_power_t){2.0f, 2.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_PLUS:
            return (binding_power_t){1.0f, 1.1f};
            break;
        case KSCRIPT_TOKEN_TYPE_MINUS:
            return (binding_power_t){1.0f, 1.1f};
            break;
        default:
            return (binding_power_t){0.0f, 0.0f};
            break;
    }
}

ast_node_t* tokenToNode(token_t token)
{
    ast_node_t* node = newNode();

    switch (token.type)
    {
        case KSCRIPT_TOKEN_TYPE_LITERAL:
            node->type   = KSCRIPT_AST_NODE_TYPE_LITERAL;
            node->lexeme = token.s;

            break;
        case KSCRIPT_TOKEN_TYPE_BOOL_LITERAL:
            node->type   = KSCRIPT_AST_NODE_TYPE_BOOL_LITERAL;
            node->lexeme = token.b == true ? "true" : "false";

            break;
        case KSCRIPT_TOKEN_TYPE_STR_LITERAL:
            node->type   = KSCRIPT_AST_NODE_TYPE_STR_LITERAL;
            node->lexeme = strdup(token.s);

            break;
        case KSCRIPT_TOKEN_TYPE_INT_LITERAL:
            node->type = KSCRIPT_AST_NODE_TYPE_INT_LITERAL;
            sprintf(node->lexeme, "%d", token.i);

            break;
        case KSCRIPT_TOKEN_TYPE_EOF:
            node->type = KSCRIPT_AST_NODE_TYPE_EOF;
            break;
        case KSCRIPT_TOKEN_TYPE_PLUS:
            node->type   = KSCRIPT_AST_NODE_TYPE_PLUS;
            node->lexeme = "+";
            break;
        case KSCRIPT_TOKEN_TYPE_MINUS:
            node->type   = KSCRIPT_AST_NODE_TYPE_MINUS;
            node->lexeme = "-";
            break;
        case KSCRIPT_TOKEN_TYPE_STAR:
            node->type   = KSCRIPT_AST_NODE_TYPE_MUL;
            node->lexeme = "*";
            break;
        case KSCRIPT_TOKEN_TYPE_SLASH:
            node->type   = KSCRIPT_AST_NODE_TYPE_DIV;
            node->lexeme = "/";
            break;
        case KSCRIPT_TOKEN_TYPE_LOGICAL_AND:
            node->type   = KSCRIPT_AST_NODE_TYPE_LOGICAL_AND;
            node->lexeme = "&&";
            break;
        case KSCRIPT_TOKEN_TYPE_LOGICAL_OR:
            node->type   = KSCRIPT_AST_NODE_TYPE_LOGICAL_OR;
            node->lexeme = "||";
            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_AND:
            node->type   = KSCRIPT_AST_NODE_TYPE_BWISE_AND;
            node->lexeme = "&";
            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_OR:
            node->type   = KSCRIPT_AST_NODE_TYPE_BWISE_OR;
            node->lexeme = "|";
            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_XOR:
            node->type   = KSCRIPT_AST_NODE_TYPE_BWISE_XOR;
            node->lexeme = "^";
            break;
        default:
            errors_generated++;
            printf("\033[1;31mERROR\033[0m: Unexpected token ");
            deTokenizeTokenKeyword(token);

            node->type = KSCRIPT_AST_NODE_TYPE_NONE;

            break;
    }

    return node;
}

ast_parent_t*
astParseExpression(token_vector_t* tokens, size_t* index, float min_bp)
{
    ast_node_t* lhs = tokenToNode(tokenVectorPeek(tokens, *index));
    (*index)++;

    while (true)
    {
        token_t op = tokenVectorPeek(tokens, *index);
        if (op.type == KSCRIPT_TOKEN_TYPE_EOF)
            break;

        binding_power_t bp =
                getBindingPower(tokenVectorPeek(tokens, *index).type);

        if (bp.left < min_bp)
            break;

        (*index)++;
        ast_node_t* op_node = tokenToNode(op);

        ast_node_t* rhs = astParseExpression(tokens, index, bp.right);

        op_node->left  = lhs;
        op_node->right = rhs;

        lhs = op_node;
    }

    return lhs;
}

ast_parent_t astParseTokens(token_vector_t* tokens)
{
    // TODO
    ast_parent_t parent = {0};
    (void)tokens;

    return parent;
}
