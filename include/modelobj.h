#include <cglm/cglm.h>

typedef struct {
	float color[4];
	int32_t vids[3];
	int32_t uids[3];
	int32_t nids[3];
	int32_t texlayer;
} Modelobj(Face);

typedef struct {
	size_t v_len;
	float (*vs)[3];
	size_t u_len;
	float (*us)[2];
	size_t n_len;
	float (*ns)[3];
	size_t f_len;
	Modelobj(Face) *fs;
} Modelobj();

void modelobj(load)(Modelobj()* model, char* buf);
void modelobj(load_file)(Modelobj()* model, char* path);
void modelobj(deinit)(Modelobj()* model);
void modelobj(dump)(FILE* fp, Modelobj()* model);
void modelobj(debug_print)(Modelobj()* model);

void modelobj(normal_build)(Modelobj()* model);
void modelobj(normal_smooth)(Modelobj()* model);

void modelobj(transform)(Modelobj()* model, mat3 t);
void modelobj(scale)(Modelobj()* model, float k);
void modelobj(translate)(Modelobj()* model, vec3 d);
