#ifndef INCLUDEGUARD_MODELOBJ_PARSERH
#define INCLUDEGUARD_MODELOBJ_PARSERH

#include <stddef.h>
#include <stdint.h>

#include "../../vector/include/vector.h"
#include "../include/modelobj.h"

// the parser store the original value
// i.e. indices in faces start from 1
typedef union {
	float v[3];
	float n[3];
	float u[2];
	int32_t f[3][3];
} ObjLineData;

typedef struct {
	char c;
	ObjLineData data;
} ObjLine;

typedef struct {
	Vector vs;
	Vector ns;
	Vector us;
	Vector fs;
} ParserState;

void parser_init(ParserState* state);
void parser_deinit(ParserState* state);
void parse_step(ParserState *state, char* line);
void build_model(Modelobj* model, ParserState* state);

#endif
