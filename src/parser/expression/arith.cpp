#include "parser/parse_arith.hpp"
#include "ast/nodes.hpp"
#include "tokens/tokens.hpp"

#include "parser/parse_prefix.hpp"

expr* parse_multi_divis(token_list& Token_list) {
	static std::map<token_symbol::type, binary_expr::type> map = {
		{ token_symbol::type::ASTERISK, binary_expr::type::multiplication },
		{ token_symbol::type::SLASH, binary_expr::type::division },
	};

	expr* left = parse_prefix(Token_list);
	while (dynamic_cast<token_symbol*> (Token_list.this_()) != NULL && map.find((dynamic_cast<token_symbol*> (Token_list.this_()))->Type) != map.end()) {
		auto sym = dynamic_cast<token_symbol*> (Token_list.fetch());
		expr* right = parse_prefix(Token_list);
		left = new binary_expr { map[sym->Type], left, right, left->BEGIN, right->END };
	}
	return left;
}

expr* parse_plus_minus(token_list& Token_list) {
	static std::map<token_symbol::type, binary_expr::type> map = {
		{ token_symbol::type::PLUS, binary_expr::type::addition },
		{ token_symbol::type::MINUS, binary_expr::type::subtraction },
	};

	expr* left = parse_multi_divis(Token_list);
	while (dynamic_cast<token_symbol*> (Token_list.this_()) != NULL && map.find((dynamic_cast<token_symbol*> (Token_list.this_()))->Type) != map.end()) {
		auto sym = dynamic_cast<token_symbol*> (Token_list.fetch());
		expr* right = parse_multi_divis(Token_list);
		left = new binary_expr { map[sym->Type], left, right, left->BEGIN, right->END };
	}
	return left;
}

expr* parse_arith(token_list& Token_list) {
	return parse_plus_minus(Token_list);
}