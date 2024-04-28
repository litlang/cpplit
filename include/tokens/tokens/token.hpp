#pragma once

#include <string>
#include <map>
#include <vector>


class token {
public:
	int BEGIN, END;
	token(int begin, int end) : BEGIN(begin), END(end) {};

	virtual std::wstring view() = 0;

};