#include <iostream>
#include "time.h"
#include <sstream>
#include <cmath>
 using namespace std;
template <typename T>
class BST{
	public:
		
	struct Node{
	Node *left, *right;
	T data;
	};
	
//punkt a dodanie elementu
void add(const T& dane){
	root=add(dane,root);
	}
	
//
//punkt b szukanie elementu
//Node* search(const T dane){
//	root=search(dane,root);
//}
//


//punkt c usuwanie szukanego elementu
void remove(const T& dane){
	root=remove(dane,root);
}
//punkt h zwrocenie drzewa
void show(){ 
	inOrder(root);
	
}

	
	
private:
	int size;
	Node* root;	
//przyklad a dodanie elementu	
Node* add(const T& dane,Node* n){
	if(n==NULL) {
		n=new Node;
		n->data=dane;	
		n->left=NULL;
		n->right=NULL;		
	}
	else if(dane<n->data)	n->left=add(dane,n->left);
	else if(n->data<dane) 	n->right=add(dane,n->right);
	return n;
} 	

//przyklad b wyszukiwanie
public:
Node* search(const T dane){
	Node* n=new Node();
	n=root;
	while(n){
	if(dane<n->data) n=n->left;
	else if(n->data<dane) n=n->right;
	else break;
	}
	return n;


}

//przyklad c usuwanie znalezionego wezla
Node* remove(const T dane,Node* n){
	n=new Node();
	n->data=dane;
	if(n==NULL) return n;
	else if (dane<n->data) n->left=remove(dane,n->left);
	else if (n->data<dane) n->right=remove(dane,n->right);
	
	
	else{
		if(n->left==NULL&&n->right==NULL){//zero galezi
			delete n;
			n=NULL;
		}else if(root->left == NULL){//jedna galaz 
			 Node *temp = n;
			n=n->right;
			delete temp;
		}else if(root->right == NULL){
			 Node *temp = n;
			n=n->left;
			delete temp;
		}
		else{//dwie galezie
			Node *temp = findMin(root->right);
			n->data=temp->data;
			n->right=remove(temp->data,root->right);
		}
	}
	return n;
}
Node* findMin(Node* n){
	if(n==nullptr) return NULL;
	else if(n->left==nullptr) return n;
	else return findMin(n->left);
}
private:

//przyklad d przejscie pre-order drzewa

//przyklad e przejscie in-order drzewa 
void inOrder(Node* it){
	if(it==NULL) return;
	inOrder(it->left);
	cout<<it->data<<" ";
	inOrder(it->right);

}
//przyklad f czyszczenie drzewa 
Node* clear(Node* n){
	if (n==NULL) return NULL;
	else{
		clear(n->left);
		clear(n->right);
		delete n;
	}
	return NULL;
}	
//przyklad g wyznaczanie wysokosci drzewa
Node* height(Node* n){
	Node* pomleft,pomright;
	
	if(n=NULL) return -1;
	pomleft=height(n->left);
	pomright=height(n->right);
	if(pomleft>pomright) return pomleft;
	else return pomright;
}

	
};
struct some_object{
	int field_1;
	//char field_2;	
	};
	
bool operator <(const some_object&a,const some_object& b){
	return a.field_1<b.field_1||a.field_1==b.field_1;//&&a.field_2<b.field_2;
}


std::ostream&operator<<(std::ostream& out, const some_object&o ){
	out<< o.field_1;//<<" "<<o.field_2;
	return out;
}	
bool operator==(const some_object& so1, const some_object& so2){
		return so1.field_1==so2.field_1;// && so1.field_2==so2.field_2 ;
	}	

 	
int main(){
	BST<some_object> * a = new BST<some_object>();
		some_object o1={50};
		some_object o2={30};
		some_object o3={20};
		some_object o4={40};
		some_object o5={70};
		some_object o6={60};
		some_object o7={80};
	a->add(o1);
	a->add(o2);
	a->add(o3);
	a->add(o4);
	a->add(o5);
	a->add(o6);
	a->add(o7);
	a->show();
	cout<<endl;
	//cout<<a->search(o4);
	//a->remove(o4);
	a->show();
	cout<<endl;
	//a->clear()
	
		 		
}
