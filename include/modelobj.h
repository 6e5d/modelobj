#ifndef INCLUDEGUARD_MODELOBJ
#define INCLUDEGUARD_MODELOBJ

#include <cglm/cglm.h>

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

void modelobj_normal_build(Modelobj* model);
void modelobj_normal_smooth(Modelobj* model);

void modelobj_transform(Modelobj* model, mat3 t);
void modelobj_scale(Modelobj* model, float k);
void modelobj_translate(Modelobj* model, vec3 d);

#endif
