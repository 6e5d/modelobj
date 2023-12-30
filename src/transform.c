#include <cglm/cglm.h>
#include <math.h>

#include "../include/modelobj.h"

void modelobj(transform)(Modelobj()* model, mat3 t) {
	for (size_t vid = 0; vid < model->v_len; vid += 1) {
		glm_mat3_mulv(t, model->vs[vid], model->vs[vid]);
	}
}

void modelobj(scale)(Modelobj()* model, float k) {
	mat3 m = {0};
	glm_mat3_identity(m);
	glm_mat3_scale(m, k);
	modelobj(transform)(model, m);
}

void modelobj(translate)(Modelobj()* model, vec3 d) {
	for (size_t vid = 0; vid < model->v_len; vid += 1) {
		glm_vec3_add(d, model->vs[vid], model->vs[vid]);
	}
}
