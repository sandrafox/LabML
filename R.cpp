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
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        xy[i] = make_pair(x, y);
    }
    double ans = 0., nd = (double) n;
    sort(xy, xy + n);
    for (int i = 0; i < n;) {
        double p = 0., np = 0.;
        int cur_x = xy[i].first;
        vector<double> pys;
        while (i < n && xy[i].first == cur_x) {
            double py = 0.;
            int cur_y = xy[i].second;
            while (i < n && xy[i].second == cur_y && xy[i].first == cur_x) {
                py++;
                i++;
            }
            np += py;
            pys.push_back(py);
            //cout << py << endl;
        }
        for (double py : pys) {
            double pyn = py / np;
            p -= pyn * log(pyn);
        }
        ans += np / nd * p;
    }
    cout.precision(20);
    cout << fixed << ans;
}