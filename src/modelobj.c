#include "../../wholefile/build/wholefile.h"
#include "../include/modelobj.h"

void modelobj(load_file)(Modelobj()* model, char* path) {
	uint8_t *buf;
	assert(0 != com_6e5d_wholefile_read(path, &buf));
	modelobj(load)(model, (char *)buf);
	free(buf);
}

void modelobj(deinit)(Modelobj()* model) {
	free(model->vs);
	free(model->us);
	free(model->ns);
	free(model->fs);
}

static void chk(int v) {
	if (v < 0) {
		abort();
	}
}

void modelobj(debug_print)(Modelobj()* model) {
	fprintf(stderr, "v:%zu u:%zu n:%zu f:%zu\n",
		model->v_len,
		model->u_len,
		model->n_len,
		model->f_len);
}

void modelobj(dump)(FILE* fp, Modelobj()* model) {
	size_t i;
	for (i = 0; i < model->v_len; i += 1) {
		chk(fprintf(fp, "v %f %f %f\n",
			(double)model->vs[i][0],
			(double)model->vs[i][1],
			(double)model->vs[i][2]
		));
	}
	for (i = 0; i < model->u_len; i += 1) {
		chk(fprintf(fp, "vt %f %f\n",
			(double)model->us[i][0],
			(double)model->us[i][1]
		));
	}
	for (i = 0; i < model->n_len; i += 1) {
		chk(fprintf(fp, "vn %f %f %f\n",
			(double)model->ns[i][0],
			(double)model->ns[i][1],
			(double)model->ns[i][2]
		));
	}
	for (i = 0; i < model->f_len; i += 1) {
		Modelobj(Face) *f = &model->fs[i];
		chk(fprintf(fp, "f"));
		for (size_t j = 0; j < 3; j += 1) {
			chk(fprintf(fp, " %d/%d/%d",
				f->vids[j] + 1,
				f->uids[j] + 1,
				f->nids[j] + 1
			));
		}
		chk(fprintf(fp, "\n"));
	}
}
