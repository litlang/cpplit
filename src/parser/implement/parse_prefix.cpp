#include "parse_prefix.hpp"
#include "parse_item.hpp"
#include "parse_arith.hpp"
#include "check.hpp"
#include "parse_comparation.hpp"
#include "check.hpp"

#include "ast/expressions/arith.hpp"
#include "ast/expressions/logical.hpp"
#include "ast/expressions/reference.hpp"


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

	else if (check::symbol::is(first, token_symbol::type::AT)) {
		Token_list.next();
		expr* item = parse_prefix(Token_list);
		return new reference { item, item->BEGIN, item->END };
	}

	else {
		return parse_miditem(Token_list);
	}
}