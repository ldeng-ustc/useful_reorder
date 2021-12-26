#include <iostream>
#include <chrono>
#include <memory>
#include <random>
#include <tuple>
#include <algorithm>
using namespace std;
using timer = chrono::high_resolution_clock;

using P = tuple<double, int, int, double, double>;

inline P operator*(const P& a, const P& b) {
    return P{
        get<0>(a)*get<0>(b),
        get<1>(a)*get<1>(b),
        get<2>(a)*get<2>(b),
        get<3>(a)*get<3>(b),
        get<4>(a)*get<4>(b),
    };
}

inline P operator+(const P& a, const P& b) {
    return P{
        get<0>(a)+get<0>(b),
        get<1>(a)+get<1>(b),
        get<2>(a)+get<2>(b),
        get<3>(a)+get<3>(b),
        get<4>(a)+get<4>(b),
    };
}

inline P operator/(const P& a, const P& b) {
    return P{
        get<0>(a)/get<0>(b),
        get<1>(a)/get<1>(b),
        get<2>(a)/get<2>(b),
        get<3>(a)/get<3>(b),
        get<4>(a)/get<4>(b),
    };
}

const size_t N = 32*1024*1024;
int main() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(1, 1545676);
    std::uniform_real_distribution<double> fdist(0.1, 23.7);

    auto v1 = make_unique<P[]>(4*N);
    auto v2 = make_unique<double[]>(4*N);

    for(size_t i=0; i<4*N; i++) {
        get<0>(v1[i]) = dist(mt);
        get<1>(v1[i]) = dist(mt);
        get<2>(v1[i]) = dist(mt);
        get<3>(v1[i]) = dist(mt);
        get<4>(v1[i]) = dist(mt);
        v2[i] = fdist(mt);
    }

    auto st = timer::now();
    
    for(size_t i=0; i< N; i++) {
        v1[i] = v1[i + 245] * v1[i * i % N];
        v1[i+245] = v1[i] * v1[(i * 5 + 447) % N];
        v1[i + 747] = v1[i] * v1[(i * i + 4572) % N];
        v1[i] = v1[i+877] * v1[(i*i) % N];
        v2[i] = v2[i+1] / v2[i+2];
        v2[i + 3] = v2[i] / v2[i+1];
        v2[i + N] = v2[i + N] / v2[i + N + 3];
        v2[i + N + 7] = v2[i + N + 77] / v2[i + N + 57];
        v2[i + N - 47] = v2[i + N - 15] / v2[i + N + 34];
    }

    auto ed = timer::now();
    chrono::duration<double> dur = ed - st;
    cout << "Calculate time: " << dur.count() << "s" << endl;
    return 0;
}