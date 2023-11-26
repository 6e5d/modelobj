#ifndef INCLUDEGUARD_MODELOBJ_TRANSFORMH
#define INCLUDEGUARD_MODELOBJ_TRANSFORMH

#include <cglm/cglm.h>

#include "../include/modelobj.h"

void modelobj_transform(Modelobj* model, mat3 t);
void modelobj_scale(Modelobj* model, float k);
void modelobj_translate(Modelobj* model, vec3 d);

#endif
