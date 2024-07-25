#pragma once

class path {
public:
	path(std::wstring src) {
		std::wstring session;

		for (auto ch : src) {
			if (ch == L'/') {
				this->data.push_back(session);
				session = L"";
			}
			else {
				session += ch;
			}
		}

		if (session != L"") {
			this->data.push_back(session);
		}

	}

	bool has_next() {
		if (index < this->data.size()) {
			return true;
		}
		else {
			return false;
		}
	}

	std::wstring next() {
		return this->data[index++];
	}

// private:
	std::vector<std::wstring> data;
	int index;
};