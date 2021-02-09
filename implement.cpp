/*************************************************************************
	> File Name: implement.cpp
	> Author: Rslsws
	> Mail: rslsws@gmail.com
	> Created Time: 一  2/ 1 09:36:10 2021
 ************************************************************************/

#include "head.h"

double r = 5.5;

c_item *C = new c_item[20002];

Ins** readData(int& len, const char* file) {
    std::ifstream in(file);
    in >> len;
    Ins** vec = new Ins*[len];
    for (int i = 0; i < len; ++i) {
        double x, y;
        in >> x >> y;
        vec[i] = new Ins; 
        vec[i]->id = i;
        vec[i]->x = x;
        vec[i]->y = y;
    }
    in.close();
    return vec;
}

void PrintIns(Ins **vec, int len) {
    
    for (int i = 0; i < len; ++i) {
        std::cout << vec[i]->id << " " << vec[i]->x << " " << vec[i]->y << std::endl;
    }
}

bool Near(Ins* i1, Ins* i2) {
    if ((i1->x - i2->x) * (i1->x - i2->x) + (i1->y - i2->y) * (i1->y - i2->y) <= r * r) return 1;
    else return 0;
}

void Find(Ins **vec, int n, int left) {
    std::cout << "left = " << vec[left]->id << std::endl;
    std::vector<Ins*> A;
    std::map<int, bool> F;

    std::cout << "C[" << vec[left]->id << "] = ";
    for (auto &i : C[vec[left]->id].ex) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    /*
    for (int i = 0; i < n; ++i) {
        std::cout << i << ":";
        for (auto &j : C[i].ex) {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
*/
    for (int i = 1; i + left < n; ++i) {
        if (vec[i + left]->x > vec[left]->x + r) break;
        if (Near(vec[i + left], vec[left])) {
            if (C[vec[left]->id].ex.find(vec[i + left]->id) != C[vec[left]->id].ex.end()) continue;
            A.push_back(vec[i + left]);
            F[vec[i + left]->id] = 0;
        }
    }
    sort(A.begin(), A.end(), [](Ins* i1, Ins* i2){
        return i1->y > i2->y;
    });

    std::cout << "A = ";
    for (auto &ins : A) {
        std::cout << ins->id << " ";
    }
    std::cout << std::endl;

    std::vector<Ins*> B;
    for (int i = 0; i < A.size(); ++i) {
        B.clear();
        B.push_back(A[i]);
        for (int j = i + 1; j < A.size(); ++j) {
            if (Near(A[i], A[j])) {
                B.push_back(A[j]);
            }
        }
        for (int k = 0; k < B.size(); ++k) {
            //std::cout << "F[" << B[k] << "] = "
            if (F[B[k]->id]) continue;
            else {
                ofs << vec[left]->id;
                for (auto l : B) {
                    ofs << " " << l->id; 
                }
                ofs << std::endl;
                F[B[k]->id] = 1;
                for (int l = k + 1; l < B.size(); ++l) {
                    F[B[l]->id] = 1;
                }
                sort(B.begin(), B.end(), [](Ins* i1, Ins* i2){
                    return i1->x < i2->x;
                });
                Mark(vec, n, B, left);
                break;
            }
        }
        int flag = 1;
        for (auto &item : F) {
            if (item.second == 0) {
                flag = 0;
                break;
            } 
        }
        if (flag) return;
    }
}


double GetPointP(double x1, double y1, double x2, double y2) {
    double xx = (x1 + x2) / 2;
    double yy = (y1 + y2) / 2;
    double detay = y1 - y2;
    double detax = x1 - x2;
    if (detax == 0) {
        return sqrt(r * r - (xx - x1) * (xx - x1)) + y1;
    }
    if (detay == 0) {
        return yy;
    }
    double k = detay / detax;
    double m = k * (xx - x1) - yy;
    double a = (1 + 1/k/k);
    double b = -2 * (y1 + m / k / k);
    double c = (m / k) * (m / k) + y1 * y1 - r * r;
    double deta = b * b - 4 * a * c;
    return (-b - sqrt(deta)) / 2 / a;
}

bool Contain(std::vector<Ins*> &B, int id) {
    for (auto &i : B) {
        if (i->id == id) return 1;
    }
    return 0;
}

void PrintR(std::map<int, std::vector<Ins*> > &R) {
    for (auto &i : R) {
        std::cout << i.first << ": ";
        for (auto &j : i.second) {
            std::cout << j->id << " ";
        }
        std::cout << std::endl;
    }
}

void Mark(Ins **vec, int len, std::vector<Ins*> &B, int left) {
    std::map<int, std::vector<Ins*> > R;
   /* 
    std::cout << "B = ";
    for (auto &i : B) {
        std::cout << i->id << " ";
    }
    std::cout << std::endl;
*/
    for (int i = 0; i < B.size() - 1; ++i) {
        for (int j = left + 1; j < len; ++j) {
            if (vec[j]->id == B[i]->id) {
                for (int k = j + 1; k < len && vec[j]->x + r >= vec[k]->x; ++k) {
                    if (!Contain(B, vec[k]->id) && Near(vec[k], vec[j])) {
                        R[B[i]->id].push_back(vec[k]); 
                    }
                }
            }
        }
    }
    //PrintR(R);
    for (int i = 0; i < B.size() - 1; ++i) {
        for (int j = i + 1; j < B.size(); ++j) {
            int flag = 1;
            for (auto &k : R[B[i]->id]) {
                if (Near(B[j], k)) {
                    flag = 0;
                    break;
                }
            }
            if (flag) {
                C[B[i]->id].ex.insert(B[j]->id);
                std::cout << "mark C[" << B[i]->id << "] = " << B[j]->id << std::endl;
            }
        }
    }
}
