#pragma once

#include "parser/parse_defination.hpp"

TYPE_namespace* parse_namespace(token_list& Token_list, int& index) {

	check_symbol(Token_list, index, token_symbol::type::BRACE_LEFT);

	defination_block* block = parse_defination_block(Token_list, index);

	return new TYPE_namespace { block, block->BEGIN, block->END };

}