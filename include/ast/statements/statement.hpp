#pragma once

#include "ast/node.hpp"
#include "ast/expressions/expr.hpp"

#include "semantic/class.hpp"
#include "semantic/environment.hpp"

#include "runtime.hpp"


class statement : public node {
public:
	statement(int begin, int end) : node(begin, end) {};

	std::wstring statement_view(std::wstring s) {
		return s + L";\n";
	}

	virtual void exec(environment env, const runtime& Runtime) {}; //!

};

class expr_statement : public statement {
public:
	expr_statement(expr* Expr, int begin, int end) : statement(begin, end), EXPR(Expr) {};
	expr* EXPR;

	std::wstring view() {
		return statement::statement_view(this->EXPR->view());
	}

	void exec(environment env, const runtime& Runtime) {
		this->EXPR->eval(env, Runtime);
	}
};