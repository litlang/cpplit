#pragma once

#include <codecvt>
#include <locale>

enum class coding {

	ASCII,
	UTF_8,
	UTF_16, //? &include multi-name(?)?
};

static std::wstring to_wstring(std::string src, coding Coding = coding::UTF_8) {
	std::wstring result;

	if (Coding == coding::ASCII || Coding == coding::UTF_8) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter; // std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    	result = converter.from_bytes(src);
	}
	return result;
}

static std::string to_string(std::wstring src, coding Coding = coding::UTF_8) {
	std::string result;

	if (Coding == coding::UTF_8) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
		result = converter.to_bytes(src);
	}
	else {
		throw "unsupport coding";
	}
	return result;
}