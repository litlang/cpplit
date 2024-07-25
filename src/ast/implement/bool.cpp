#include "ast/expressions/bool.hpp"
#include "semantic/builtin/bool.hpp"

semantic_node* expr_boolean::eval(environment env, const runtime& Runtime) {
	return new builtin_object_bool { this->VALUE->VALUE };
}