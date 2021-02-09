/*************************************************************************
	> File Name: main.cxx
	> Author: Rslsws
	> Mail: rslsws@gmail.com
	> Created Time: 一  2/ 1 11:23:45 2021
 ************************************************************************/

#include "head.h"

int main() {

    int n;
    Ins** vec = readData(n, "test1.txt");
    //PrintIns(vec, n);
    std::sort(vec, vec+n, [](Ins* Ip1, Ins* Ip2){
        return Ip1->x < Ip2->x;
    });
    PrintIns(vec, n);
    for (int i = 0; i < n; ++i) {
        Find(vec, n, i);
    }
    for (int i = 0; i < n; ++i) {
        std::cout << i << ":";
        for (auto &j : C[i].ex) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}
