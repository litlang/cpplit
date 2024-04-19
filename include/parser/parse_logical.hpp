#include "ast/nodes.hpp"

#pragma once

expr* parse_logical_and(token_list& Token_list);
expr* parse_logical_or(token_list& Token_list);