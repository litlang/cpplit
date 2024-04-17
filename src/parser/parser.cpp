#include "tokens/tokens.hpp"
#include "scanner/scanner.hpp"

#include "ast/nodes.hpp"
#include "parser/parser.hpp"

#include "parser/parse_statement_block.hpp"

statement_block* parse_exe(std::wstring filepath) { // parse main program
	token_list Token_list = scan(filepath);
	int index = 1; // pass BOF
	Token_list.fetch();
	
	return parse_statements(Token_list, index, token_type::EOF_);
}


/*
语句：
定义，如a=1
过程：不可赋值的，如 loop, do{}, break, (async?)
记录：可被赋值的代码块，如func, class (call?) // 或函数返回值也可以赋值，a=a+1后面的运算也可以赋值
*/