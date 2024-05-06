#pragma once

#include "semantic/class.hpp"

extern semantic_class* builtin_class_bool;

class builtin_object_bool : public semantic_object {
public:
	builtin_object_bool(bool data) : semantic_object(builtin_class_bool, {}), data(data) {};
	bool data;

	semantic_node* get_member(std::wstring name) {
		if (this->type->methods.find(name) != this->type->methods.end()) {
			return this->type->methods[name];
		}
		else {
			throw L"no member named " + name;
		}
	}

};