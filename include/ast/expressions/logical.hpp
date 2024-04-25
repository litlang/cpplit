#pragma once

/*class expr_logic : public expr {
public:
	enum class type {
		AND,
		XOR,
		OR,
	};

	expr_logic(type sym, expr* left, expr* right, int begin, int end) : expr(begin, end), SYM(sym), LEFT(left), RIGHT(right) {}

	type SYM;
	expr* LEFT;
	expr* RIGHT;

	std::wstring view() {
		static std::map<type, std::wstring> to_view = {
			{ type::AND, L"&&" },
			{ type::XOR, L"\\\\" },
			{ type::OR, L"||" },
		};

		std::wstring left, right;
		if (dynamic_cast<expr_entity*> (this->LEFT) != NULL) {
			left = this->LEFT->view();
		}
		else {
			left = L"(" + this->LEFT->view() + L")";
		}

		if (dynamic_cast<expr_entity*> (this->RIGHT) != NULL) {
			right = this->RIGHT->view();
		}
		else {
			right = L"(" + this->RIGHT->view() + L")";
		}

		return left + to_view[this->SYM] + right;
	}
};*/

class logical_and : public expr {
public:
	logical_and(std::vector<expr*> items, int begin, int end) : expr(begin, end), items(items) {};

	std::wstring view() {
		std::wstring result = L"(";
		for (expr* item : this->items) {
			result += item->view() + L" && ";
		}
		result = result.substr(0, result.size()-4);
		result += L")";
		return result;
	}

private:
	std::vector<expr*> items;
};

class logical_or : public expr {
public:
	logical_or(std::vector<expr*> items, int begin, int end) : expr(begin, end), items(items) {};

	std::wstring view() {
		std::wstring result = L"(";
		for (expr* item : this->items) {
			result += item->view() + L" || ";
		}
		result = result.substr(0, result.size()-4);
		result += L")";
		return result;
	}

private:
	std::vector<expr*> items;
};

class logical_xor : public expr {
public:
	logical_xor(expr* left, expr* right, int begin, int end) : expr(begin, end), left(left), right(right) {};

	std::wstring view() {
		std::wstring result = L"(";
		result += this->left->view() + L" \\\\ " + this->right->view();
		result += L")";
		return result;
	}

private:
	expr* left;
	expr* right;
};

class logical_not : public expr {
public:
	logical_not(expr* Expr, int begin, int end) : expr(begin, end), Expr(Expr) {};

	std::wstring view() {
		std::wstring result = L"(";
		result += L"!" + this->Expr->view();
		result += L")";
		return result;
	}

private:
	expr* Expr;
};