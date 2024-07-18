#include <string>

#include "helper/helper.hpp"
#include "helper/version.hpp"

void help(losh command) {
	bool version = command.has_bool(L"v") || command.has_bool(L"version");
	// std::wstring lang = command
	// color

	if (version) {
		help_version(command);
	}
	else {
		//
	}
}

/*
site: lit.org
version
contact
commands
*/