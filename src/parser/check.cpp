#include "parser/check.hpp"
#include "exceptions/syntax_errors.hpp"

void check_symbol(token_list& Token_list, token_symbol::type Type) {
	if (dynamic_cast<token_symbol*> (Token_list.this_()) != NULL && (dynamic_cast<token_symbol*> (Token_list.this_())) -> Type == Type) {
		Token_list.next();
	}
	else {
		throw new expect_symbol { {Token_list.this_()->BEGIN, Token_list.this_()->END}, Type };
	}
}

bool check_symbol_if(token* Token, token_symbol::type Type) {
	if (dynamic_cast<token_symbol*> (Token) != NULL && (dynamic_cast<token_symbol*> (Token))->Type == Type) {
		return true;
	}
	else {
		return false;
	}
}