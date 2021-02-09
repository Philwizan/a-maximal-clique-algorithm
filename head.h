/*************************************************************************
	> File Name: head.h
	> Author: Rslsws
	> Mail: rslsws@gmail.com
	> Created Time: 一  2/ 1 08:54:55 2021
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <map>
#include <set>
#include <cmath>

struct Ins {
    int id;
    double x, y;
};

struct c_item {
    std::set<int> ex;
};

extern double r;

extern c_item *C;

static std::ofstream ofs("output_MC.txt");

bool Near(Ins* i1, Ins* i2);
Ins** readData (int& len, const char* file);
void PrintIns(Ins **vec, int len);
void Find(Ins **vec, int n, int left);
double GetPointP(double x1, double y1, double x2, double y2);
void Mark(Ins **vec, int len, std::vector<Ins*> &B, int left);
bool Contain(std::vector<Ins*> &B, int id);
void PrintR(std::map<int , std::vector<Ins*> > &R);

#endif
