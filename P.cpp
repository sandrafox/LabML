//
// Created by adnin on 18.03.2020.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <utility>

using namespace std;

int main() {
    int n, nx;
    cin >> nx >> n;
    double xs[nx] = {0.}, ey[nx] = {0.}, ey2[nx] = {0.};
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        xs[--x]++;
        ey[x] += y;
        ey2[x] += y * y;
    }
    double ans = 0., nd = (double) n;
    for (int i = 0; i < nx; ++i) {
        if (xs[i] != 0) {
            ey[i] /= xs[i];
            ey2[i] /= xs[i];
            ans += (ey2[i] - ey[i] * ey[i]) * xs[i] / nd;
        }
    }
    cout.precision(20);
    cout << fixed << ans;
}