//
// Created by Vladislav Kalugin on 08/09/2018.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <cmath>
#include "fixed_vector.h"

using namespace std;

template<class T, size_t N>
bool diff(fixed_vector<T, N> const &fv, vector<T> v) {
    bool k = fv.size() == v.size();
    for (size_t i = 0; (i < v.size()) && k; i++) {
        if (fv[i] != v[i]) {
            cout << fv[i] << " " << v[i] << endl;
            k = false;
        }
    }
    return k;
}

int main() {
    srand(time(nullptr));
    const size_t capacity = 12345;

    fixed_vector<int, capacity> test_fixed_vector;
    vector<int> test_vector(0);
    for (int i = 0; i < rand() % capacity; i++) {
        int r = rand();
        test_fixed_vector.push_back(r);
        test_vector.push_back(r);
    }
    cout << (diff(test_fixed_vector, test_vector) ? "Good push_back()" : "Bad") << endl;


    cout << (test_fixed_vector.size() == test_vector.size() ? "Good size()" : "Bad") << endl;


    cout << (test_fixed_vector.max_size() == capacity ? "Good max_size()" : "Bad") << endl;


    cout << (test_fixed_vector.capacity() == capacity ? "Good capacity()" : "Bad") << endl;


    auto fv2(test_fixed_vector);
    cout << (diff(fv2, test_vector) ? "Good copy constructor" : "Bad") << endl;


    auto fv3 = test_fixed_vector;
    cout << (diff(fv3, test_vector) ? "Good copy constructor 2" : "Bad") << endl;


    fixed_vector<int, capacity> fv4;
    fv4 = test_fixed_vector;
    cout << (diff(fv3, test_vector) ? "Good operator =" : "Bad") << endl;


    auto fv5(test_fixed_vector);
    auto k1(test_vector);
    for (size_t i = 0; i < rand() % fv5.size(); i++) {
        fv5.pop_back();
        k1.pop_back();
    }
    cout << (diff(fv5, k1) ? "Good pop_back()" : "Bad") << endl;


    fixed_vector<int, capacity> sf;
    auto ss = test_fixed_vector;
    swap(sf, ss);
    cout << (diff(sf, test_vector) ? "Good swap" : "Bad") << endl;


    int l = 0;

    for (auto r = test_fixed_vector.begin(); r < test_fixed_vector.end(); r++) {
        *r = l++;
    }
    l = 0;
    for (auto r = test_vector.begin(); r < test_vector.end(); r++) {
        *r = l++;
    }
    cout << (diff(test_fixed_vector, test_vector) ? "Good iterator" : "Bad") << endl;


    l = 44;
    for (auto r = test_fixed_vector.rbegin(); r < test_fixed_vector.rend(); r++) {
        *r = l++;
    }
    l = 44;
    for (auto r = test_vector.rbegin(); r < test_vector.rend(); r++) {
        *r = l++;
    }
    cout << (diff(test_fixed_vector, test_vector) ? "Good reverse iterator" : "Bad") << endl;
}


