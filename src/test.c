#include <assert.h>
#include <stdio.h>
#include <unistd.h>

#include "../include/modelobj.h"

int main(int argc, char **argv) {
	assert(argc >= 2);
	Modelobj model;
	modelobj_load_file(&model, argv[1]);
	FILE* fp = fdopen(STDOUT_FILENO, "w");
	modelobj_dump(fp, &model);
	modelobj_debug_print(&model);
	modelobj_deinit(&model);
}
