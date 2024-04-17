#pragma once

#include "utils/coding.hpp"

std::wstring read(std::wstring filepath, coding Coding = coding::UTF_8);
std::wstring get_content(std::wstring filepath);