#include <cglm/cglm.h>
#include <math.h>

#include "../include/modelobj.h"

void modelobj(transform)(Modelobj()* model, CglmMat3 t) {
	for (size_t vid = 0; vid < model->v_len; vid += 1) {
		glm_mat3_mulv(t, model->vs[vid], model->vs[vid]);
	}
}

void modelobj(scale)(Modelobj()* model, float k) {
	CglmMat3 m = {0};
	glm_mat3_identity(m);
	glm_mat3_scale(m, k);
	modelobj(transform)(model, m);
}

void modelobj(translate)(Modelobj()* model, CglmVec3 d) {
	for (size_t vid = 0; vid < model->v_len; vid += 1) {
		glm_vec3_add(d, model->vs[vid], model->vs[vid]);
	}
}
