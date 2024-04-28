#include <string>
#include <vector>
#include <map>

#include "scanner/scanner.hpp"
#include "scanner/scan_string.hpp"

#include "utils/coding.hpp"
#include "reader/reader.hpp"

#include "tokens/tokens.hpp"
#include "tokens/keyword.hpp"
#include "tokens/symbol.hpp"

#include "utils/numcvt.hpp"
#include "exceptions/lex_errors.hpp"

#include "utils/ranges.hpp"
#include "utils/null.hpp"

#include "utils/position.hpp"
#include "scanner/trie.hpp"

ranges identifier_charset = {

	{ 65, 90 },  // A-Z
	{ 97, 122 }, // a-z
	{ 95, 95 },  // _
	// { 36, 36 },  // $
	{ 48, 57 },  // 0-9
	{ 32, 32 },  // ␣

	{ 0x4E00, 0x9FFF }, // chinese characters

};

ranges digit_charset = {
	{ 48, 57 },
};

std::map<std::wstring, token_keyword::type> keyword_map = {

// en-us
	{ L"import", token_keyword::type::IMPORT },
	{ L"if", token_keyword::type::IF },
	{ L"else if", token_keyword::type::ELSE_IF },
	{ L"else", token_keyword::type::ELSE },
	{ L"loop", token_keyword::type::LOOP },
	{ L"func", token_keyword::type::FUNC },
	{ L"class", token_keyword::type::CLASS },
	{ L"namespace", token_keyword::type::NAMESPACE },
	{ L"enum", token_keyword::type::ENUM },
	{ L"try", token_keyword::type::TRY },
	{ L"catch", token_keyword::type::CATCH },

// zh-cn
	{ L"导入", token_keyword::type::IMPORT },
	{ L"如果", token_keyword::type::IF },
	{ L"若", token_keyword::type::IF },
	{ L"又如果", token_keyword::type::ELSE_IF },
	{ L"否则", token_keyword::type::ELSE },
	{ L"循环", token_keyword::type::LOOP },
	{ L"函数", token_keyword::type::FUNC },
	{ L"类", token_keyword::type::CLASS },
	{ L"命名空间", token_keyword::type::NAMESPACE },
	{ L"枚举", token_keyword::type::ENUM },
	{ L"尝试", token_keyword::type::TRY },
	{ L"捕获", token_keyword::type::CATCH },

};

std::map<std::wstring, bool> literal_bool_map = {

// en-us
	{ L"true", true },
	{ L"false", false },

// zh-cn
	{ L"真", true },
	{ L"假", false },

};

trie<token_symbol::type> symbol_map = {

// 通用

	{ L"@", token_symbol::type::AT },
	{ L"?", token_symbol::type::QUESTION },
	{ L"!", token_symbol::type::NOT },
	{ L"&", token_symbol::type::AND },
	{ L"|", token_symbol::type::OR },
	{ L"\\", token_symbol::type::XOR },
	{ L"&&", token_symbol::type::AND_AND },
	{ L"||", token_symbol::type::OR_OR },
	{ L"\\\\", token_symbol::type::XOR_XOR },

	{ L"+", token_symbol::type::PLUS },
	{ L"-", token_symbol::type::MINUS },
	{ L"*", token_symbol::type::ASTERISK },
	{ L"/", token_symbol::type::SLASH },
	{ L"^", token_symbol::type::CARET },
	{ L"^/", token_symbol::type::CARET_SLASH },
	{ L"%", token_symbol::type::PERCENT },


	{ L".", token_symbol::type::DOT },
	{ L",", token_symbol::type::COMMA },
	{ L":", token_symbol::type::COLON },
	{ L";", token_symbol::type::SEMICOLON },
	{ L"(", token_symbol::type::PAREN_LEFT },
	{ L")", token_symbol::type::PAREN_RIGHT },
	{ L"[", token_symbol::type::BRACKET_LEFT },
	{ L"]", token_symbol::type::BRACKET_RIGHT },
	{ L"{", token_symbol::type::BRACE_LEFT },
	{ L"}", token_symbol::type::BRACE_RIGHT },
	{ L"<<", token_symbol::type::ANGLE_BRACKET_LEFT },
	{ L">>", token_symbol::type::ANGLE_BRACKET_RIGHT },

	{ L">", token_symbol::type::GREATER },
	{ L"<", token_symbol::type::LESS },
	{ L">=", token_symbol::type::GREATER_EQUAL },
	{ L"≥", token_symbol::type::GREATER_EQUAL },
	{ L"<=", token_symbol::type::LESS_EQUAL },
	{ L"≤", token_symbol::type::LESS_EQUAL },
	{ L"==", token_symbol::type::EQUAL_EQUAL },
	{ L"!=", token_symbol::type::NOT_EQUAL },
	{ L"≠", token_symbol::type::NOT_EQUAL },

	{ L"->", token_symbol::type::SINGLE_ARROW },
	{ L"=>", token_symbol::type::DOUBLE_ARROW },
/*	{ L"!->", token_symbol::type::NOT_BELONG },
	{ L"!=>", token_symbol::type::NOT_SUB },*/

	{ L"=", token_symbol::type::EQUAL },
	{ L"+=", token_symbol::type::PLUS_EQUAL },
	{ L"-=", token_symbol::type::MINUS_EQUAL },
	{ L"*=", token_symbol::type::ASTERISK_EQUAL },
	{ L"/=", token_symbol::type::SLASH_EQUAL },
	{ L"^=", token_symbol::type::CARET_EQUAL },
	{ L"^/=", token_symbol::type::CARET_SLASH_EQUAL },
	{ L"%=", token_symbol::type::PERCENT_EQUAL },

// zh-cn
	{ L"？", token_symbol::type::QUESTION },
	{ L"！", token_symbol::type::NOT },

	{ L"，", token_symbol::type::COMMA },
	{ L"：", token_symbol::type::COLON },
	{ L"；", token_symbol::type::SEMICOLON },
	{ L"（", token_symbol::type::PAREN_LEFT },
	{ L"）", token_symbol::type::PAREN_RIGHT },
	{ L"【", token_symbol::type::BRACKET_LEFT },
	{ L"】", token_symbol::type::BRACKET_RIGHT },
	{ L"｛", token_symbol::type::BRACE_LEFT },
	{ L"｝", token_symbol::type::BRACE_RIGHT },
	{ L"《", token_symbol::type::ANGLE_BRACKET_LEFT },
	{ L"》", token_symbol::type::ANGLE_BRACKET_RIGHT },

/*	{ L"！->", token_symbol::type::NOT_BELONG },
	{ L"！=>", token_symbol::type::NOT_SUB }, // replace_list*/

};

