#include "parser/parse_prefix.hpp"
#include "parser/parse_item.hpp"
#include "parser/parse_arith.hpp"

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
	else {
		return parse_miditem(Token_list);
	}
}