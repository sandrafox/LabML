//
// Created by adnin on 19.03.2020.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <utility>

using namespace std;

int main() {
    long long ny, n;
    cin >> ny >> n;
    long xs[n], ys[ny] = {0};
    pair<long, long> xy[n];
    for (int i = 0; i < n; ++i) {
        int y;
        cin >> xs[i] >> y;
        xy[i] = make_pair(y, xs[i]);
        ys[--y]++;
    }
    sort(xs, xs + n);
    sort(xy, xy + n);
    long long all_sum = 0, in_sum = 0;
    for (long long i = 1; i < n; ++i) {
        all_sum += ((long long) xs[i] - (long long) xs[i - 1]) * (n - i) * i;
    }
    all_sum *= 2;
    for (long long i = 0; i < n;) {
        int cur_y = xy[i].first;
        long long cur_x = xy[i].second;
        long long j = 1;
        i++;
        while (i < n && xy[i].first == cur_y) {
            in_sum += ((long long) xy[i].second - cur_x) * j * ((long long) ys[cur_y - 1] - j);
            cur_x = xy[i].second;
            j++;
            i++;
        }
    }
    in_sum *= 2;
    cout << in_sum << endl;
    cout << all_sum - in_sum;
}