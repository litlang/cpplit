#pragma once

#include "./expr.hpp"

class expr_positive : public expr {
public:
	expr_positive(expr* operand, int begin, int end) : expr(begin, end), operand(operand) {};
	expr* operand;

	std::wstring view() {
		return L"(+" + this->operand->view() + L")";
	}
};

class expr_negative : public expr {
public:
	expr_negative(expr* operand, int begin, int end) : expr(begin, end), operand(operand) {};
	expr* operand;

	std::wstring view() {
		return L"(-" + this->operand->view() + L")";
	}
};

class expr_addition : public expr {
public:
	expr_addition(expr* operand_left, expr* operand_right, int begin, int end) : expr(begin, end), operand_left(operand_left), operand_right(operand_right) {}
	expr* operand_left;
	expr* operand_right;

	std::wstring view() {
		return L"(" + this->operand_left->view() + L"+" + this->operand_right->view() + L")";
	}
};

class expr_subtraction : public expr {
public:
	expr_subtraction(expr* operand_left, expr* operand_right, int begin, int end) : expr(begin, end), operand_left(operand_left), operand_right(operand_right) {}
	expr* operand_left;
	expr* operand_right;

	std::wstring view() {
		return L"(" + this->operand_left->view() + L"-" + this->operand_right->view() + L")";
	}
};

class expr_multiplication : public expr {
public:
	expr_multiplication(expr* operand_left, expr* operand_right, int begin, int end) : expr(begin, end), operand_left(operand_left), operand_right(operand_right) {}
	expr* operand_left;
	expr* operand_right;

	std::wstring view() {
		return L"(" + this->operand_left->view() + L"×" + this->operand_right->view() + L")";
	}
};

class expr_division : public expr {
public:
	expr_division(expr* operand_left, expr* operand_right, int begin, int end) : expr(begin, end), operand_left(operand_left), operand_right(operand_right) {}
	expr* operand_left;
	expr* operand_right;

	std::wstring view() {
		return L"(" + this->operand_left->view() + L"/" + this->operand_right->view() + L")";
	}
};