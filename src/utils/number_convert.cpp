#include <string>
#include <map>

unsigned int from(std::wstring src, std::map<wchar_t, int> convert_map, int base) {

	int val = 0;

	for (auto ch : src) {
		val *= base;

		if (convert_map.find(ch) != convert_map.end()) {
			val += convert_map[ch];
		}
		else {
			throw "invalid character";
		}
	}

	return val;
}

std::wstring to(unsigned int val, std::map<int, wchar_t> convert_map, int base) {
	std::wstring result;

	do {
		result.insert(0, 1, convert_map[val % base]);
		val /= base;
	} while (val != 0);

	return result;
}

namespace number_convert {

	unsigned int from_bin(std::wstring src) {
		static std::map<wchar_t, int> map = {
			{ L'0', 0 },
			{ L'1', 1 },
		};

		return from(src, map, 2);
	}

	unsigned int from_oct(std::wstring src) {
		static std::map<wchar_t, int> map = {
			{ L'0', 0 },
			{ L'1', 1 },
			{ L'2', 2 },
			{ L'3', 3 },
			{ L'4', 4 },
			{ L'5', 5 },
			{ L'6', 6 },
			{ L'7', 7 },
		};

		return from(src, map, 8);
	}

	unsigned int from_dec(std::wstring src) {
		static std::map<wchar_t, int> map = {
			{ L'0', 0 },
			{ L'1', 1 },
			{ L'2', 2 },
			{ L'3', 3 },
			{ L'4', 4 },
			{ L'5', 5 },
			{ L'6', 6 },
			{ L'7', 7 },
			{ L'8', 8 },
			{ L'9', 9 },
		};

		return from(src, map, 10);
	}

	unsigned int from_hex(std::wstring src) {
		static std::map<wchar_t, int> map = {
			{ L'0', 0 },
			{ L'1', 1 },
			{ L'2', 2 },
			{ L'3', 3 },
			{ L'4', 4 },
			{ L'5', 5 },
			{ L'6', 6 },
			{ L'7', 7 },
			{ L'8', 8 },
			{ L'9', 9 },

			{ L'a', 10 },
			{ L'A', 10 },
			{ L'b', 11 },
			{ L'B', 11 },
			{ L'c', 12 },
			{ L'C', 12 },
			{ L'd', 13 },
			{ L'D', 13 },
			{ L'e', 14 },
			{ L'E', 14 },
			{ L'f', 15 },
			{ L'F', 15 },

		};

		return from(src, map, 16);
	}

	std::wstring to_bin(unsigned int val) {
		static std::map<int, wchar_t> map = {
			{ 0, L'0' },
			{ 1, L'1' },
		};

		return to(val, map, 2);
	}

	std::wstring to_oct(unsigned int val) {
		static std::map<int, wchar_t> map = {
			{ 0, L'0' },
			{ 1, L'1' },
			{ 2, L'2' },
			{ 3, L'3' },
			{ 4, L'4' },
			{ 5, L'5' },
			{ 6, L'6' },
			{ 7, L'7' },
		};

		return to(val, map, 8);
	}

	std::wstring to_dec(unsigned int val) {
		static std::map<int, wchar_t> map = {
			{ 0, L'0' },
			{ 1, L'1' },
			{ 2, L'2' },
			{ 3, L'3' },
			{ 4, L'4' },
			{ 5, L'5' },
			{ 6, L'6' },
			{ 7, L'7' },
			{ 8, L'8' },
			{ 9, L'9' },
		};

		return to(val, map, 10);
	}

	std::wstring to_hex(unsigned int val) {
		static std::map<int, wchar_t> map = {
			{ 0, L'0' },
			{ 1, L'1' },
			{ 2, L'2' },
			{ 3, L'3' },
			{ 4, L'4' },
			{ 5, L'5' },
			{ 6, L'6' },
			{ 7, L'7' },
			{ 8, L'8' },
			{ 9, L'9' },
			{ 10, L'A' },
			{ 11, L'B' },
			{ 12, L'C' },
			{ 13, L'D' },
			{ 14, L'E' },
			{ 15, L'F' },
		};

		return to(val, map, 16);
	}

};