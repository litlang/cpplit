#include "ast/nodes.hpp"
#include "parser/parse_keyword.hpp"

#include "parser/loop/parse_loop.hpp"

#include "parser/parse_expression.hpp"
#include "parser/parse_statement_block.hpp"
#include "parser/check.hpp"

// ----------

conditional_branch* parse_if(token_list& Token_list) {

	check_symbol(Token_list, token_symbol::type::PAREN_LEFT);
	expr* Condition = parse_expression(Token_list);
	check_symbol(Token_list, token_symbol::type::PAREN_RIGHT);

	check_symbol(Token_list, token_symbol::type::BRACE_LEFT);

	statement_block* block = parse_statement_block(Token_list);

	return new conditional_branch { Condition, block, Condition->BEGIN, block->END };
}

conditional_branch* parse_else(token_list& Token_list) {

	check_symbol(Token_list, token_symbol::type::BRACE_LEFT);

	statement_block* block = parse_statement_block(Token_list);

	return new conditional_branch { new expr_boolean { new token_boolean { true, 1, 1 }, 1, 1 }, block, 1, block->END };
}

conditional_branches* parse_ifs(token_list& Token_list) {

	std::vector<conditional_branch*> result;
	result.push_back(parse_if(Token_list));

	while (true) {
		if (check_symbol_if(Token_list.this_(), token_symbol::type::EOL_)) {
			Token_list.next();
		}
		else if (dynamic_cast<token_keyword*> (Token_list.this_()) != NULL && dynamic_cast<token_keyword*> (Token_list.this_())->Type == token_keyword::type::ELSE_IF) {
			Token_list.next();
			result.push_back(parse_if(Token_list));
		}
		else {
			break;
		}
	}

	if (dynamic_cast<token_keyword*> (Token_list.this_()) != NULL && dynamic_cast<token_keyword*> (Token_list.this_())->Type == token_keyword::type::ELSE) {
		Token_list.next();
		result.push_back(parse_else(Token_list));
	}

	return new conditional_branches { result, 1, 1 };
}

// --------

statement* parse_statement_keyword(token_list& Token_list) {
	token_keyword::type keyword = dynamic_cast<token_keyword*> (Token_list.this_()) -> Type;
	Token_list.next();

	if (keyword == token_keyword::type::IF) {
		return parse_ifs(Token_list);
	}

	else if (keyword == token_keyword::type::ELSE_IF) {
		throw L"'else if' without privious 'if'";
	}

	else if (keyword == token_keyword::type::ELSE) {
		throw L"'else' without privious 'if'";
	}

	else if (keyword == token_keyword::type::LOOP) {
		return parse_loop(Token_list);
	}

	else {
		throw "保留kw";
	}
}

// ----------

#include "parser/namespace/parse_namespace.hpp"
expr* parse_expression_keyword(token_list& Token_list) {
	token_keyword* kw = dynamic_cast<token_keyword*> (Token_list.this_());
	Token_list.next();

	if (kw->Type == token_keyword::type::IMPORT) {
		int begin = Token_list.this_()->BEGIN;

		check_symbol(Token_list, token_symbol::type::PAREN_LEFT);

		expr* path = parse_expression(Token_list);

		import* result;
		// check if path formally valid
		if (dynamic_cast<expr_string*> (path) != NULL) {
			result = new import { dynamic_cast<expr_string*> (path), begin, Token_list.this_()->END };
		}
		else {
			throw "import path must be literal_string";
		}// import()

		check_symbol(Token_list, token_symbol::type::PAREN_RIGHT);

		return result;

	}

	else if (kw->Type == token_keyword::type::NAMESPACE) {
		return parse_namespace(Token_list);
	}

	else {
		throw L"保留kw";
	}
}