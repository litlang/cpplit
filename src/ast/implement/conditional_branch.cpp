#include "ast/statements/conditional_branch.hpp"
#include "call_method.hpp"

void conditional_branches::exec(environment env, const runtime& Runtime) {
	for (auto branch : this->BRANCHES) {
		semantic_object* condition = dynamic_cast<semantic_object*> (branch->CONDITION->eval(env, Runtime));
		semantic_object* interface;

		try {
			interface = call_method(condition, L"bool");
		}
		catch (const char*) {
			throw "no impl: bool()";
		}

		bool result = dynamic_cast<builtin_object_bool*> (interface) -> data;

		if (result) {
			branch->BLOCK->exec(env, Runtime);
			break;
		}
	}
};