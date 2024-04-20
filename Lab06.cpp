#include <iostream>
#include "time.h"
#include <sstream>
#include <cmath>

using namespace std;

template<typename T>
class binary_heap {
public:


//konstruktor
    binary_heap() {
        capacity = 10;
        size = 0;
        array = new T[capacity];
    }

    void heapDown(unsigned int i) {

        int min;
        int n = size - 1;
        do {
            int l = 2 * i + 1;
            int r = l + 1;
            if ((l <= n) && (array[l] < array[i])) min = l;
            else min = i;
            if ((r <= n) && (array[r] < array[i]) && (array[r] < array[l])) min = r;
            if (i != min) {
                swap(array[i], array[min]);
                i = min;
            } else break;
        } while (i < n);

    }

    void heapUp(unsigned int i) {
        while (i && array[i] < array[(i - 1) / 2]) {
            swap(array[i], array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }

    }

    void add(const T &dane) {
        //sprawdzenie duplikatu
       // for (int i = 0; i < size; i++) if (dane == array[i]) return;

        if (size < capacity) {
            array[size++] = dane;
        } else {
            capacity = capacity * 2+1;
            T *tempArray = new T[capacity];

            for (int i = 0; i < size; i++) {
                tempArray[i] = array[i];
            }

            delete[] array;
            array = tempArray;
            array[size++] = dane;
            
        }
        heapUp(size-1);
    }


    T removeMax() {
        T temp = array[0];
        array[0] = array[--size];
        heapDown(0);
        return temp;
    }

    void clear() {
        delete[] array;
        array = NULL;
        size = 0;
        capacity = 0;
    }

    void out() const {
        int i = 0;
        while (i < size) {
            cout << array[i] << " ";
            cout << endl;
            i++;
        }
    }


private:
    T *array;
    int capacity;
    unsigned int size = 0;
};

struct some_object {
    int field_1;
};

std::ostream &operator<<(std::ostream &out, const some_object &o) {
    out << o.field_1;
    return out;
}

bool operator<(const some_object &a, const some_object &b) {
    return a.field_1 < b.field_1 || a.field_1 == b.field_1;

}

bool operator==(const some_object &so1, const some_object &so2) {
    return so1.field_1 == so2.field_1;
}

/*
int main() {
    binary_heap<some_object> *l = new binary_heap<some_object>;
    some_object o1 = {1}, o2 = {3}, o3 = {6}, o4 = {5}, o5 = {9}, o6 = {8};
    //dodaje 3 elementy
    l->add(o1);
    l->add(o2);
    l->add(o3);
    l->add(o4);
    l->add(o5);
    l->add(o6);
    l->out();
    cout<<"Usunieto: "<<l->removeMax();
    cout<<endl;
    l->out();
    l->clear();
    cout<<endl;
    l->add(o1);
    l->out();
    return 0;
}
*/

int main() {
const int MAX_ORDER = 6; // maksymalny rzad wielkosci dodawanych danych
binary_heap < some_object >* bh = new binary_heap < some_object > ;
for ( int o = 1; o <= MAX_ORDER ; o ++)
{
const int n = pow (10 , o ) ; // rozmiar danych

// dodawanie do kopca
clock_t t1 = clock () ;
for ( int i = 0; i < n ; i ++) {
some_object so = {rand() % 100}; // losowe dane
bh->add(so);
}
clock_t t2 = clock () ;

//bh->out(); // wypis na ekran aktualnej postaci kopca ( skrotowej ) oraz pomiarow czasowych
cout<<"Pomiar czasowy "<<(t2-t1)/(double)CLOCKS_PER_SEC<<endl;


// pobieranie ( i usuwanie ) elementu maksymalnego z kopca
t1 = clock () ;
for ( int i = 0; i < n ; i ++) {
//cout<<"Usun "<<bh->removeMax();// ewentualny wypis na ekran danych elementu pobranego ( przy malym eksperymencie )
bh -> removeMax ( ) ; 
}
t2 = clock () ;


bh-> out(); // wypis na ekran aktualnej postaci kopca ( kopiec pusty ) oraz pomiarow czasowych
cout<<endl;
cout<<"Pomiar czasowy "<<double(t2-t1)/(CLOCKS_PER_SEC)<<endl;
bh -> clear() ; // czyszczenie kopca ( tak naprawde ,, zresetowanie �� tablicy dynamicznej
}

return 0;
}
