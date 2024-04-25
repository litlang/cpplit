#pragma once

#include "tokens/tokens.hpp"
#include "ast/nodes.hpp"

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

class defination : public statement {
public:
	defination(token_identifier* Identifier, expr* Val, int begin, int end) : statement(begin, end), IDENTIFIER(Identifier), VALUE(Val) {}; // 'id' to 'ref'
	token_identifier* IDENTIFIER;
	expr* VALUE;

	std::wstring view() {
		return statement::statement_view(this->IDENTIFIER->view() + L" = " + this->VALUE->view());
	}

	void exec(environment& env, const runtime& Runtime) {
		env.add(this->IDENTIFIER->VALUE, this->VALUE->eval(env, Runtime));
	}
};

class statement_block : public statement {
public:
	statement_block(std::vector<statement*> block, int begin, int end) : statement(begin, end), BLOCK(block) {};
	std::vector<statement*> BLOCK;

	std::wstring view() {
		std::wstring result;
		for (auto Statement : this->BLOCK) {
			result += Statement->view();
		}
		return result;
	}

	void exec(environment env, const runtime& Runtime) {
		for (auto Statement : this->BLOCK) {
			if (dynamic_cast<defination*> (Statement) != NULL) {
				(dynamic_cast<defination*> (Statement))->exec(env, Runtime);
			}
			else {
				Statement->exec(env, Runtime);
			}
		}
	}
};


class defination_block : public statement { // inhret node?
public:
	defination_block(std::vector<defination*> block, int begin, int end) : statement(begin, end), BLOCK(block) {};

	std::vector<defination*> BLOCK;

	std::wstring view() {
		std::wstring result;

		for (auto Defination : this->BLOCK) {
			result += Defination->view();
		}
		return result;
	}
};

class TYPE_namespace : public expr {
public:
	TYPE_namespace(defination_block* block, int begin, int end) : expr(begin, end), BLOCK(block) {};
	defination_block* BLOCK;

	std::wstring view() {
		return L"namespace {\n" + block_indent(this->BLOCK->view()) + L"}";
	}
};

/*class defination_block : public statement_block {
public:
	defination_block(std::vector<defination*> block, int begin, int end) : statement_block(block, begin, end) {};
};*/



/*class program_definations : public defination_block {
public:
	std::wstring view() {
		std::wstring result = L":";
		for (auto Statement : this->BLOCK) {
			result += Statement->view() + L"\n";
		}
		return result;
	}
};
*/