#include "polinom.h"
#include <vector>
#include <iostream>

int main(){
    //A különböző konstruktorok működése
    //Kész vektorból
    std::vector<int> coef1{1,2};
    Polinom<int> p1(coef1);
    std::cout << "p1 = " << p1 << std::endl;
    //pr értékű vektorból
    Polinom<int> p2(std::vector<int>({1,2,3}));
    std::cout << "p2 = " << p2 << std::endl;
    //Kész arrayből
    int coef3[4]={1,2,3,4};
    Polinom<int> p3(coef3);
    std::cout << "p3 = " << p3 << std::endl;
    //Direktbe megadott arrayből, és most floatként
    Polinom<float> pf1({1.0,2.0,3.0,4.0,5.0});
    //Másik polinomból
    Polinom<float> pf2(pf1);
    std::cout << "pf1 = pf2 = " << pf1 <<std::endl;
    //pr értékű polinomból
    Polinom<int> p4(p1+p2);
    std::cout << "p4 = p1+p2 = " << p4 << std::endl;
    //Szorzás
    Polinom<float> pf3=pf1*pf2;
    std::cout << "pf3 = pf1*pf2 = " << pf3 << std::endl;
    //Önnön szorzás
    p2*=p3;
    p2.derivate();
    std::cout << "(d/dx)(p2*p3)" << p2<< std::endl;
    std::cout << "pf3-pf1 = " << pf3-pf1<< std::endl;
    return 0;
};
