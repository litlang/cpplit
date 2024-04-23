#include "parser/parse_prefix.hpp"
#include "parser/parse_item.hpp"
#include "parser/parse_arith.hpp"
#include "parser/check.hpp"
#include "parser/parse_comparation.hpp"

expr* parse_prefix(token_list& Token_list) {
	static std::map<token_type, unary_expr::type> unary_map = {
		{ token_type::PLUS, unary_expr::type::positive },
		{ token_type::MINUS, unary_expr::type::negative },
	};

	token* first = Token_list.this_();

	if (unary_map.find(first->TYPE) != unary_map.end()) {
		Token_list.next();
		auto val = parse_multi_divis(Token_list);
		return new unary_expr { unary_map[first->TYPE], val, first->BEGIN, val->END };
	}

	else if (check::symbol::is(first, token_symbol::type::NOT)) {
		Token_list.next();
		return new logical_not { parse_comparation(Token_list), 0, 0 };
	}

	else {
		return parse_miditem(Token_list);
	}
}