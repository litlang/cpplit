#include "ast/nodes.hpp"

#include "parser/parse_expression.hpp"
#include "parser/check.hpp"
#include "parser/parse_defination.hpp"

defination* parse_defination(token_list& Token_list) {
	if (dynamic_cast<token_identifier*> (Token_list.this_()) != NULL) {
		token_identifier* id = dynamic_cast<token_identifier*> (Token_list.this_());
		Token_list.next();

		if (check_symbol_if(Token_list.this_(), token_symbol::type::EQUAL)) {
			Token_list.next();

			auto val = parse_expression(Token_list);
			return new defination { id, val, id->BEGIN, val->END };
		}
		else {
			throw "暂不支持泛型";
		}
	}
	else {
		throw "expect identifier";
	}
}

defination_block* parse_defination_block(token_list& Token_list) {
	int begin = Token_list.this_()->BEGIN;

	std::vector<defination*> result;

	while (!check_symbol_if(Token_list.this_(), token_symbol::type::BRACE_RIGHT)) {

		if (check_symbol_if(Token_list.this_(), token_symbol::type::SEMICOLON) || check_symbol_if(Token_list.this_(), token_symbol::type::EOL_)) {
			Token_list.next();
		}
		else {
			result.push_back(parse_defination(Token_list));
			if (!check_symbol_if(Token_list.this_(), token_symbol::type::BRACE_RIGHT) && !check_symbol_if(Token_list.this_(), token_symbol::type::SEMICOLON) && !check_symbol_if(Token_list.this_(), token_symbol::type::EOL_)) {
				throw "unexpect token";
			}
		}
	}

	Token_list.fetch();
	return new defination_block { result, begin, Token_list.this_()->END };
}