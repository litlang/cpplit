#pragma once

statement_block* parse_statements(token_list& Token_list, int& index, token_type terminator); // temp

statement_block* parse_statement_block(token_list& Token_list, int& index);