#pragma once

#include "ast/statements/statement.hpp"

statement_block* parse_statements(token_list& Token_list, token_symbol::type terminator); // temp

statement_block* parse_statement_block(token_list& Token_list);