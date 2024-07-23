#include"temp_cal.hpp"

// axis x, y, z
// w->e, n->s, b->t
// The size of the whole container, walls included, is mnp

void update_temp(float** temp, int m, int n, int p, int ite, float* temp_b, float* temp_t, float* temp_w, float* temp_e, float* temp_n, float* temp_s, float d_x, float d_t)
{
    float kappa = 0.6;
    float rho = 1000;
    float c = 4.2;
    float alpha = kappa / c / rho;

    // read buffer & write buffer
    int rb = ite % 2;
    int wb = rb ^ 1;

    for (int i = 1; i < m - 1; i++)
        for (int j = 1; j < n - 1; j++)
        {
            temp[rb][i * n * p + j * p] = temp_b[i * n + j];
            temp[rb][i * n * p + j * p + p - 1] = temp_t[i * n + j];
        }

    for (int j = 1; j < n - 1; j++)
        for (int k = 1; k < p - 1; k++)
        {
            temp[rb][j * p + k] = temp_w[j * p + k];
            temp[rb][(m - 1) * n * p + j * p + k] = temp_e[j * p + k];
        }

    for (int i = 1; i < m - 1; i++)
        for (int k = 1; k < p - 1; k++)
        {
            temp[rb][i * n * p + k] = temp_n[i * p + k];
            temp[rb][i * n * p + (n - 1) * p + k] = temp_s[i * p + k];
        }

    for (int i = 1; i < m - 1; i++)
        for (int j = 1; j < n - 1; j++)
            for (int k = 1; k < p - 1; k++)
            {
                temp[wb][i * n * p + j * p + k] = temp[rb][i * n * p + j * p + k] + d_t * alpha / d_x / d_x * (
                    temp[rb][(i - 1) * n * p + j * p + k] + temp[rb][(i + 1) * n * p + j * p + k] - 2 * temp[rb][i * n * p + j * p + k] +
                    temp[rb][i * n * p + (j - 1) * p + k] + temp[rb][i * n * p + (j + 1) * p + k] - 2 * temp[rb][i * n * p + j * p + k] +
                    temp[rb][i * n * p + j * p + (k - 1)] + temp[rb][i * n * p + j * p + (k + 1)] - 2 * temp[rb][i * n * p + j * p + k]
                    );
            }
}

void test_temp_sim(int m, int n, int p)
{
    // 定义液体初始温度
    float* temp[2];
    temp[0] = (float*)malloc(m * n * p * sizeof(float));
    temp[1] = (float*)malloc(m * n * p * sizeof(float));

    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            for (int k = 0; k < p; k++)
            {
                temp[0][i * n * p + j * p + k] = 300;
                temp[1][i * p * p + j * p + k] = 0;
            }

    // 定义容器壁温度
    float* temp_b, * temp_t, * temp_w, * temp_e, * temp_n, * temp_s;

    temp_b = (float*)malloc(m * n * sizeof(float));
    temp_t = (float*)malloc(m * n * sizeof(float));
    temp_w = (float*)malloc(n * p * sizeof(float));
    temp_e = (float*)malloc(n * p * sizeof(float));
    temp_n = (float*)malloc(m * p * sizeof(float));
    temp_s = (float*)malloc(m * p * sizeof(float));

    for (int i = 1; i < m - 1; i++)
        for (int j = 1; j < n - 1; j++)
        {
            temp_b[i * n + j] = 400;
            temp_t[i * n + j] = 300;
        }

    for (int j = 1; j < n - 1; j++)
        for (int k = 1; k < p - 1; k++)
        {
            temp_w[j * p + k] = 300;
            temp_e[j * p + k] = 300;
        }

    for (int i = 1; i < m - 1; i++)
        for (int k = 1; k < p - 1; k++)
        {
            temp_n[i * p + k] = 300;
            temp_s[i * p + k] = 300;
        }

    for (int ite = 0; ite < 30; ite++)
    {
        update_temp(temp, m, n, p, ite, temp_b, temp_t, temp_w, temp_e, temp_n, temp_s, 0.008, 0.01);

        for (int i = 0; i < m; i++)
        {
            for (int k = 0; k < p; k++)
                printf("%f ", temp[ite % 2][i * n * p + p + k]);
            printf("\n");
        }

        Sleep(2000);
    }
}