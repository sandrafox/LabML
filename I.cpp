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

int main() {
    int m;
    cin >> m;
    vector<int> ts;
    for (int i = 0; i < (1 << m); ++i) {
        int x;
        cin >> x;
        if (x) ts.push_back(i);
    }
    if (ts.size() == 0) {
        cout << "1\n1\n";
        for (int i = 0; i < m; ++i) {
            cout << "0 ";
        }
        cout << "-0.5";
    } else {
        cout << "2\n" << ts.size() << " 1\n";
        for (int t : ts) {
            for (int i = 0; i < m; ++i) {
                if ((1 << i) & t) cout << "1 ";
                else cout << "-1 ";
            }
            double c = -((double) __builtin_popcount(t) - 0.5);
            cout << c << endl;
        }
        for (int i = 0; i < ts.size(); ++i) {
            cout << "1 ";
        }
        cout << "-0.5\n";
    }
}