trie<null> ignore_set = {
	{ L" ", Null },
	{ L"\t", Null },
};

token_list scan(std::wstring filepath) {

	std::vector<token*> Token_list;
	std::wstring src = read(filepath, coding::UTF_8);

	Token_list.push_back(new token_symbol {token_symbol::type::BOF_, 0, 0});

	int length = src.length();

	for (int i = 0; i < length; ) {

		int begin = i;

		// comments.sharp_comments
		if (src[i] == L'#') {

			do {
				i += 1;
				if (i >= length) {
					throw new unterminated_comments { filepath, position_format(src, i) };
				}
			} while (src[i] != L'#');
			i += 1;
		}

		// comments.single_line
		else if (src.substr(i, 2) == L";;") {
			i += 2;
			while (i < length && src[i] != L'\n') { //
				i += 1;
			}
		}

		// whitespace (ignored character)
		else if (auto _ = ignore_set.search(src, i)) { // `v
			// pass
		}

		// EOL
		else if (src[i] == L'\u000A' || src[i] == L'\u000D' || src[i] == L'\u0085') { // LF || CR || NEL
			do {
				i += 1;				
			} while (src[i] == L'\u000A' || src[i] == L'\u000D' || src[i] == L'\u0085');
			Token_list.push_back(new token_symbol {token_symbol::type::EOL_, begin, i});
		}

		// escape
		else if (src[i] == L'`') {
			i += 1;
			if (src[i] == L'\n') {
				i += 1;
			}
			// else if '`x837' 汉字标识符
			else {
				throw new invalid_escape { filepath, position_format(src, i) };
			}
		}

		// string
		else if (string_head_matched(src[i])) {
			Token_list.push_back(lex_string(src, i, filepath));
		}

		// entity.literal.number
		else if (digit_charset.include(src[i])) {
			int val = cvt_dec(src, i);
			Token_list.push_back(new token_number { val, begin, i });
		}

		// entity.identifier || keyword || literal
		else if (identifier_charset.include(src[i])) {

			std::wstring val;

			do {

				if (src[i] != L' ' || src[i-1] != L' ') {
					val += src[i];
				}
				i += 1;

			} while(i < length && identifier_charset.include(src[i]));

			// remove back spaces
			if (val[val.length()-1] == L' ') {
				val = val.substr(0, val.length()-1);
			}

			if (keyword_map.find(val) != keyword_map.end()) { // is keyword
				Token_list.push_back(new token_keyword { keyword_map[val], begin, i});
			}
			else if (literal_bool_map.find(val) != literal_bool_map.end()) {
				Token_list.push_back(new token_boolean { literal_bool_map[val], begin, i });
			}
			else { // is identifier
				Token_list.push_back(new token_identifier {val, begin, i});
			}

		}

		// token.symbol
		else if (auto val = symbol_map.search(src, i)) {
			Token_list.push_back(new token_symbol { *val, begin, i });
		}

		else {
			throw new invalid_character { filepath, position_format(src, i), src[i] };
		}

	}

	Token_list.push_back(new token_symbol {token_symbol::type::EOF_, length, length});
	return token_list { Token_list };

}