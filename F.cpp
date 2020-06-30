//
// Created by adnin on 22.03.2020.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <utility>
#include <ctime>
#include <cstdlib>
#include <map>
#include <set>

using namespace std;

double likelyhood(double w, double alpha, double v, double c) {
    return (w + alpha) / (c + alpha * v);
}

int main() {
    double E = 2.7182818284590;
    int k, n, m;
    cin >> k;
    double lambda[k], alpha, unique = 0., all[k] = {0.}, count[k] = {0.};
    for (int i = 0; i < k; ++i) {
        cin >> lambda[i];
    }
    cin >> alpha;
    cin >> n;
    map<string, double> dictionary[k];
    map<string, vector<double>>::iterator it;
    vector<double>::iterator itv;
    for (int i = 0; i < n; ++i) {
        int cl;
        double l;
        cin >> cl >> l;
        cl--;
        count[cl]++;
        set<string> message;
        for (int j = 0; j < l; ++j) {
            string doc;
            cin >> doc;
            message.insert(doc);
            /*it = dictionary.find(doc);
            if (it != dictionary.end()) {
                (it->second)[cl]++;
            } else {
                unique++;
                //cout << "Create vector\n";
                vector<double> v(k, 0.);
                //cout << "Add value\n";
                v[cl]++;
                //cout << "Add to dictionary\n";
                dictionary[doc] = v;
            }*/
        }
        for (string doc : message) {
            dictionary[cl][doc]++;
        }
        //all[cl] += message.size();
    }
    /*for (it = dictionary.begin(); it != dictionary.end(); ++it) {
        cout << it->first << ": ";
        vector<double> v = it->second;
        for (itv = v.begin(); itv != v.end(); ++itv) {
            cout << *itv << " ";
        }
        cout << endl;
    }*/
    for (int i = 0; i < k; ++i) {
        all[i] = dictionary[i].size();
    }
    cin >> m;
    vector<vector<double>> ans(m);
    for (int i = 0; i < m; ++i) {
        int l;
        cin >> l;
        vector<double> cur_ans(k, 1.);
        set<string> message;
        for (int j = 0; j < l; ++j) {
            string doc;
            cin >> doc;
            /*it = dictionary.find(doc);
            if (it == dictionary.end()) {
                vector<double> v(k, 0.);
                dictionary[doc] = v;
            }
            for (int t = 0; t < k; ++t) {
                cur_ans[t] *= likelyhood(dictionary[doc][t], alpha, unique, count[t]);
            }*/
            message.insert(doc);
        }
        for (int j = 0; j < k; ++j) {
            cur_ans[j] = log(lambda[j]) + log(count[j] / (double) n);
            for (string doc : message) {
                cur_ans[j] += log((dictionary[j][doc] + alpha) / (count[j] + alpha * all[j]));
            }
        }
        /*for (int j = 0; j < k; ++j) {
            cout << cur_ans[j] << " ";
        }
        cout << endl;*/
        double shift = 0.;
        for (double a : cur_ans) {
            shift = min(shift, a);
        }
        double s = 0;
        for (int j = 0; j < k; ++j) {
            if (abs(cur_ans[j]) < 0.00000001) {
                cur_ans[j] = 0.;
            } else {
                cur_ans[j] = pow(E, (cur_ans[j] - shift));
            }
            s += cur_ans[j];
        }
        for (int j = 0; j < k; ++j) {
            cur_ans[j] /= s;
        }
        ans[i] = cur_ans;
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < k; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}