#include <iostream>
#include "time.h"
#include <sstream>
#include <cmath>

using namespace std;

template<typename T>
class dynamic_array {
public:


//konstruktor
    dynamic_array() {
        capacity = 10;
        size = 0;
        array = new T[capacity];
    }

//przyklad a dodawanie na koncu

    void addLast(const T &dane) {

        if (size<capacity) {
            array[size++] = dane;
        } else {
            capacity = capacity * 2;
            T *tempArray = new T[capacity];

            for (int i = 0; i < size; i++) {
                tempArray[i] = array[i];
            }

            delete[] array;
            array = tempArray;
            array[size++] = dane;
        }

    }

//przyklad b zwrocenie itego elementu tablicy
    T &get(int n) {

        if (n < size && n >= 0) {
            return array[n];
        } else throw "brak elementu";

    }

//przyklad c ustawienie danych itego elementu tablicy	
    void replace(int n, const T &dane) {
        if (n < size && n >= 0) {
            array[n] = dane;
        } else throw "brak elementu";
    }

//przyklad d
    void remove() {
        delete[] array;
        array = NULL;
        size = 0;
        capacity = 0;
    }

//przyklad e
    void out() const {
        int i = 0;
        while (i < size) {
            cout << array[i] << " ";
            cout << endl;
            i++;
        }
    }

//przyklad f bubble sort
    void bubbleSort() {
        //T* tempArray= new T[capacity];
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (array[j + 1] < array[j]) {
                    //tempArray[j]=array[j];
                    swap(array[j], array[j + 1]);
                    //array[j+1]=tempArray[j];
                }
            }
        }

    }

//dekonstruktor
    ~dynamic_array() {
        delete[] array;
    }

private:
    T *array;
    int capacity;
    unsigned int size = 0;

};

struct some_object {
    int field_1;
    char field_2;
};

std::ostream &operator<<(std::ostream &out, const some_object &o) {
    out << o.field_1 << " " << o.field_2;
    return out;
}

bool operator<(const some_object &a, const some_object &b) {
    return a.field_1 < b.field_1 || a.field_1 == b.field_1 && a.field_2 < b.field_2;

}

int main() {

    dynamic_array<some_object> *l = new dynamic_array<some_object>;
    l->remove();
    for (int i = 0; i < 10; i++) {
        some_object o1 = {rand() % 20, 'a'};
        l->addLast(o1);
    }
    /*
    some_object o1={1,'a'} ,o2={2,'b'},o3={3,'c'},o4={4,'d'};
    //dodaje 3 elementy
    l->addLast(o1);
    l->addLast(o2);
    l->addLast(o3);
    l->out();
    cout<<endl;
    //podaje 2 element
    //1 bo numerowanie od 0
    cout<<l->get(1);
    cout<<endl<<endl;
    //zmieniam 2 element na 4
    l->replace(1,o4);
    l->out();
    cout<<endl;
    */
    //sortuje
    l->bubbleSort();
    l->out();

    l->remove();




/*
Kopiuj wklej z PDF


dynamic_array < some_object * >* da = new dynamic_array < some_object * >() ; // stworzenie tablicy
const int order = 7; // rzad wielkosci rozmiaru dodawanych danych
const int n = pow (10 , order ) ; // rozmiar danych
// dodawanie do tablicy
clock_t t1 = clock () ;
double max_time_per_element = 0.0; // najgorszy zaobserwowany czas operacji dodawania
for ( int i = 0; i < n ; i ++) {
some_object * so = ... // losowe dane
clock_t t1_element = clock () ;
da - > add ( so ) ;
clock_t t2_element = clock () ;
double time_per_element = ... // obliczenie czasu pojedynczej operacji dodawania
if ( time_per_element > max_time_per_element )
{
... // odnotowanie nowego najgorszego czasu i komunikat informacyjny na ekran ( przy ktorym
indeksie mialo to miejsce )
}
}
clock_t t2 = clock () ;
... // wypis na ekran aktualnej postaci tablicy ( skrotowej ) i pomiarow czasowych ( czas calkowity i
zamortyzowany )
da - > clear ( true ) ; // czyszczenie tablicy wraz z uwalnianiem pamieci danych
delete da ;
return 0;
*/

}
