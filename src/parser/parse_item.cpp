#include "parser/parse_item.hpp"

#include "parser/parse_suffix.hpp"
#include "parser/parse_keyword.hpp"

#include "parser/parse_expression.hpp"
#include "parser/check.hpp"

expr_entity* make_entity(token_entity* Token) {
	
	if (dynamic_cast<token_number*> (Token) != NULL) {
		return new expr_number { dynamic_cast<token_number*> (Token), Token->BEGIN, Token->END }; // number unit
	}

	else if (dynamic_cast<token_string*> (Token) != NULL) {
		return new expr_string { dynamic_cast<token_string*> (Token), Token->BEGIN, Token->END };
	}

	else if (dynamic_cast<token_boolean*> (Token) != NULL) {
		return new expr_boolean { dynamic_cast<token_boolean*> (Token), Token->BEGIN, Token->END };
	}

	else if (dynamic_cast<token_identifier*> (Token) != NULL) {
		return new expr_identifier { dynamic_cast<token_identifier*> (Token), Token->BEGIN, Token->END }; // id string
	}

	else {
		throw "unknown entity"; //
	}

}


expr* parse_miditem(token_list& Token_list, int& index) {
	expr* result;

	token* first = Token_list.fetch();
	if (dynamic_cast<token_entity*> (first) != NULL) {
		result = make_entity(dynamic_cast<token_entity*> (first));
	}

	else if (dynamic_cast<token_keyword*> (first) != NULL) {
		Token_list.prev(); //temp
		result = parse_expression_keyword(Token_list, index);
	}

	else if (check_symbol_if(first, token_symbol::type::PAREN_LEFT)) {
		result = parse_expression(Token_list, index);
		check_symbol(Token_list, index, token_symbol::type::PAREN_RIGHT);
	}
	else {
		throw "unknown symbol";
	}

	result = parse_suffix(Token_list, index, result);

	return result;
}

