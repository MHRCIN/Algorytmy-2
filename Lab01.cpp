#include <iostream>
#include "time.h"
#include <sstream>
#include <cmath>

using namespace std;

template<typename T>
class List {
public:
    struct Node {
        Node *next, *prev;
        T data;
    };


    //przyklad a dodanie nowego elementu na koncu listy (argument: dane),
    void addLast(const T &dane) {
        Node *n = new Node();
        n->data = dane;
        n->next = nullptr;

        if (size == 0) {
            tail = head = n;
            n->prev = nullptr;
        } else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }
        size++;
    }

    //przyklad b dodanie nowego elementu na poczatku listy (argument: dane)
    void addFirst(const T &dane) {
        Node *n = new Node();
        n->data = dane;
        n->prev = nullptr;

        if (size == 0) {
            head = tail = n;
            n->next = nullptr;
        } else {
            head->prev = n;
            n->next = head;
            head = n;
        }
        size++;
    }

    //przyklad c usuniecie ostatniego elementu
    void deleteLast() {
        if (size == 0) {
            return;
        } else if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size--;
        } else {
            Node *pom = tail->prev;
            delete tail;
            pom->next = nullptr;
            tail = pom;
            size--;
        }
    }

    //przyklad d usuniecie pierwszego elementu
    void deleteFirst() {
        if (size == 0) {
            return;
        } else if (size == 1) {
            delete head;
            head = nullptr;
            tail = nullptr;
            size--;
        } else {
            Node *pom = head->next;
            delete head;
            pom->prev = nullptr;
            head = pom;
            size--;
        }
    }

    //przyklad e zwrocenie danych itego elementu
    T &get(int n) const {
        if (n < size) {

            Node *it = head;

            for (int i = 0; i < n; i++) {
                it = it->next;
            }
            return it->data;
        } else throw "brak elementu";
    }

    //przyklad f ustawienie itego elementu
    void replace(int n, const T &dane) {
        if (n < size) {
            Node *it = head;
            for (int i = 0; i < n; i++) {
                it = it->next;
            }
            it->data = dane;


        } else throw "brak elementu";

    }

    //przyklad g wyszukiwanie elementu
    T *find(const T &dane) const {
        Node *it = head;
        while (it != nullptr && !(it->data == dane)) {
            it = it->next;
        }
        if (it != nullptr) {
            return &(it->data);
        } else {
            return nullptr;
        }

    }

    //przyklad h
    bool remove(const T &dane) {
        Node *it = head;
        while (it != nullptr && !(it->data == dane)) {
            it = it->next;
        }
        if (it != nullptr) {

            if (it == head) {
                deleteFirst();
            } else if (it == tail) {
                deleteLast();
            } else {
                it->prev->next = it->next;
                it->next->prev = it->prev;
                size--;
                delete it;
            }
            return true;
        } else {
            return false;
        }

    }

    //przyklad i
    void addSorted(const T &dane) {
        if (size == 0) {
            addFirst(dane);
        } else if (dane < head->data || dane == head->data) {
            addFirst(dane);
        } else if (tail->data < dane || tail->data == dane) {
            addLast(dane);
        } else {
            Node *it = head;

            while (it->data < dane) {
                it = it->next;
            }
            Node *n = new Node();
            n->data = dane;
            n->prev = it->prev;
            n->next = it;
            it->prev->next = n;
            it->prev = n;
            size++;
        }

    }


    //czyszczenie listy
    void clear() {
        Node *it = head;
        while (it != nullptr) {
            Node *pom = it->next;
            delete it;
            it = pom;
        }
        head = tail = nullptr;
        size = 0;
    }


    //wypisywanie listy
    string to_string() const {
        ostringstream out;
        Node *it = head;
        while (it != nullptr) {
            out << it->data << endl;
            it = it->next;
        }

        return out.str();
    }

    ~List() {//destruktor
        clear();
    }

private:
    Node *head = nullptr, *tail = nullptr;
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

bool operator==(const some_object &so1, const some_object &so2) {
    return so1.field_1 == so2.field_1 && so1.field_2 == so2.field_2;
}
//przyklad i

bool operator<(const some_object &a, const some_object &b) {
    return a.field_1 < b.field_1 || a.field_1 == b.field_1 && a.field_2 < b.field_2;

}


int main() {

    List<some_object> l;
    for (int i = 0; i < 6; i++) {
        some_object so = some_object();
        so.field_1 = rand();
        l.addSorted(so);
    }

    cout << l.to_string();

    srand(time(NULL));
    const int MAX_ORDER = 5; // maksymalny rzad wielkosci rozmiaru dodawanych danych
    List<some_object> *ll = new List<some_object>(); // stworzenie listy
    for (int o = 1; o <= MAX_ORDER; o++) // petla po kolejnych rzedach wielkosci
    {

        const int n = pow(10, o); // rozmiar danych
        cout << "n=" << n << endl;
// dodawanie do listy
        clock_t t1 = clock();
        for (int i = 0; i < n; i++) {
            some_object so = some_object(); // losowe dane
            so.field_1 = rand() % 10000;
            so.field_2 = (rand() % ('z' - 'a') + 'a');
            ll->addLast(so);
        }
        clock_t t2 = clock();
        cout << "sredni czas dodawania " << double(t2 - t1) / n
             << endl; // wypis na ekran aktualnej postaci listy ( skrotowej ) i pomiarow czasowych
// wyszukiwanie i usuwanie z listy


        const int m = pow(10, 4); // liczba prob wyszukania
        t1 = clock();
        for (int i = 0; i < m; i++) {
            some_object so = some_object(); // losowe dane jako wzorzec do wyszukiwania ( obiekt chwilowy )
            so.field_1 = rand() % 10000;
            so.field_2 = (rand() % ('z' - 'a') + 'a');
            ll->remove(so);

        }
        t2 = clock();
        cout << double(t2 - t1) / n
             << endl; // wypis na ekran aktualnej postaci listy ( skrotowej ) i pomiarow czasowych
        ll->clear(); // czyszczenie listy wraz z uwalnianiem pamieci danych

    }
    delete ll;

    return 0;
}

