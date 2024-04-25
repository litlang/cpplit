#pragma once

class loop_statement : public statement {
public:
	loop_statement(int begin, int end) : statement(begin, end) {};
};