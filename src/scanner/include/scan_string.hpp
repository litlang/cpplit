#pragma once

#include "tokens/entity.hpp"

bool string_head_matched(wchar_t ch);

token_string* lex_string(std::wstring src, int& i, const std::wstring& filepath);