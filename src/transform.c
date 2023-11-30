#include <cglm/cglm.h>
#include <math.h>

#include "../include/modelobj.h"

void modelobj_transform(Modelobj* model, mat3 t) {
	for (size_t vid = 0; vid < model->v_len; vid += 1) {
		glm_mat3_mulv(t, model->vs[vid], model->vs[vid]);
	}
}

void modelobj_scale(Modelobj* model, float k) {
	mat3 m = {0};
	glm_mat3_identity(m);
	glm_mat3_scale(m, k);
	modelobj_transform(model, m);
}

void modelobj_translate(Modelobj* model, vec3 d) {
	for (size_t vid = 0; vid < model->v_len; vid += 1) {
		glm_vec3_add(d, model->vs[vid], model->vs[vid]);
	}
}
