#include "parser/parse_import.hpp"
#include "ast/nodes.hpp"
#include "parser/check.hpp"
#include "parser/parse_expression.hpp"

import* parse_import(token_list& Token_list) {
	int begin = Token_list.this_()->BEGIN;

	check::symbol::require(Token_list, token_symbol::type::PAREN_LEFT);

	expr* path = parse_expression(Token_list);

	import* result;
	if (dynamic_cast<expr_string*> (path) != NULL) {
		result = new import { dynamic_cast<expr_string*> (path), begin, Token_list.this_()->END };
	}
	else {
		throw "import path must be literal_string";
	}

	check::symbol::require(Token_list, token_symbol::type::PAREN_RIGHT);

	return result;
};