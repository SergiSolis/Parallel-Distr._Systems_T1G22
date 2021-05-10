#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <omp.h>

int main(int argc, char * argv[]) {
    double x0, y0;
    double x, y;
    double xtmp;
    int i, j;
    int iter;
    int **M;

    const double X_MIN = 0.27085;
    const double X_MAX = 0.271;
    const double Y_MIN = 0.004640;
    const double Y_MAX = 0.004810;
    const uint16_t ITER_MAX = 750;
    const int X_RES = 2048;
    const int Y_RES = (X_RES * (Y_MAX - Y_MIN)) / (X_MAX - X_MIN);
    double dx = (X_MAX - X_MIN) / X_RES;
    double dy = (Y_MAX - Y_MIN) / Y_RES;

    double start, end;

    const unsigned char black[] = {0,0,0,0,0,0};
    unsigned char color[6];
    int pixel;

    const char *filename = "mandelbrot.ppm";
    FILE *file;
 
    M = (int**) malloc(Y_RES * sizeof(int*));

    for (int i = 0; i < Y_RES; i++) {
        M[i] = (int*) malloc(X_RES * sizeof(int));
    }

    start = omp_get_wtime();
    #pragma omp parallel for schedule(dynamic)
    for (i = 0; i < Y_RES; i++) {
        y0 = Y_MAX - i * dy;
        for (j = 0; j < X_RES; j++) {
            x = 0.0;
            y = 0.0;
            x0 = X_MIN + j * dx;
            for (iter = 0; (x * x + y * y <= 4.0) && iter < ITER_MAX; iter++) {
                xtmp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xtmp;
            };
            M[i][j] = iter;
        }
    }
    end = omp_get_wtime();
    printf("Mandelbrot took %f sec\n", end - start);

    file = fopen(filename, "wb");
    fprintf(file, "P6 %d %d %d\n", X_RES, Y_RES, (ITER_MAX < 256 ? 256 : ITER_MAX));

    for (i = 0; i < Y_RES; i++) {
        for (j = 0; j < X_RES; j++) {
            pixel = M[i][j];
            if (pixel >= ITER_MAX) {                
                fwrite(black, 6, 1, file);
            } else {
                color[0] = pixel >> 8;
                color[1] = pixel & 255;
                color[2] = pixel >> 8;
                color[3] = pixel & 255;
                color[4] = pixel >> 8;
                color[5] = pixel & 255;
                fwrite(color, 6, 1, file);
            }
        }
    }
    fclose(file);
    return 0;
}
