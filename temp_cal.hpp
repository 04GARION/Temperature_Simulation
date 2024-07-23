#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

// axis x, y, z
// w->e, n->s, b->t
// The size of the whole container, walls included, is mnp

void update_temp(float** temp, int m, int n, int p, int ite, float* temp_b, float* temp_t, float* temp_w, float* temp_e, float* temp_n, float* temp_s, float d_x, float d_t);

void test_temp_sim(int m, int n, int p);