/*
examples:

lit pack my-module ;; generate my-module.zip
args:
	type=(mod, lib, exec)
	lit pack src dist/my-module.zip
	zip, tar.gz, ...


lit install <url> <install_path>

lit install https://repo.lit.org/lit/integer.zip $global/lit/int
*/

// #include "minizip/zip.h"