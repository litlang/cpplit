#pragma once

#include "codec.hpp"

std::wstring read(std::wstring filepath, codec_type Codec_type = codec_type::UTF_8);
std::wstring get_content(std::wstring filepath);