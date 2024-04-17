#pragma once

#include "tokens/tokens.hpp"

bool string_head_matched(wchar_t ch);

token_string* lex_string(std::wstring src, int& i, const std::wstring& filepath);