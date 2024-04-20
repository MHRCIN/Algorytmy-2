#include <iostream>
#include <vector>
#include <forward_list>
#include <sstream>
#include <cmath>
#include "time.h"
#include <algorithm>
using namespace std;

template<typename V>

class Hash {
public:
    Hash() {
        t.resize(4);
        n = 0;
    }

    void add(const string &key, const V &va) {
        if (n >= 0.75 * t.size()) {
            rehash();
        }
        size_t idx = compute_idx(key);
        for (auto &e: t[idx]) {
            if (e.first == key) {
                e.second = va;
                return;
            }
        }
        t[idx].push_front(make_pair(key, va));
        n++;
    }

    V *search(const string &key) {
        size_t idx = compute_idx(key);
        for (auto &e: t[idx]) {
            if (e.first == key) {
                return &e.second;
            }
        }
        return nullptr;
    }

    bool remove(const string &key) {
        size_t idx = compute_idx(key);
        for (auto &e: t[idx]) {
            if (e.first == key) {
                t[idx].remove(e);
                return true;
            }
        }
        return false;
    }

    void clear() {
        t.clear();
        n = 0;
    }

    void display() {
        for (int i = 0; i < t.size(); i++) {
        	if (!t[i].empty()) {
            cout << i << " -> ";
            for (auto it = t[i].begin(); it != t[i].end(); it++) {
                cout << "(" << it->first << ", " << it->second << ") ";
            }
            cout << endl;
        }}
    }

    string toString() {
        string a;
        for (int i = 0; i < t.size(); i++) {
            if (!t[i].empty()) {
                a += (to_string(i) + " -> ");
                for (auto &e: t[i]) {
                    a += "(" + e.first + ", " + e.second + ") ";
                }
                a += "\n";
            }
        }
        return a;
    }

    size_t compute_idx(string key) const {
        size_t h = 0;
        for (size_t i = 0; i < key.length(); i++) {
            h = h * 31 + key[i];
        }
        return h % t.size();
    }
    
	void print_stats(){
		cout<<"Rozmiar "<<n<<endl;
	
		int blank=0,it,max,min=100;
		for (int i = 0; i < t.size(); i++) {
            if(t[i].empty()) blank++;
            it=0;
        	for (auto &e: t[i]) {
			it++;
			if(max<it) max=it; 
			if(min>it) min=it;
			}
			
		}
        cout<<"Puste "<<blank<<endl;
        cout<<"Max "<<max<<endl;
        cout<<"Min "<<min<<endl;
        
	}
   

private:
    vector<forward_list<pair<string, V>>> t;
    size_t n;

    void rehash() {
        vector<forward_list<pair<string, V>>> o;
        o = t;
        t.clear();
        t.resize(o.size() * 2 + 1);
        for (auto &e: o) {
            for (auto &f: e) {
                size_t idx = compute_idx(f.first);
                t[idx].push_front(f);
            }
        }
    }


};

struct some_object {
    int value;
};

string random_key(const int length) {
    static const char dictionary[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ""abcdefghijklmnopqrstuvwxyz";
    string tmp;
    for (int i = 0; i < length; i++) {
        tmp += dictionary[rand() % (sizeof(dictionary) - 1)];
    }
    return tmp;
}

std::ostream &operator<<(std::ostream &out, const some_object &o) {
    out << o.value;
    return out;
}

bool operator==(const some_object &o1, const some_object &o2) {
    return o1.value == o2.value;
}

string operator+(const string &s, const some_object &o2) {
    return s + to_string(o2.value);
}

/*
int main()
{
    some_object o1 = { 2 };
    some_object o2 = { 5 };
    Hash<some_object>* a = new Hash<some_object>();
    a->add("aqwefa", o1);
    a->add("eadgfd", o1);
    a->add("fsdfzb", o1);
    a->add("ffgjhs", o1);
    cout<<a->toString();
    a->add(random_key(6),o1);
    a->add(random_key(6),o2);
    cout<<"Szukanie: "<<*(a->search("eadgfd"))<<endl;
//    cout<<"Usuwanie: "<<a->remove("aqwefa")<<endl;
//    cout<<"Usuwanie nieistniejacego: "<<a->remove("eeeeee")<<endl;
    a->display();
//    a->clear();
//    a->add("aqwefa", D1);
    //a->display();
    cout<<endl;
    //cout<<a->toString();
	cout<<endl;
	cout<<endl;
	
}
*/

int main() {

    const int MAX_ORDER = 7; // maksymalny rzad wielkosci dodawanych danych
    Hash<int> *ht = new Hash<int>();
    for (int o = 1; o <= MAX_ORDER; o++) {
        const int n = pow(10, o); // rozmiar danych
// dodawanie do tablicy mieszajacej
        clock_t t1 = clock();
        for (int i = 0; i < n; i++)
            ht->add(random_key(6), i); // klucze losowe 6 - znakowe , a jako wartosci indeks petli
        clock_t t2 = clock();
        ht->print_stats(); // wypis na ekran aktualnej postaci tablicy mieszajacej ( skrotowej ) oraz pomiarow

        cout << endl << endl;
        
        
// wyszukiwanie w tablicy mieszajacej
        const int m = pow(10, 4);
        int hits = 0;
        t1 = clock();
        for (int i = 0; i < m; i++) {
            auto entry = ht->search(random_key(6)); // wyszukiwanie wg losowego klucza
            if (entry != NULL)
                hits++;
        }
        t2 = clock();
       cout<<double(t2-t1)/n<<endl; // wypis na ekran pomiarow czasowych i liczby trafien
        ht->clear(); // czyszczenie tablicy mieszajacej
    }
    delete ht;
    return 0;
}



