#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../vector/include/vector.h"
#include "../include/modelobj.h"
#include "../include/parser.h"

void parser_init(ParserState* state) {
	vector_init(&state->vs, sizeof(float[3]));
	vector_init(&state->ns, sizeof(float[3]));
	vector_init(&state->us, sizeof(float[2]));
	vector_init(&state->fs, sizeof(ModelobjFace));
}

void parser_deinit(ParserState* state) {
	vector_deinit(&state->vs);
	vector_deinit(&state->ns);
	vector_deinit(&state->us);
	vector_deinit(&state->fs);
}

static const char ws[] = " \t";

static uint8_t parse_line_face(ObjLine* result, char* saveptr) {
	result->c = 'f';
	for (size_t i = 0; i < 3; i += 1) {
		char* word = strtok_r(NULL, ws, &saveptr);
		if (word == NULL) {
			return 3;
		}
		char* saveptr2;
		char* idx;
		// first
		idx = strtok_r(word, "/", &saveptr2);
		if (idx == NULL) {
			// v cannot be empty
			return 3;
		}
		result->data.f[0][i] = atoi(idx);
		// second
		idx = strtok_r(NULL, "/", &saveptr2);
		if (idx == NULL) {
			continue;
		}
		result->data.f[1][i] = atoi(idx);
		// third
		idx = strtok_r(NULL, "/", &saveptr2);
		if (idx == NULL) {
			continue;
		}
		result->data.f[2][i] = atoi(idx);
	}
	return 0;
}

// 1 empty line
// 2 unknown object type
// 3 parse failed
static uint8_t parse_line(ObjLine* result, char* line) {
	char* saveptr;
	char* p = strtok_r(line, ws, &saveptr);
	if (p == NULL) {
		// empty line
		return 1;
	}
	if (0 == strcmp(p, "v")) {
		result->c = 'v';
		for (size_t i = 0; i < 3; i += 1) {
			char* word = strtok_r(NULL, ws, &saveptr);
			if (word == NULL) {
				return 3;
			}
			result->data.v[i] = (float)atof(word);
		}
	} else if (0 == strcmp(p, "vt")) {
		result->c = 'u';
		for (size_t i = 0; i < 2; i += 1) {
			char* word = strtok_r(NULL, ws, &saveptr);
			if (word == NULL) {
				return 3;
			}
			result->data.v[i] = (float)atof(word);
		}
	} else if (0 == strcmp(p, "vn")) {
		result->c = 'n';
		for (size_t i = 0; i < 3; i += 1) {
			char* word = strtok_r(NULL, ws, &saveptr);
			if (word == NULL) {
				return 3;
			}
			result->data.v[i] = (float)atof(word);
		}
	} else if (0 == strcmp(p, "f")) {
		return parse_line_face(result, saveptr);
	} else {
		return 2;
	}
	return 0;
}

void parse_step(ParserState *state, char* line) {
	ObjLine oline = {0};
	switch (parse_line(&oline, line)) {
		case 1:
			return;
		case 2:
			printf("skip unknown object: %s\n", line);
			return;
		case 3:
			printf("parse failed: %s\n", line);
			return;
	}
	switch (oline.c) {
	case 'v':
		vector_pushback(&state->vs, &oline.data.v);
		break;
	case 'n':
		vector_pushback(&state->ns, &oline.data.n);
		break;
	case 'u':
		vector_pushback(&state->us, &oline.data.u);
		break;
	case 'f': {
		ModelobjFace f = {0};
		for (size_t i = 0; i < 3; i++) {
			f.vids[i] = oline.data.f[0][i] - 1;
			f.nids[i] = oline.data.f[1][i] - 1;
			f.uids[i] = oline.data.f[2][i] - 1;
		}
		vector_pushback(&state->fs, &f);
		break;
	}
	default:
		printf("BUG: unknown line type %c\n", oline.c);
		abort();
	}
}

void build_model(Modelobj* model, ParserState* state) {
	model->v_len = vector_unwrap(&state->vs, (void**)&model->vs);
	model->n_len = vector_unwrap(&state->ns, (void**)&model->ns);
	model->u_len = vector_unwrap(&state->us, (void**)&model->us);
	model->f_len = vector_unwrap(&state->fs, (void**)&model->fs);
}
