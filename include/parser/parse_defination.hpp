#pragma once

#include "ast/statements/statement.hpp"

defination* parse_defination(token_list& Token_list);
defination_block* parse_defination_block(token_list& Token_list);