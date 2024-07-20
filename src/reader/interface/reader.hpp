#pragma once

#include "codec.hpp"

std::wstring read(std::wstring filepath, codec_type Codec_type = codec_type::UTF_8);
std::wstring get_content(std::wstring filepath);

class char_stream {
public:
	char_stream(std::wstring data) : data(data), length(data.length()) {};

	wchar_t get() {
		return this->data[this->index];
	}

	void next() {
		this->index += 1;
	}

	wchar_t fetch() {
		wchar_t result = this->get();
		this->next();
		return result;
	}

	bool is_end() {
		if (this->index >= this->length) {
			return true;
		}
		else {
			return false;
		}
	}

private:
	std::wstring data;
	int length;
	int index = 0;
};