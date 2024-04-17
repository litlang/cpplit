#pragma once

#include "semantic/class.hpp"
#include "semantic/builtins.hpp"

#include <iostream>


class _lit_io_output : public semantic_function {
public:
	_lit_io_output() : semantic_function(semantic_builtin_class_null) {};

	semantic_object* call(_builtin_object_tuple* arglist) {
		auto arg = arglist->items[0];
		std::wcout << (dynamic_cast <semantic_object_builtin_string*> (arg->get_member(L"output"))) -> val;
		return semantic_builtin_object_null;
	}
};

static _lit_io_output* lit_io_output = new _lit_io_output {};