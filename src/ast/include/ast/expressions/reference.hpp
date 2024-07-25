#pragma once

#include "ast/expressions/expr.hpp"

class reference : public expr {
public:
	reference(expr* item, int begin, int end) : expr(begin, end), item(item) {};
	expr* item;

	std::wstring view() {
		return L"(@" + this->item->view() + L")";
	}
};