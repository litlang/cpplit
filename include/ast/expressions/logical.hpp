#pragma once

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