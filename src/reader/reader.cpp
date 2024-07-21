#include <fstream>
#include <string>
#include <map>

#include "exceptions/fserrs.hpp"
#include "codec.hpp"

std::map<std::wstring, std::wstring> content_map;


std::wstring read(std::wstring filepath, codec_type Codec_type) {

	std::string source;

	std::ifstream file;
	file.open(encode(filepath), std::ios::in);

	if (! file.is_open()) {
		throw new file_not_exists { filepath }; // perm access
	}

	char c;
	while ((c = file.get()) != EOF) {
		source += c;
	}

	file.close();
	std::wstring result = decode(source, Codec_type);

	content_map[filepath] = result;
	return result;
}

std::wstring get_content(std::wstring filepath) {
	return content_map[filepath];
}