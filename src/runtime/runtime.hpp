#pragma once

#include <filesystem>

#include "project.hpp"
#include "language.hpp"

struct runtime {
	std::wstring filepath;
	std::filesystem::path working_directory;
	library* external_library; // import_lib

	struct {
		language lang;
	} debug;
};