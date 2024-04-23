#pragma once

#include <string>
#include <map>
#include <vector>


enum class token_type {

	temp,

	// operators

	AT,

	QUESTION,
	NOT, // !
	XOR,
	AND, // AMPERSAND &
	OR, // BAR |

	BIT_INVERSION, // *!
	BIT_AND,       // *&
	BIT_XOR,       
	BIT_OR,        // *|


	PLUS,         // + 
	MINUS,        // -
	ASTERISK,     // *
	SLASH,        // /
	CARET,        // ^
	CARET_SLASH,  // ^/
	PERCENT,      // %

	/// comparision operators
	GREATER,          // >
	LESS,             // <
	GREATER_EQUAL,    // >=
	LESS_EQUAL,       // <=
	EQUAL_EQUAL,      // ==
	NOT_EQUAL,        // !==
	IDENTICAL,        // ===
	NOT_IDENTICAL,    // !=== identity
	// !> !< !>= ...

	/// logical operators
	NOT_NOT, // !!
	AND_AND, // &&
	XOR_XOR,
	OR_OR,   // ||

	/// relational operators emm
	BELONG,           // ->
	SUB,     // =>
	NOT_BELONG,       // !->
	NOT_SUB, // !=>

	/// assign ops
	EQUAL,             // =
	PLUS_EQUAL,        // +=
	MINUS_EQUAL,       // -=
	ASTERISK_EQUAL,    // *=
	SLASH_EQUAL,       // /=
	CARET_EQUAL,       // ^=
	CARET_SLASH_EQUAL, // ^/=
	PERCENT_EQUAL,     // %=


	AT_EQUAL, // @=

	TILDE, //


	// seperators
	BOF_,
	EOL_,
	EOF_,

	COMMA,     // ,
	DOT,       // .
	COLON,     // :
	SEMICOLON, // ;

	OPEN_PAREN,    // (
	CLOSE_PAREN,   // )
	OPEN_BRACKET,  // [
	CLOSE_BRACKET, // ]
	OPEN_BRACE,    // {
	CLOSE_BRACE,   // }

	DOUBLE_ANGLE_BRACKET_LEFT,  // <<
	DOUBLE_ANGLE_BRACKET_RIGHT, // >>

};

class token {
public:
	token_type TYPE;
	int BEGIN, END;
	token(token_type type, int begin, int end) : TYPE(type), BEGIN(begin), END(end) {};

	virtual std::wstring view() {
		return this->view();
	};

};

class token_list {
public:

	token_list(std::vector<token*> data) : data(data) {};

	token* this_() {
		return this->data[this->index];
	} //temp

	token* peek() {
		return this->data[this->index + 1];
	}

	void next() {
		this->index += 1;
	}

	void prev() {
		this->index -= 1;
	}

	token* fetch() {
		token* result = this->data[this->index];
		this->index += 1;
		return result;
	}

	std::wstring view() {
		std::wstring result;
/*		int l = this->data.size();
	    for (int i = 0; i < l; i += 1) {
	    	result += this->data.at(i)->view() + L" ";
	    }
	    result = result.substr(0, result.length() - 1);*/

		for (token* t : this->data) {
			result += t->view() + L" ";
		}

	    return result;
	}

private:
	std::vector <token*> data;
	int index = 0;
};