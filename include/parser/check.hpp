#pragma once

#include "tokens/tokens.hpp"

namespace check_symbol {

	void require(token_list& Token_list, token_symbol::type Type);
	bool is(token* Token, token_symbol::type Type);

};