#include "ast/nodes.hpp"
#include "parser/parse_logical.hpp"
#include "parser/parse_expression.hpp"

expr* parse_expression(token_list& Token_list) {
	return parse_logical_and(Token_list);
}