#pragma once

#include <vector>
#include <map>
#include <string>

#include "./node.hpp"

class semantic_method;

class semantic_class : public semantic_node {
public:
	semantic_class(std::vector<semantic_class*> supers = {}, std::map<std::wstring, semantic_node*> members = {}, std::map<std::wstring, semantic_method*> methods = {}) : semantic_node(members), supers(supers), methods(methods) {};
	std::vector<semantic_class*> supers;
	std::map<std::wstring, semantic_method*> methods;

	semantic_node* get_member(std::wstring name);
};

class semantic_object : public semantic_node {
public:
	semantic_object(semantic_class* type, std::map<std::wstring, semantic_object*> members) : type(type), members(members) {};
	semantic_class* type;
	semantic_node* get_member(std::wstring name);

private:
	std::map<std::wstring, semantic_object*> members;
};

#include "semantic/builtin/tuple.hpp"
class semantic_function : public semantic_node {
public:
	semantic_function(semantic_class* type) : return_type(type) {};
	semantic_class* return_type;

	virtual semantic_object* call(_builtin_object_tuple* arglist) {
		return this->call(arglist);
	}

	semantic_node* get_member(std::wstring name) {
	/*	if (name == L"call") {

		}*/
		return NULL;
	}
};

class semantic_method : public semantic_node {
public:
	semantic_method(semantic_class* type) : return_type(type) {};
	semantic_class* return_type;
	virtual semantic_object* call(semantic_object* obj, std::vector<semantic_object*> arglist) {
		throw "no call";
	};

	semantic_node* get_member(std::wstring name) {
		throw L"no member named " + name;
	}
};

// null == null