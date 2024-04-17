#pragma once

#include <string>

#include "language/language.hpp"


class exception {
public:
	virtual std::wstring msg(language L) = 0;
};