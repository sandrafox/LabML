#include <iostream>
#include <string>
#include <cmath>
#include <utility>
#include <algorithm>

using namespace std;

const double _PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679;

double triangular(double u) {
    if (u >= 1) return 0;
    return 1. - u;
}


double epanechikov( double u) {
    if (u >= 1) return 0;
    return 3. * (1. - pow(u, 2.)) / 4.;
}


double quartic(double u) {
    if (u >= 1) return 0;
    return 15. * pow((1 - u * u), 2.) / 16.;
}


double triweight(double u) {
    if (u >= 1) return 0;
    return 35. * pow((1. - u * u), 3.) / 32.;
}


double tricube(double u) {
    if (u >= 1) return 0;
    return 70. * pow((1. - u * u * u) , 3.) / 81.;
}


double gaussian(double u) {
    return 1. / sqrt(2. * _PI) * exp(-(u * u) / 2.);
}


double cosine(double u) {
    if (u >= 1) return 0;
    return _PI / 4. * cos(u * _PI / 2.);
}


double logistic(double u) {
    return 1. / (exp(u) + 2. + exp(-u));
}


double sigmoid(double u) {
    return 2. / _PI * 1. / (exp(u) + exp(-u));
}


double uniform(double u) {
    if (u >= 1) return 0;
    return 0.5;
}


double funck(string name, double r) {
    if (name == "uniform") return uniform(r);
    if (name == "triangular") return triangular(r);
    if (name == "epanechnikov") return epanechikov(r);
    if (name == "quartic") return quartic(r);
    if (name == "triweight") return triweight(r);
    if (name == "tricube") return tricube(r);
    if (name == "gaussian") return gaussian(r);
    if (name == "cosine") return cosine(r);
    if (name == "logistic") return logistic(r);
    if (name == "sigmoid") return sigmoid(r);
}

int main() {
    int n, m;
    cin >> n >> m;
    int objs[n][m], k[m];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> objs[i][j];
        }
        cin >> k[i];
    }
    int q[m];
    for (int i  = 0; i < m; ++i) {
        cin >> q[i];
    }
    string distance;
    cin >> distance;
    pair<double, double> dobjs[n];
    if (distance == "manhattan")
    {
        for (int j = 0; j < n; ++j) {
            double r = 0;
            for (int i = 0; i < m; ++i) {
                r += fabs((double)objs[j][i] - (double) q[i]);
            }
            dobjs[j] = make_pair(r, (double) k[j]);
        }
    }
    else if (distance == "euclidean") {
        for (int j = 0; j < n; ++j) {
        double r = 0;
        for (int i = 0; i < m; ++i) {
            r += pow(((double) objs[j][i] - (double) q[i]), 2);
        }
        r = sqrt(r);
        dobjs[j] = make_pair(r, (double) k[j]);
        }
    }
    else {
        for (int j = 0; j < n; ++j) {
            double r = 0;
            for (int i = 0; i < m; ++i) {
                double ri = fabs((double) objs[j][i] - (double) q[i]);
                if (ri > r) r = ri;
            }
            dobjs[j] = make_pair(r, (double) k[j]);
        }
    }
    sort(dobjs, dobjs + n);
    string kernel;
    cin >> kernel;
    string window;
    cin >> window;
    int h_;
    cin >> h_;
    /*for (int i = 0; i < n; ++i) {
        cout << dobjs[i].first << " ";
    }
    cout << endl;*/
    double a = 0, b = 0;
    double h = (double) h_;

    if (window == "fixed") {
        if (h_ == 0) {
            for (int i = 0; i < n; ++i) {
                if (dobjs[i].first > 0) break;
                double c = funck(kernel, 0.);
                a += dobjs[i].second * c;
                b += c;
            }
        }
        for (int i = 0; i < n; ++i) {
            //cout << dobjs[i].first / h << " ";
            double c = funck(kernel, dobjs[i].first / h);
            a += dobjs[i].second * c;
            b += c;
            //cout << c << endl;
        }
    }
    else {
        pair<double, double> pk = dobjs[h_ - 1];
        double dist = pk.first;
        bool changed = false;
        int j = h_;
        for (; j < n; ++j) {
            double tmp = dobjs[j].first;
            if (tmp > dist) {
                changed = true;
                dist = tmp;

                break;
            }
        }
        if (!changed) {
            dist = nextafter(dist, numeric_limits <double> :: max());
        } else {
            dist = dobjs[h_].first;
        }
        if (dist == 0.) {
            for (int i = 0; i < j; ++i) {
                if (dobjs[i].first > 0) break;
                double c = funck(kernel, 0.);
                a += dobjs[i].second * c;
                b += c;
            }
        } else {
            for (int i = 0; i < j; ++i) {
                if (dobjs[i].first > dist) break;
                double c = funck(kernel, dobjs[i].first / dist);
                a += dobjs[i].second * c;
                b += c;
            }
        }
    }
    //cout << a << " " << b;
    cout.precision(20);
    if (a == 0) cout << fixed << 0;
    else cout << fixed << a / b;
    return 0;
}