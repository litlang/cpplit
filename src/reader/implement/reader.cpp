#include <fstream>
#include <string>
#include <sstream>

#include "exceptions/fserrs.hpp"
#include "codec.hpp"

std::wstring read(std::wstring filepath, codec_type Codec_type) {

	std::ifstream file(encode(filepath), std::ios::in);
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	return decode(buffer.str(), Codec_type);
}

// std::wstring get_content(std::wstring filepath) {
// 	return content_map[filepath];
// }