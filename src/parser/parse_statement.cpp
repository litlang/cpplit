#include "ast/nodes.hpp"

#include "parser/parse_expression.hpp"

#include "parser/parse_keyword.hpp"

statement* parse_statement(token_list& Token_list, int& index) {
	if (dynamic_cast<token_identifier*> (Token_list.this_()) != NULL && Token_list.peek()->TYPE == token_type::EQUAL) {
		token_identifier* idn = dynamic_cast<token_identifier*> (Token_list.fetch()); // :=
		// index += 2; // += -= ...
		Token_list.next();
		expr* val = parse_expression(Token_list, index); // a = +1
		return new defination { idn, val, idn->BEGIN, val->END };
	}

	else if (dynamic_cast<token_keyword*> (Token_list.this_()) != NULL) {
		return parse_statement_keyword(Token_list, index);
	}

	else { // 有点草率？
		expr* Expr = parse_expression(Token_list, index);
		return new expr_statement { Expr, Expr->BEGIN, Expr->END };
	}
}