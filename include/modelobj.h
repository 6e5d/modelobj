#ifndef INCLUDEGUARD_MODELOBJ_MODELOBJH
#define INCLUDEGUARD_MODELOBJ_MODELOBJH

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

typedef struct {
	float color[4];
	int32_t vids[3];
	int32_t uids[3];
	int32_t nids[3];
	int32_t texlayer;
} ModelobjFace;

typedef struct {
	size_t v_len;
	float (*vs)[3];
	size_t u_len;
	float (*us)[2];
	size_t n_len;
	float (*ns)[3];
	size_t f_len;
	ModelobjFace *fs;
} Modelobj;

void modelobj_load(Modelobj* model, char* buf);
void modelobj_load_file(Modelobj* model, char* path);
void modelobj_deinit(Modelobj* model);
void modelobj_dump(FILE* fp, Modelobj* model);
void modelobj_debug_print(Modelobj* model);

#endif
