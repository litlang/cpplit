#include "parser/parse_comparation.hpp"

#include "parser/parse_arith.hpp"

#include "ast/nodes.hpp"

expr* parse_comparation(token_list& Token_list, int& index) {

	static std::map<token_type, comparation::type> map = {
		{ token_type::EQUAL_EQUAL, comparation::EQUAL },
		{ token_type::GREATER, comparation::GREATER },
		{ token_type::LESS, comparation::LESS },
		{ token_type::NOT_EQUAL, comparation::NOT_EQUAL },
		{ token_type::GREATER_EQUAL, comparation::GREATER_EQUAL },
		{ token_type::LESS_EQUAL, comparation::LESS_EQUAL },
	};
	expr* result;
	expr* left;

	result = parse_arith(Token_list, index);

	// token_symbol::type
	if (map.find(Token_list.this_()->TYPE) != map.end()) {
		expr* left = result;
		std::vector<std::pair<comparation::type, expr*>> right;

		do {
			comparation::type comp_type = map[Token_list.this_()->TYPE];
			Token_list.next();

			expr* comp_item = parse_arith(Token_list, index);
			right.push_back({ comp_type, comp_item });
		} while (map.find(Token_list.this_()->TYPE) != map.end());

		result = new comparation { left, right, left->BEGIN, right.back().second->END };
	}

	return result;
}