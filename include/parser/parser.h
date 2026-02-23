#pragma once

#include <types/types.h>
#include <common/common.h>

#include <stdio.h>
#include <tokenizer/tokenizer.h>

binding_power_t getBindingPower(token_type type);
ast_node_type   tokenToExpression(token_t token);

ast_parent_t*
astParseExpression(token_vector_t* tokens, size_t* index, float min_bp);
ast_parent_t astParseTokens(token_vector_t* tokens);