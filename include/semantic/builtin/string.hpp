#pragma once

#include "semantic/class.hpp"

extern semantic_class* builtin_class_string;

class builtin_object_string : public semantic_object {
public:
	builtin_object_string(std::wstring data) : semantic_object(builtin_class_string, {}), val(data) {};
	std::wstring val;

	semantic_node* get_member(std::wstring name) {
		if (this->type->methods.find(name) != this->type->methods.end()) {
			return this->type->methods[name];
		}
		else {
			throw L"no member named " + name;
		}
	}

};