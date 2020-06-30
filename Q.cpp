//
// Created by adnin on 17.03.2020.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <utility>

using namespace std;

int main() {
    int nx, ny, n;
    cin >> nx >> ny >> n;
    pair<int, int> xy[n];
    double xs[nx] = {0.}, ys[ny] = {0.};
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        xy[i] = make_pair(x, y);
        xs[--x]++;
        ys[--y]++;
    }
    double ans = 0., nd = (double) n, nu = (double) n;
    sort(xy, xy + n);
    for (int i = 0; i < n;) {
        int cur_x = xy[i].first;
        while (i < n && xy[i].first == cur_x) {
            double py = 0.;
            int cur_y = xy[i].second;
            while (i < n && xy[i].second == cur_y && xy[i].first == cur_x) {
                py++;
                i++;
            }
            double at = xs[cur_x - 1] * ys[cur_y - 1] / nd, tmp = py - at;
            //cout << at << " " << py << endl;
            ans += tmp * tmp / at;
            nu -= at;
        }
    }
    cout.precision(20);
    cout << fixed << ans + nu;
}