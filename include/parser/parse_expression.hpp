#pragma once

#include "tokens/token_list.hpp"
#include "ast/expressions/expr.hpp"

expr* parse_expression(token_list& Token_list);