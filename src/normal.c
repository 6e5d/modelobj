#include <cglm/cglm.h>
#include <math.h>

#include "../include/modelobj.h"

void modelobj(normal_build)(Modelobj()* model) {
	// for face-normal the number of normal = number of faces
	model->ns = realloc(model->ns, sizeof(float[3]) * model->f_len);
	model->n_len = model->f_len;
	for (size_t fid = 0; fid < model->f_len; fid += 1) {
		Modelobj(Face)* f = &model->fs[fid];
		float* v1 = model->vs[f->vids[0]];
		float* v2 = model->vs[f->vids[1]];
		float* v3 = model->vs[f->vids[2]];
		CglmVec3 va, vb;
		glm_vec3_sub(v2, v1, va);
		glm_vec3_sub(v3, v1, vb);
		glm_vec3_crossn(va, vb, model->ns[fid]);
		f->nids[0] = (int32_t)fid;
		f->nids[1] = (int32_t)fid;
		f->nids[2] = (int32_t)fid;
	}
}

void modelobj(normal_smooth)(Modelobj()* model) {
	float (*new_ns)[3] = calloc(model->v_len, sizeof(float[3]));
	uint32_t *count = calloc(model->v_len, sizeof(uint32_t));
	for (size_t fid = 0; fid < model->f_len; fid += 1) {
		Modelobj(Face)* f = &model->fs[fid];
		for (size_t j = 0; j < 3; j += 1) {
			int32_t vid = f->vids[j];
			int32_t nid = f->nids[j];
			glm_vec3_add(
				model->ns[nid],
				new_ns[vid],
				new_ns[vid]
			);
			// update normal index
			f->nids[j] = vid;
			count[vid] += 1;
		}
	}
	for (size_t vid = 0; vid < model->v_len; vid += 1) {
		for (size_t j = 0; j < 3; j += 1) {
			uint32_t c = count[vid];
			if (c < 3) {
				printf("skip: vid %lu connects <3 faces\n",
					vid);
			}
			glm_vec3_normalize(new_ns[vid]);
		}
	}
	free(count);
	free(model->ns);
	model->ns = new_ns;
	model->n_len = model->v_len;
}
