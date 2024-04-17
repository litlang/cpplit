#pragma once

statement* parse_statement_keyword(token_list& Token_list, int& index);

expr* parse_expression_keyword(token_list& Token_list, int& index);