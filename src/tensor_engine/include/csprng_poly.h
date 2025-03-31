#pragma once

#include "lattica_tensor_defs.h"

void init_sodium();
void generate_random_int64_tensor(TTensor& tensor, int64_t q);
void generate_random_int32_tensor(TTensor& tensor, int32_t low, int32_t high);
std::pair<float, float> boxMullerTransform(uint32_t r1, uint32_t r2);
void generate_random_normal_tensor(TTensor& tensor, float mean, float std);