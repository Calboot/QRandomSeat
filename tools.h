#ifndef TOOLS_H
#define TOOLS_H

#include "QtCore/qstring.h"
#include <iostream>
#include <cstdlib>
#define fu(x) for(int i=0;i<x;i++)
#define fd(y) for(int i=y;i>0;i--)
#define wh(b) while(b)
using namespace std;

void randomArray(QString s[],int len,int seed=time(0)){
    srand(seed);

    bool b[len];
    QString t[len];
    int tmp;

    fu(len){
        b[i]=false;
        t[i]=s[i];
    }

    fu(len){
        do{
            tmp=arc4random()%len;
        }wh(b[tmp]);
        t[i]=s[tmp];
        b[tmp]=true;
    }

    fu(len){
        s[i]=t[i];
    }

}

void readConfig(){

}

void exportAsCSV(){

}

void exportAsHTML(){

}

#endif // TOOLS_H
