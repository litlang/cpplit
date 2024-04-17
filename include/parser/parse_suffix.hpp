#pragma once

#include "ast/nodes.hpp"

expr* parse_suffix(token_list& Token_list, int& index, expr* item);