

#define ARGLIB_IMPLEMENTATION
#include "../arglib.h"

#include <stdio.h>

int main(){

	int argc = 4;
	const char* argv[] = {"./bin/arglib.exe", "-h", "--param", "42"};

	arglib_init();
	arglib_add_option('p', NULL, "Test parameter", ARG_FLOAT, ARG_OPT);
	arglib_add_option('v', "verbose", "Print extra info", ARG_FLAG, ARG_OPT);

	if (!arglib_parse(argc, argv)) return 1;

	double* param = (double*)arglib_get_value("param");
	if(param) printf("Float param is %g\n", *param);
	if (arglib_get_value("v")) printf("Verbose is ON");

	arglib_free();

	return 0;
}
