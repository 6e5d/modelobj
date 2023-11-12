#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "../include/modelobj.h"
#include "../include/parser.h"
#include "../../wholefile/include/wholefile.h"

void modelobj_load_file(Modelobj* model, char* path) {
	uint8_t *buf;
	assert(0 != wholefile_read(path, &buf));
	modelobj_load(model, (char *)buf);
	free(buf);
}

void modelobj_load(Modelobj* model, char* buf) {
	ParserState parser;
	parser_init(&parser);
	char *saveptr;
	while(1) {
		char* p = strtok_r(buf, "\n", &saveptr);
		if (NULL == p) {
			break;
		}
		buf = NULL;
		parse_step(&parser, p);
	}
	build_model(model, &parser);
}

void modelobj_deinit(Modelobj* model) {
	free(model->vs);
	free(model->us);
	free(model->ns);
	free(model->fs);
}

void modelobj_debug_print(Modelobj* model) {
	fprintf(stderr, "v:%zu u:%zu n:%zu f:%zu\n",
		model->v_len,
		model->u_len,
		model->n_len,
		model->f_len);
}

void modelobj_dump(FILE* fp, Modelobj* model) {
	size_t i;
	for (i = 0; i < model->v_len; i += 1) {
		fprintf(fp, "v %f %f %f\n",
			(double)model->vs[i][0],
			(double)model->vs[i][1],
			(double)model->vs[i][2]
		);
	}
	for (i = 0; i < model->u_len; i += 1) {
		fprintf(fp, "vt %f %f\n",
			(double)model->us[i][0],
			(double)model->us[i][1]
		);
	}
	for (i = 0; i < model->n_len; i += 1) {
		fprintf(fp, "vn %f %f %f\n",
			(double)model->ns[i][0],
			(double)model->ns[i][1],
			(double)model->ns[i][2]
		);
	}
	for (i = 0; i < model->f_len; i += 1) {
		ModelobjFace *f = &model->fs[i];
		fprintf(fp, "f");
		for (size_t j = 0; j < 3; j += 1) {
			fprintf(fp, " %d/%d/%d",
				f->vids[j] + 1,
				f->uids[j] + 1,
				f->nids[j] + 1
			);
		}
		fprintf(fp, "\n");
	}
}
