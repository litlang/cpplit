#include "ast/nodes.hpp"
#include "parser/parse_statement_block.hpp"
#include "parser/parse_statement.hpp"
#include "exceptions/syntax_errors.hpp"


statement_block* parse_statements(token_list& Token_list, int& index, token_type terminator) {
	std::vector<statement*> statement_list;
	int begin = index;

	while (Token_list.this_()->TYPE != terminator) {

		if (Token_list.this_()->TYPE == token_type::SEMICOLON || Token_list.this_()->TYPE == token_type::EOL_) {
			Token_list.next();
		}

		else {
			statement_list.push_back(parse_statement(Token_list, index));

			if (Token_list.this_()->TYPE != token_type::SEMICOLON &&
				Token_list.this_()->TYPE != token_type::EOL_       &&
				Token_list.this_()->TYPE != terminator) {

				throw new unexpect_token {2,1};
			}
		}

	}
	statement_block* result = new statement_block { statement_list, begin, index };
	Token_list.next();
	return result;
}

statement_block* parse_statement_block(token_list& Token_list, int& index) {
	return parse_statements(Token_list, index, token_type::CLOSE_BRACE);
}