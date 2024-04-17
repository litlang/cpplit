#pragma once

namespace number_convert {

	unsigned int from_bin(std::wstring src);
	unsigned int from_oct(std::wstring src);
	unsigned int from_dec(std::wstring src);
	unsigned int from_hex(std::wstring src);

	std::wstring to_bin(unsigned int val);
	std::wstring to_oct(unsigned int val);
	std::wstring to_dec(unsigned int val);
	std::wstring to_hex(unsigned int val);

};