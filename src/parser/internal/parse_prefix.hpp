#pragma once

#include "tokens/token_list.hpp"
#include "ast/expressions/expr.hpp"

expr* parse_prefix(token_list& Token_list);