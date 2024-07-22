#pragma once

#include "./expr.hpp"

class expr_entity : public expr {
public:
	expr_entity(int begin, int end) : expr(begin, end) {};
};