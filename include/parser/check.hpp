#pragma once

#include "tokens/keyword.hpp"
#include "tokens/symbol.hpp"
#include "tokens/token_list.hpp"

namespace check::symbol {

	void require(token_list& Token_list, token_symbol::type Type);
	bool is(token* Token, token_symbol::type Type);

};

namespace check::keyword {
	bool is(token* Token, token_keyword::type Type);
};