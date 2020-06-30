//
// Created by adnin on 19.03.2020.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <utility>
#include <ctime>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    clock_t start = clock();
    int m, n;
    cin >> n >> m;
    long double X[n][m + 1], y[n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> X[i][j];
        }
        X[i][m] = 1.;
        cin >> y[i];
    }
    long double w[m + 1] = {0.}, md = (long double) m, t = 1., k = 0.05, nd = (long double) n;
    long double a[n] = {0.};
    long double grad[m + 1] = {0.};
    long double norm[n] = {0.}, c = 0., d = 0.;
    do {

        for (int i = 0; i < n; ++i) {
            a[i] = 0;
            for (int j = 0; j <= m; ++j) {
                a[i] += X[i][j] * w[j];
            }
            a[i] -= y[i];
        }

        for (int i = 0; i <= m; ++i) {
            grad[i] = 0;
            for (int j = 0; j < n; ++j) {
                grad[i] += X[j][i] * a[j];
            }
            grad[i] *= 2 * k / (md * t);
        }
        /*c = 0.;
        d = 0.;
        for (int i = 0; i < n; ++i) {
            norm[i] = 0;
            for (int j = 0; j <= m; ++j) {
                norm[i] += X[i][j] * grad[j];
            }
            c += a[i] * norm[i];
            d += norm[i] * norm[i];
        }
        long double mu = c / (d);*/
        //long double mu = k / t;
        for (int i = 0; i <= m; ++i) {
            //grad[i] *= mu;
            //grad[i] *= (long double) 0.0000000001;
            w[i] -= grad[i];
        }
        /*for (int i = 0; i <= m; ++i) {
            cout << (double) grad[i] << endl;
        }*/
        t++;
    } while ((clock() - start) < 0.5 * CLOCKS_PER_SEC);
    for (int i = 0; i <= m; ++i) {
        printf("%.20f\n", (double) w[i]);
    }
    return 0;
}