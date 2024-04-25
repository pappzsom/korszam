#include <vector>
#include <iostream>

template<typename T>
struct Polinom{
    std::vector<T> coef;

    //constructors
    Polinom<T>(std::vector<T> const& coefficients);
    Polinom<T>(std::vector<T>&& coefficients);
    Polinom<T>(T coefficients[]);
    Polinom<T>(std::initializer_list<T>&& coefficients);
    Polinom<T>(Polinom<T> const& p);
    Polinom<T>(Polinom<T>&& p);

    //+= op
    Polinom<T>& operator+=(Polinom<T> const& p);

    //-= op
    Polinom<T>& operator-=(Polinom<T> const& p);

    //*= op
    Polinom<T>& operator*=(Polinom<T> const& p);

    //Önderiválás
    Polinom<T>& derivate();

    //[] op
    T& operator[](int i);
    T const& operator[](int i) const;
};


//Operátorok és függvények
//összeadás
template<typename T>
Polinom<T> operator+(Polinom<T> const& p1, Polinom<T> const& p2);

//kivonás
template<typename T>
Polinom<T> operator-(Polinom<T> const& p1, Polinom<T> const& p2);

//Szorzás
template<typename T>
Polinom<T> operator*(Polinom<T> const& p1, Polinom<T> const& p2);

//IO operátorok
template<typename T>
std::ostream& operator<<(std::ostream& o, Polinom<T> p);
//input nem lesz mert az komplikált lenne a nem fix méret miatt

//deriválás
template<typename T>
Polinom<T> derivate(Polinom<T> p);
