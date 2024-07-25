#pragma once

struct position {
	int line;
	int column;
};

static position position_format(const std::wstring& src, const int& index) {
	int line = 1;
    int column = 1;

    for (int i = 0; i < index; i += 1) {
        if (src[i] == L'\n') { //! NEL, CRLF?
            line += 1;
            column = 1;
        }
        else {
            column += 1;
        }
    }

    return { line, column };
}