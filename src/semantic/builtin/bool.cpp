#include "semantic/builtin/bool.hpp"
#include "semantic/builtin/string.hpp"
#include "semantic/class.hpp"

#include <vector>
#include <map>

/*class new_semantic_class : public semantic_class {
public:
	new_semantic_class(std::vector<semantic_class*> supers, std::map<std::wstring, semantic_node*> members, std::map<std::wstring, semantic_method*> methods) : members(members), semantic_class(supers, methods) {}

	std::map<std::wstring, semantic_node*> members;
};*/

class _bool_init : public semantic_function {
public:
	_bool_init() : semantic_function(builtin_class_bool) {};

	semantic_object* call(_builtin_object_tuple* arglist) {
		auto arg = arglist->items[0];
		return (dynamic_cast<semantic_method*> (arg->get_member(L"bool"))) -> call(arg, {});
	}
};
auto bool_init = new _bool_init {};

class _bool_bool : public semantic_method {
public:
	_bool_bool() : semantic_method(builtin_class_bool) {};

	semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist) {
		return obj;
	}
};
auto bool_bool = new _bool_bool {};

class _bool_output : public semantic_method {
public:
	_bool_output() : semantic_method(builtin_class_bool) {};

	semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist) {
		return new semantic_object_builtin_string { dynamic_cast<builtin_object_bool*> (obj)->data ? L"真" : L"假" };
	}
};
auto bool_output = new _bool_output {};

semantic_class* builtin_class_bool = new semantic_class { {}, 
{{L"call", bool_init}}, 
{
	{L"bool", bool_bool}, {L"output", bool_output}
}
};