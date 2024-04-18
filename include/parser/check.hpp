#pragma once

#include "tokens/tokens.hpp"

void check_symbol(token_list& Token_list, token_symbol::type Type);
bool check_symbol_if(token* Token, token_symbol::type Type);