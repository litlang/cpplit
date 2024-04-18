#include "parser/parse_comparation.hpp"
#include "parser/parse_expression.hpp"

expr* parse_expression(token_list& Token_list) {
	return parse_comparation(Token_list);
}