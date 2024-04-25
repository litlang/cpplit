#pragma once

class binary_expr : public expr {
public:

	enum class type {
		addition,
		subtraction,
		multiplication,
		division,
	};

	type Type;
	expr* OPERAND_LEFT, * OPERAND_RIGHT;
	binary_expr(type Type, expr* operand1, expr* operand2, int begin, int end) : expr(begin, end), Type(Type), OPERAND_LEFT(operand1), OPERAND_RIGHT(operand2) {};

	std::wstring view() {

		static std::map<type, std::wstring> view_map = {
			{ type::addition, L"+" },
			{ type::subtraction, L"-" },
			{ type::multiplication, L"*" },
			{ type::division, L"/" },
		};

		std::wstring result = L"(";
		result += this->OPERAND_LEFT->view() + view_map[this->Type] + this->OPERAND_RIGHT->view();
		result += L")";
		return result;
	}
};