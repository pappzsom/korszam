#include <vector>
#include <iostream>
#include "polinom.h"

template<typename T>
Polinom<T>::Polinom(std::vector<T> const& coefficients){
    coef=coefficients;
};

template<typename T>
Polinom<T>::Polinom(std::vector<T>&& coefficients){
    coef=coefficients;
};

template<typename T>
Polinom<T>::Polinom(T coefficients[]){
    coef=std::vector<T>(coefficients, coefficients+sizeof(coefficients));
};

template<typename T>
Polinom<T>::Polinom(std::initializer_list<T>&& coefficients){
    coef=coefficients;
};

template<typename T>
Polinom<T>::Polinom(Polinom<T> const& p){
    coef=p.coef;
};

template<typename T>
Polinom<T>::Polinom(Polinom<T>&& p){
    std::swap(coef,p.coef);
};

template<typename T>
Polinom<T>& Polinom<T>::operator+=(Polinom<T> const& p){
    if(coef.size()>=p.coef.size()){
        for (int i = 0; i < p.coef.size(); i++){
            coef[i]+=p[i];
        };
    }else{
        coef.resize(p.coef.size());
        for (int i = 0; i < coef.size(); i++){
            coef[i]+=p[i];
        };
        for (int i = coef.size(); i < p.coef.size(); i++){
            coef[i]=p[i];
        };
    };
    return *this;
};

template<typename T>
Polinom<T>& Polinom<T>::operator-=(Polinom<T> const& p){
    if(coef.size()>=p.coef.size()){
        for (int i = 0; i < p.coef.size(); i++){
            coef[i]-=p[i];
        };
    }else{
        coef.resize(p.coef.size());
        for (int i = 0; i < coef.size(); i++){
            coef[i]-=p[i];
        };
        for (int i = coef.size(); i < p.coef.size(); i++){
            coef[i]=-p[i];
        };
    };
    return *this;
};

template<typename T>
Polinom<T>& Polinom<T>::operator*=(Polinom<T> const& p){
    std::vector<T> result;
    result.resize(coef.size()+p.coef.size(),0);
    for(int i = 0; i<coef.size();i++){
        for(int j = 0; j<p.coef.size();j++){
            result[i+j]+=coef[i]*p.coef[j];
        };
    };
    coef=std::move(result);
    return *this;
};
//Önderiválás
template<typename T>
Polinom<T>& Polinom<T>::derivate(){
    for(int i = 1; i<coef.size(); i++){
        coef[i-1]=i*coef[i];
    }
    coef.pop_back();
    return *this;
};
//[] op
template<typename T>
T& Polinom<T>::operator[](int i){
    return coef[i];
};
template<typename T>
T const& Polinom<T>::operator[](int i) const{
    return coef[i];
};


template<typename T>
Polinom<T> operator+(Polinom<T> const& p1, Polinom<T> const& p2){
    std::vector<T> result;
    if(p1.coef.size()>=p2.coef.size()){
        result = p1.coef;
        for(int i = 0; i<p2.coef.size();i++){
            result[i]+=p2[i];
        };
    }else{
        result = p2.coef;
        for(int i = 0; i<p1.coef.size();i++){
            result[i]+=p1[i];
        };
    };
    return Polinom<T>(std::move(result));
};

//kivonás
template<typename T>
Polinom<T> operator-(Polinom<T> const& p1, Polinom<T> const& p2){
    std::vector<T> result;
    if(p1.coef.size()>=p2.coef.size()){
        result = p1.coef;
        for(int i = 0; i<p2.coef.size();i++){
            result[i]-=p2[i];
        };
    }else{
        result = p2.coef;
        for(int i = 0; i<p1.coef.size();i++){
            result[i]=-result[i];
            result[i]+=p1[i];
        };
        for(int i = p1.coef.size(); i<p2.coef.size();i++){
            result[i]=-result[i];
        }
    };
    return Polinom<T>(std::move(result));
};

//Szorzás
template<typename T>
Polinom<T> operator*(Polinom<T> const& p1, Polinom<T> const& p2){
    std::vector<T> result;
    result.resize(p1.coef.size()+p2.coef.size(),0);
    for(int i = 0; i<p1.coef.size();i++){
        for(int j = 0; j<p2.coef.size();j++){
            result[i+j]+=p1[i]*p2[j];
        };
    };
    return Polinom<T>(std::move(result));
};

//IO operátorok
template<typename T>
std::ostream& operator<<(std::ostream& o, Polinom<T> p){
    for(int i = 0; i < p.coef.size(); i++){
        if(p[i]!=0){
            if(p[i]>0){
                o << "+ ";
            }else{
                o << "- ";
            };
            o << p[i];
            if(i!=0){
                o << " * x^" << i;
            };
            o<<" ";
        };
    }
    return o;
};
//input nem lesz mert az komplikált lenne a nem fix méret miatt

//deriválás
template<typename T>
Polinom<T> derivate(Polinom<T> p){
    std::vector<T> result;
    result.resize(p.coef.size()-1);
    for(int i =1; i<p.coef.size();i++){
        result[i-1]=i*p[i];
    }
    return Polinom<T>(std::move(result));
};

/*
Ez erősen fúj hogy így kell megoldani. Vagy berakom a definíciókat a headerbe, elveéve annak a lényegét, vagy előre meg kell mondjam az összes
lehetséges classt amivel hasznánli szeretném.
*/
template struct Polinom<int>;
template struct Polinom<float>;
template Polinom<int> operator*(Polinom<int> const& p1, Polinom<int> const& p2);
template Polinom<float> operator*(Polinom<float> const& p1, Polinom<float> const& p2);
template Polinom<int> operator+(Polinom<int> const& p1, Polinom<int> const& p2);
template Polinom<float> operator+(Polinom<float> const& p1, Polinom<float> const& p2);
template Polinom<int> operator-(Polinom<int> const& p1, Polinom<int> const& p2);
template Polinom<float> operator-(Polinom<float> const& p1, Polinom<float> const& p2);
template std::ostream& operator<<(std::ostream& o, Polinom<int> p);
template std::ostream& operator<<(std::ostream& o, Polinom<float> p);
