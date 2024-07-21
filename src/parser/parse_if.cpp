#include "ast/statements/conditional_branch.hpp"

#include "parse_expression.hpp"
#include "parse_statement_block.hpp"
#include "check.hpp"

conditional_branch* parse_if(token_list& Token_list) {

	check::symbol::require(Token_list, token_symbol::type::PAREN_LEFT);
	expr* Condition = parse_expression(Token_list);
	check::symbol::require(Token_list, token_symbol::type::PAREN_RIGHT);

	check::symbol::require(Token_list, token_symbol::type::BRACE_LEFT);

	statement_block* block = parse_statement_block(Token_list);

	return new conditional_branch { Condition, block, Condition->BEGIN, block->END };
}

#include "ast/expressions/bool.hpp"
conditional_branch* parse_else(token_list& Token_list) {

	check::symbol::require(Token_list, token_symbol::type::BRACE_LEFT);

	statement_block* block = parse_statement_block(Token_list);

	return new conditional_branch { new expr_boolean { new token_boolean { true, 1, 1 }, 1, 1 }, block, 1, block->END };
}

conditional_branches* parse_ifs(token_list& Token_list) {

	std::vector<conditional_branch*> result;
	result.push_back(parse_if(Token_list));

	while (true) {
		if (check::symbol::is(Token_list.this_(), token_symbol::type::EOL_)) {
			if (check::keyword::is(Token_list.peek(), token_keyword::type::ELSE_IF) || check::keyword::is(Token_list.peek(), token_keyword::type::ELSE)) {
				Token_list.next();
			}
			else {
				break;
			}
		}
		else if (check::keyword::is(Token_list.this_(), token_keyword::type::ELSE_IF)) {
			Token_list.next();
			result.push_back(parse_if(Token_list));
		}
		else {
			break;
		}
	}

	if (check::keyword::is(Token_list.this_(), token_keyword::type::ELSE)) {
		Token_list.next();
		result.push_back(parse_else(Token_list));
	}

	return new conditional_branches { result, 1, 1 };
}