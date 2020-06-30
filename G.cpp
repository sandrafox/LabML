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

using namespace std;

struct Node {
    int cl;
    int f;
    double v;
    int left;
    int right;
    bool isLeaf;
};

vector<Node> tree(2050);
vector<vector<int>> xs;
vector<int> ys;
int k, m;
int index;
double enthropy[4001];

int build(vector<int> has, int height) {
    vector<int> count(k, 0);
    vector<int>::iterator it;
    bool oneClass = true;
    for (int i = 0; i < has.size() - 1; ++i) {
        count[ys[has[i]]]++;
        oneClass = oneClass && (ys[has[i]] == ys[has[i + 1]]);
    }
    count[ys[has[has.size() - 1]]]++;
    if (height == 0) {
        tree[index].cl = max_element(count.begin(), count.end()) - count.begin();
        tree[index].isLeaf = true;
        /*cout << "end of height: ";
        for (int c : count) cout << c << " ";
        cout << endl;*/
        return index++;
    }
    if (oneClass) {
        tree[index].cl = ys[has[0]];
        tree[index].isLeaf = true;
        /*cout << "one class: ";
        for (int c : count) cout << c << " ";
        cout << endl;*/
        return index++;
    }
    double max_gain = -1e10, max_v = 0.;
    int max_f = -1;
    for (int f = 0; f < m; ++f) {
        sort(has.begin(), has.end(), [&](int i, int j) { return xs[i][f] < xs[j][f];});
        vector<int> count1(k, 0);
        vector<int> count2 = count;
        int p1 = 0, p2 = has.size();
        for (int i = 1; i < has.size(); ++i) {
            count1[ys[has[i - 1]]]++;
            count2[ys[has[i - 1]]]--;
            p1++;
            p2--;
            if (xs[has[i - 1]][f] == xs[has[i]][f]) continue;
            //cout << "p1 = " << log(p1) << " p2 = " << (p2) << endl;
            double gain1 = -(double) p1 * log(p1),
                   gain2 = -(double) p2 * log(p2);
            for (int j = 0; j < k; ++j) {
                /*if (count1[j] != 0)
                gain1 += (double) count1[j] * log(count1[j]);
                if (count2[j] != 0)
                gain2 += (double) count2[j] * log(count2[j]);*/
                gain1 += enthropy[count1[j]];
                gain2 += enthropy[count2[j]];
            }
            //cout << gain1 + gain2 << endl;
            if (gain1 + gain2 > max_gain) {
                max_gain = gain1 + gain2;
                max_v = (double) ((double) xs[has[i - 1]][f] + (double) xs[has[i]][f]) * 0.5;
                max_f = f;
            }
        }
    }
    if (max_f == -1) {
        tree[index].cl = max_element(count.begin(), count.end()) - count.begin();
        tree[index].isLeaf = true;
        /*cout << "can't choose f: ";
        for (int c : count) cout << c << " ";
        cout << endl;*/
        return index++;
    }
    tree[index].f = max_f;
    tree[index].v = max_v;
    tree[index].isLeaf = false;
    int old_index = index;
    index++;
    vector<int> has1, has2;
    for (int i = 0; i < has.size(); ++i) {
        if (xs[has[i]][max_f] < max_v) has1.push_back(has[i]);
        else has2.push_back(has[i]);
    }
    tree[old_index].left = build(has1, height - 1);
    tree[old_index].right = build(has2, height - 1);
    return old_index;
}

int main() {
    int n, h;
    cin >> m >> k >> h >> n;
    xs.resize(n, vector<int>(m));
    ys.resize(n);
    vector<int>has(n);
    enthropy[0] = 0.;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> xs[i][j];
        }
        cin >> ys[i];
        ys[i]--;
        has[i] = i;
        enthropy[i + 1] = (i + 1) * log(i + 1);
    }
    index = 1;
    build(has, h);
    printf("%d\n", index - 1);
    for (int i = 1; i < index; ++i) {
        if (tree[i].isLeaf) {
            printf("C %d\n", tree[i].cl + 1);
        } else {
            printf("Q %d %.7f %d %d\n", tree[i].f + 1, tree[i].v, tree[i].left, tree[i].right);
        }
    }
}