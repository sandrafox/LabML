//
// Created by adnin on 20.03.2020.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <utility>
#include <ctime>
#include <cstdlib>

using namespace std;

 double max( double a,  double b) {
    return (a < b) ? b : a;
}

 double min( double a,  double b) {
    return (a > b) ? b : a;
}

int main() {
    srand((unsigned)time(0));
    clock_t start = clock();
    int n;
    cin >> n;
     double K[n][n], y[n], c;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> K[i][j];
        }
        cin >> y[i];
    }
    cin >> c;
     double a[n] = {0.}, b = 0., eps = 0.00000001;
    bool changed;
    int not_changed = 0;
    do {
        changed = false;
        for (int i = 0; i < n; ++i) {
             double e = b - y[i];
            for (int j = 0; j < n; ++j) {
                e += a[j] * y[j] * K[j][i];
            }
            if (((y[i] * e < -eps) && (a[i] < c)) || ((y[i] * e > eps) && (a[i] > 0.))) {
                int j = rand() % n;
                while (i == j) j = (j + 3) % n;
                 double ej = b - y[j];
                for (int t = 0; t < n; ++t) {
                    ej += a[t] * y[t] * K[t][j];
                }
                 double ai = a[i], aj = a[j], l = 0., h = 0.;
                if (y[i] != y[j]) {
                    l = max(0, aj - ai);
                    h = min(c, c + aj - ai);
                } else {
                    l = max(0, ai + aj - c);
                    h = min(c, ai + aj);
                }
                if (abs(l - h) < eps) continue;
                 double etha = 2. * K[i][j] - K[i][i] - K[j][j];
                if (etha >= 0) continue;
                a[j] -= y[j] * (e - ej) / etha;
                a[j] = min(h, a[j]);
                a[j] = max(l, a[j]);
                if (abs(a[j] - aj) < eps) continue;
                a[i] += y[i] * y[j] * (aj - a[j]);
                 double b1 = b - e - y[i] * (a[i] - ai) *
                        K[i][i] - y[j] * (a[j] - aj) * K[i][j],
                       b2 = b - ej - y[i] * (a[i] - ai) *
                               K[i][j] - y[j] * (a[j] - aj) *
                               K[j][j];
                if ((0. < a[i]) && (a[i] < c))  {
                    b = b1;
                    //cout << "b1\n";
                }
                else if ((0. < a[j]) && (a[j] < c)) {
                    b = b2;
                    //cout << "b2\n";
                }
                else {
                    b = (b1 + b2) / 2.;
                    //cout << "medium\n";
                }
                changed = true;
            }
        }
        /*for (int i = 0; i < n; ++i) {
            printf("%.7f\n", a[i]);
        }
        printf("%.7f\n\n", b);*/
        if (!changed) not_changed++;
        else not_changed = 0;
    } while (not_changed <= 5);
    for (int i = 0; i < n; ++i) {
        printf("%.7f\n", (double) a[i]);
    }
    printf("%.7f", (double) b);
    return 0;
}