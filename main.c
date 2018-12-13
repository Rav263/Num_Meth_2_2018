#include <stdlib.h>
#include <stdio.h>
#include <math.h>

double f_1(double x, double y) {
    return x + y;
}

double f_2(double x, double y) {
    return sin(x) - y;
}

double check_f_2(double x) {
    return 0.5 * (sin(x) - cos(x)) + 10.5 * exp(-x);
}


void print_string(double x, double *y, int n, int accur) {
    printf("%*.*lf;", accur + 3, accur, x);

    for (int i = 0; i < n; i++) {
        printf("%*.*lf; %*.*lf;", accur + 3, accur, y[i], accur + 3, accur, check_f_2(x));
    }

    printf("\n");
}



double next_iter_2(double y, double x, double h, double (*func)(double, double)) {
    double tmp_y = y + func(x, y) * h;
    double tmp = func(x, y) + func(x + h, tmp_y);
    tmp /= 2;
    return y + tmp * h;
}


void runge_kutt_2(double x, double *y, int n, int accur, int max_iter, double h) {
    double tmp_x = x;
    for (int i = 0; i < max_iter; i++) {
        for (int j = 0; j < n; j++) {
            y[j] = next_iter_2(y[j], tmp_x, h, f_2);
        }

        tmp_x += h;

        print_string(tmp_x, y, n, accur);
    }
}

double count_coofs(double x, double y, double h, double (*func)(double, double)) {
    double k1 = func(x, y);
    double k2 = func(x + (h / 2), y + (h / 2) * k1);
    double k3 = func(x + (h / 2), y + (h / 2) * k2);
    double k4 = func(x + h, y + h * k3);

    return (h / 6) * (k1 + 2 * k2 + 2 * k3 + k4);
}


void runge_kutt_4(double x, double *y, double h, int n, int accur, int max_iter) {
    for (int i = 0; i < max_iter; i++) {
        for (int j = 0; j < n; j++) {
            double coof = count_coofs(x, y[j], h, f_2);
            y[j] = y[j] + coof;
        }

        x += h;

        print_string(x, y, n, accur);
    }
}


int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int max_iter = atoi(argv[2]);
    double h = atof(argv[3]);
    int accur = atoi(argv[4]);

    double y[] = {10};

    runge_kutt_4(0, y, h, n, accur, max_iter);
}
