#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 


using namespace std;

template<typename T>
struct Node{
	T data;
	Node<T> * sons[2];
	/*sons[0] left
	sons[1] rigth*/
	Node<T>(){
		sons[0] = NULL;
		sons[1] = NULL;
	} 
	Node<T>( T data_ ){
		data = data_;
		sons[0] = NULL;
		sons[1] = NULL;
	}
};


template<typename T>
class binTree{
public:
	Node<T> * head;
	binTree(){
		head = NULL;
	}

	bool find ( T data_, Node<T> ** & p ){
		for(p = &head; *p && data_ !=(*p)->data ; p = &(*p)->sons[data_ > (*p)->data]);
		return *p && (*p)->data == data_ ;
	} 

	bool insert( T data_ ){
		Node<T> ** p = &head;
		if ( find(data_,p) ){
			return false;
		}
		*p = new Node<T> (data_);
		return true;
	}

	Node<T> ** findYoungestSon(Node<T> ** & p){
		Node<T> ** tmp = p;
		tmp = &(*tmp)->sons[0];
		while(!!(*tmp)->sons[1]){
			tmp = &(*tmp)->sons[1];
		}
		return tmp;
	}

	bool remove(T data_){
		Node<T> ** p = &head;
		Node<T> * deleted;
		if ( !(find (data_,p) ) ){
			return false;
		}
		bool left, rigth;
		left = !!(*p)->sons[0];
		rigth = !!(*p)->sons[1];
		if ( left & rigth ){
			Node<T> ** tmp = findYoungestSon( p );
			(*p)->data = (*tmp)->data;
			p = tmp;
			left = !!(*p)->sons[0];
			rigth = !!(*p)->sons[1];
		}
		deleted = *p;
		*p = (*p)->sons[rigth>left];
		delete deleted;
		return true;
	}

	void _display (Node<T>** current, int ident) {
		if (*current) {
			_display( &(*current)->sons[0], ident+1 );
			for (int i=0; i<ident; i++) {
				cout << "    ";
			}
			cout << (*current)->data << endl;
			_display( &(*current)->sons[1], ident+1 );
		}
	}

	void display () {
		_display(&head, 0);
	}
	

	~binTree(){}
	
};