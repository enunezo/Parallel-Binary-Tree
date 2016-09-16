#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h> 


using namespace std;


mutex * blockPointers = new mutex[10];

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

	bool insert( T data_, int pos ){
		Node<T> ** p = &head;
		if ( find(data_,p) ){
			return false;
		}
		int tmpMutexPos = pos%10;
		blockPointers[tmpMutexPos].lock();
		*p = new Node<T> (data_);
		blockPointers[tmpMutexPos].unlock();
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


/*void petersonAlgorithm(int me, vector<thread> interested) {
    static int loser;
    static bool * interested_threads = new bool [interested.size()];
    for (int i = 0; i < interested.size(); ++i){
    	interested_threads[i] = 0;
    }    
    int other; 

    /*other = 1 - me;
    interested[me] = 1;
    loser = me;
    while (loser == me && interested[other] )
        ;

    
    interested[me] = 0;
    
}
*/

int main(){
	binTree<int> a;
	srand (time(NULL));
	vector<thread> threads; 
	for (int i = 0; i < 100; ++i){
		int tmp = rand() % 100 + 1;
		thread x(a.insert,tmp,i);
		threads.pushback(x);
	}

	for (int i = 0; i < threads.size(); ++i){
		threads.at(i).join();
	}



	a.display();

	cout<<"hello world!"<<endl;
	return 0;
}