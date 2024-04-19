#include "parser/parse_logical.hpp"
#include "ast/nodes.hpp"
#include "parser/parse_comparation.hpp"
#include "parser/check.hpp"

expr* parse_logical_and(token_list& Token_list) {

	expr* result = parse_comparation(Token_list);
	if (check::symbol::is(Token_list.this_(), token_symbol::type::AND_AND)) {
		std::vector<expr*> items;
		items.push_back(result);

		do {
			Token_list.next();
			items.push_back(parse_comparation(Token_list));
		} while (check::symbol::is(Token_list.this_(), token_symbol::type::AND_AND));

		result = new logical_and { items, 0, 0 };
	}

	return result;
}

expr* parse_logical_or(token_list& Token_list) {
	expr* result = parse_logical_and(Token_list);

	if (check::symbol::is(Token_list.this_(), token_symbol::type::OR_OR)) {
		std::vector<expr*> items;
		items.push_back(result);

		do {
			Token_list.next();
			items.push_back(parse_logical_and(Token_list));
		} while (check::symbol::is(Token_list.this_(), token_symbol::type::OR_OR));

		result = new logical_or { items, 0, 0 };
	}

	return result;
}