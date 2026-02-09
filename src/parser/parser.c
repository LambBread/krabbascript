#include <parser/parser.h>

binding_power_t getBindingPower(token_type type) {
    switch (type) {
        case KSCRIPT_TOKEN_TYPE_STAR:
            return (binding_power_t){ 2.0f, 2.1f };
            break;
        case KSCRIPT_TOKEN_TYPE_SLASH:
            return (binding_power_t){ 2.0f, 2.1f };
            break;
        case KSCRIPT_TOKEN_TYPE_PLUS:
            return (binding_power_t){ 1.0f, 1.1f };
            break;
        case KSCRIPT_TOKEN_TYPE_MINUS:
            return (binding_power_t){ 1.0f, 1.1f };
            break;
        default:
            return (binding_power_t){ 0.0f, 0.0f };
            break;
    }

}

ast_node_t *tokenToNode(token_t token) {
    ast_node_t *node = newNode();

    switch (token.type) {
        case KSCRIPT_TOKEN_TYPE_LITERAL:
            node->type   = KSCRIPT_AST_NODE_TYPE_LITERAL;
            node->lexeme = token.s;

            break;
        case KSCRIPT_TOKEN_TYPE_BOOL_LITERAL:
            node->type   = KSCRIPT_AST_NODE_TYPE_BOOL_LITERAL;
            node->b      = token.b;

            break;
        case KSCRIPT_TOKEN_TYPE_STR_LITERAL:
            node->type   = KSCRIPT_AST_NODE_TYPE_STR_LITERAL;
            node->s      = strdup(token.s);

            break;
        case KSCRIPT_TOKEN_TYPE_INT_LITERAL:
            node->type   = KSCRIPT_AST_NODE_TYPE_INT_LITERAL;
            node->i      = token.i;

            break;
        case KSCRIPT_TOKEN_TYPE_EOF:
            node->type   = KSCRIPT_AST_NODE_TYPE_NONE;
            break;
        case KSCRIPT_TOKEN_TYPE_PLUS:
            node->type   = KSCRIPT_AST_NODE_TYPE_PLUS;
            break;
        case KSCRIPT_TOKEN_TYPE_MINUS:
            node->type   = KSCRIPT_AST_NODE_TYPE_MINUS;
            break;
        case KSCRIPT_TOKEN_TYPE_STAR:
            node->type   = KSCRIPT_AST_NODE_TYPE_MUL;
            break;
        case KSCRIPT_TOKEN_TYPE_SLASH:
            node->type   = KSCRIPT_AST_NODE_TYPE_DIV;
            break;
        case KSCRIPT_TOKEN_TYPE_LOGICAL_AND:
            node->type   = KSCRIPT_AST_NODE_TYPE_LOGICAL_AND;
            break;
        case KSCRIPT_TOKEN_TYPE_LOGICAL_OR:
            node->type   = KSCRIPT_AST_NODE_TYPE_LOGICAL_OR;
            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_AND:
            node->type   = KSCRIPT_AST_NODE_TYPE_BWISE_AND;
            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_OR:
            node->type   = KSCRIPT_AST_NODE_TYPE_BWISE_OR;
            break;
        case KSCRIPT_TOKEN_TYPE_BWISE_XOR:
            node->type   = KSCRIPT_AST_NODE_TYPE_BWISE_XOR;
            break;
        default:
            errors_generated++;
            printf("\e[1;31mERROR\e[0m: Unexpected token ");
            deTokenizeTokenKeyword(token);

            node->type = KSCRIPT_AST_NODE_TYPE_NONE;

            break;
    }

    return node;
}

ast_parent_t *astParseExpression(token_vector_t *tokens, size_t *index, float min_bp) {
    ast_node_t *lhs = tokenToNode(tokenVectorPeek(tokens, *index));
    (*index)++;

    while (true) {
        token_t op = tokenVectorPeek(tokens, *index);
        if (op.type == KSCRIPT_TOKEN_TYPE_EOF) break;

        binding_power_t bp = getBindingPower(tokenVectorPeek(tokens, *index).type);

        if (bp.left < min_bp) break;

        (*index)++;
        ast_node_t *op_node = tokenToNode(op);

        ast_node_t *rhs = astParseExpression(tokens, index, bp.right);

        nodePushLeft(op_node, lhs);
        nodePushRight(op_node, rhs);

        lhs = op_node;
    }

    return lhs;
}

ast_parent_t astParseTokens(token_vector_t *tokens) {
    // TODO
    ast_parent_t parent = { 0 };
    (void)tokens;

    return parent;
}