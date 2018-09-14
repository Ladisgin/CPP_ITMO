//
// Created by Vladislav Kalugin on 08/09/2018.
//
#include <iostream>
#include <vector>
#include <algorithm>
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
    fixed_vector<int, 999> fv;
    vector<int> k(0);
    for (int i = 0; i < 50; i++) {
//        if ((i + 1) % 25) {
        fv.push_back(i);
        k.push_back(i);
//        } else {
//            fv.pop_back();
//            k.pop_back();
//        }
//        fv[i/7] = i*3;
//        k[i/7] = i*3;
    }
    cout << (diff(fv, k) ? "Good push back" : "Bad") << endl;
    fixed_vector<int, 999> fv2(fv);
    cout << (diff(fv2, k) ? "Good copy constructor" : "Bad") << endl;
    fixed_vector<int, 999> fv3 = fixed_vector<int, 999>(fv);
    cout << (diff(fv3, k) ? "Good" : "Bad") << endl;
    fixed_vector<int, 999> fv4;
    fv4 = fixed_vector<int, 999>(fv);
    cout << (diff(fv3, k) ? "Good operator =" : "Bad") << endl;
//    for (auto i:fv) {
//        cout << i << endl;
//    }

    //fix::iterator it = fv.begin();
    int l = 0;

    for (auto r = fv.begin(); r < fv.end(); r++) {
        *r = l++;
    }
    l = 0;
    for (auto r = k.begin(); r < k.end(); r++) {
        *r = l++;
    }
    cout << (diff(fv, k) ? "Good iterator" : "Bad") << endl;

    l = 44;
    for (auto r = fv.rbegin(); r < fv.rend(); r++) {
        *r = l++;
    }
    l = 44;
    for (auto r = k.rbegin(); r < k.rend(); r++) {
        *r = l++;
    }
    cout << (diff(fv, k) ? "Good reverse iterator" : "Bad") << endl;
}


