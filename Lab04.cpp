//ALGO2 IS1 221B LAB04
//Marcin Gieraszek
//gm49251@zut.edu.pl
#include <iostream>

using namespace std;

template<typename T>
class RBT {
public:

    struct Node {
        Node *left, *right, *parent;
        T data;
        bool color;
    };

    //przyklad a wyszukiwanie elementu
    Node *search(const T &dane) {
        Node *n = root;
        while (n) {
            if (dane < n->data) n = n->left;
            else if (n->data < dane) n = n->right;
            else break;
        }
        return n;
    }

    //przeladowanie d czyszczenie drzewa
    void clear() {
        clear(root);
        size = 0;
    }

    //przeladowanie e wyznaczenie wysokosci drzewa
    int findHeight() {
        return findHeight(root);
    }


    //przeladowanie g wyswietlenie drzewa
    void show() {
        inOrder(root);
    }

    int getSize() {
        return size;
    }

    Node *root;
    int size = 0;


//przyklad b przejscie pre-order drzewa
    void preOrder(Node *it) {
        if (it == nullptr) return;
        if (it->color) {
            cout << it->data << " " << "BLACK ";
        } else {
            cout << it->data << " " << "RED ";
        }
        preOrder(it->left);
        preOrder(it->right);
    }

//przyklad c przejscie in-order drzewa
    void inOrder(Node *it) {
        if (it == nullptr) return;
        inOrder(it->left);
        if (it->color) {
            cout << it->data << " " << "BLACK ";
        } else {
            cout << it->data << " " << "RED ";
        }
        inOrder(it->right);

    }

//przyklad d czyszczenie drzewa
    void clear(Node *n) {
        root = nullptr;
        if (n == nullptr) return;
        else {
            clear(n->left);
            clear(n->right);
            delete n;
        }
    }

//przyklad e wyznaczanie wysokosci
    int findHeight(Node *n) {
        if (n == nullptr) return 0;
        int leftHeight = findHeight(n->left);
        int rightHeight = findHeight(n->right);
        if (leftHeight < rightHeight) return rightHeight + 1;
        else return leftHeight + 1;
    }


//przyklad f dodanie nowego elementu
    Node *add(const T &dane) {
    	//x wskaznik do znalezienia punktu wstawiania
    	//y wezel nadrzedny do wstawiania
        Node *n = this->root;
        Node *y = nullptr;
        Node *z = new Node();
        z->data = dane;
        z->color = false;
        z->parent = nullptr;
        z->left = nullptr;
        z->right = nullptr;
//to w sumie jest bst
        while (n != nullptr) {
            y = n;
            if (n->data < dane)
                n = n->right;
            else
                n = n->left;
        }

        z->parent = y;

        if (y == nullptr)
            root = z;
        else if (y->data < z->data)
            y->right = z;
        else
            y->left = z;
//jesli wezel nadrzedny "z' jest glownym to mozna wkleic bez koniecznosci naprawy 
        if (z->parent == nullptr) {
            z->color = true;
            return nullptr;
        }
        if (z->parent->parent == nullptr) {
            return nullptr;
        }
        InsertFinUp(z);

        return nullptr;
    }

    void InsertFinUp(Node *z) {

//jesli nie jest to wezel glowny
//i kolor czerwony
        while (z != root && z->parent->color == false) {
            Node *grandparent = z->parent->parent;
            Node *uncle = (z->parent == grandparent->left) ? grandparent->right : grandparent->left;
            bool side = (z->parent == grandparent->left) ? true : false;
//I
            if (uncle && uncle->color == false) {
                z->parent->color = true;
                uncle->color = true;
                grandparent->color = false;
                z = grandparent;
            } else {
//II side true p[z] jest lewym dzieckiem false prawym

                if (z == (side ? z->parent->right : z->parent->left)) {
                    z = z->parent;
                    side ? RotateLeft(z) : RotateRight(z);
                }

                z->parent->color = true;
                grandparent->color = false;
                side ? RotateRight(grandparent) : RotateLeft(grandparent);
            }
        }
        root->color = true;
    }


    bool checkIntegrity(Node *n) {
        if (!n) return true;
        bool ok = true;
        if (n->left) {
            ok = ok && n->left->parent == n;
            ok = ok && check_integrity(n->left);
        }
        if (n->right) {
            ok = ok && n->right->parent == n;
            ok = ok && check_integrity(n->right);
        }
        return ok;
    }

    void RotateLeft(Node *x) {
        Node *y;

        y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if (!x->parent) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        x->parent = y;
        y->left = x;
    }

    void RotateRight(Node *y) {
        Node *x;

        x = y->left;
        y->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = y;
        }
        x->parent = y->parent;

        if (!y->parent) {
            root = x;
        } else if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
        y->parent = x;
        x->right = y;
    }


};

struct some_object {
    int field_1;
};


bool operator<(const some_object &a, const some_object &b) {
    return a.field_1 < b.field_1;
}

std::ostream &operator<<(std::ostream &out, const some_object &o) {
    out << o.field_1;
    return out;
}

bool operator==(const some_object &so1, const some_object &so2) {
    return so1.field_1 == so2.field_1;
}

int main() {
    RBT<int> *a = new RBT<int>();
//    some_object o1 = {50};
//    some_object o2 = {30};
//    some_object o3 = {20};
//    some_object o4 = {40};
//    some_object o5 = {70};
//    some_object o6 = {60};
//    some_object o7 = {80};
//    a->add(o1);
//    a->add(o2);
//    a->add(o3);
//    a->add(o4);
//    a->add(o5);
//    a->add(o6);
//    a->add(o7);
    for(int i=0;i<10000000;i++){
    	a->add(i);
	}

    //a->show();
    cout<<a->findHeight();
    cout << endl;
//    cout << a->search(o1);
//    cout<<endl;
//
//    cout<<"Size: "<<a->getSize();
//
//    a->clear();
//    a->show();

    return 0;
}
