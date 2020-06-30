//
// Created by adnin on 04.03.2020.
//
#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
    int n;
    cin >> n;
    pair<int, int> x[n], y[n];
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        x[i] = make_pair(a, i);
        y[i] = make_pair(b, i);
    }
    sort(x, x + n);
    sort(y, y + n);
    int r[n], s[n];
    for (int i = 0; i < n; ++i) {
        r[x[i].second] = i + 1;
        s[y[i].second] = i + 1;
    }
    double a = 0;
    for (int i = 0; i < n; ++i) {
        double d = (double) r[i] - (double) s[i];
        a += d * d;
        //cout << r[i] << " " << s[i] << endl;
    }
    double nd = (double) n;
    double ans = 1. - a * 6. / (nd * (nd - 1) * (nd + 1));
    cout.precision(9);
    cout << ans;
}
