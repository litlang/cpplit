#include "parse_logical.hpp"
#include "parse_expression.hpp"

expr* parse_expression(token_list& Token_list) {
	return parse_logical_or(Token_list);
}