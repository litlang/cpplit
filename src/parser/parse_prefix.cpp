#include "parser/parse_prefix.hpp"
#include "parser/parse_item.hpp"
#include "parser/parse_arith.hpp"
#include "parser/check.hpp"
#include "parser/parse_comparation.hpp"
#include "parser/check.hpp"

#include "ast/expressions/arith.hpp"

expr* parse_prefix(token_list& Token_list) {
	token* first = Token_list.this_();

	if (check::symbol::is(first, token_symbol::type::PLUS)) {
		Token_list.next();
		auto val = parse_multi_divis(Token_list);
		return new expr_positive { val, first->BEGIN, val->END };
	}

	else if (check::symbol::is(first, token_symbol::type::MINUS)) {
		Token_list.next();
		auto val = parse_multi_divis(Token_list);
		return new expr_negative { val, first->BEGIN, val->END };
	}

	else if (check::symbol::is(first, token_symbol::type::NOT)) {
		Token_list.next();
		return new logical_not { parse_comparation(Token_list), 0, 0 };
	}

	else {
		return parse_miditem(Token_list);
	}
}