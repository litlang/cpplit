#include "parser/loop/parse_loop.hpp"

#include "parser/parse_expression.hpp"
#include "parser/parse_statement_block.hpp"
#include "parser/check.hpp"

condition_loop* parse_condition_loop(token_list& Token_list, int& index) {

	check_symbol(Token_list, index, token_symbol::type::PAREN_LEFT);
	expr* Condition = parse_expression(Token_list, index);
	check_symbol(Token_list, index, token_symbol::type::PAREN_RIGHT);

	check_symbol(Token_list, index, token_symbol::type::BRACE_LEFT);

	statement_block* block = parse_statement_block(Token_list, index);

	return new condition_loop { Condition, block, Condition->BEGIN, block->END };
}

loop_statement* parse_loop(token_list& Token_list, int& index) {
	return parse_condition_loop(Token_list, index);
}