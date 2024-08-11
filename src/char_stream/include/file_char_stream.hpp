#include "char_stream.hpp"

class file_char_stream : public char_stream {
public:
	file_char_stream(std::wstring data) : data(data), length(data.length()) {};

	wchar_t peek() {
		return this->data[this->index];
	}

	wchar_t get() {
		wchar_t result = this->get();
		this->next();
		return result;
	}

	bool is_end() {
		if (this->index == this->length) {
			return true;
		}
		else {
			return false;
		}
	}

protected:
	void next() {
		this->index += 1;
		if (this->index > length) {
			throw "error: index out of range";
		}
	}

private:
	std::wstring data;
	int length;
	int index = 0;
};