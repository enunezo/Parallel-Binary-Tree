#include <iostream>
#include <thread>
#include "Tree.cpp"
#include <vector>

using namespace std;

void foo () {
  cout << "bar" << endl;
}

void bar (int x) {
  cout << "bar"<< x << endl;
}

class A {

	public:
	A (){

	}
	void asd () {
		cout<<"hello";
	} 

};

void petersonAlgorithm(vector<thread> interested) {
    static int * interested_threads = new int [interested.size()];
    for (int i = 0; i < interested.size(); ++i){
    	interested_threads[i] = i;
    }    
    static int * loser = new int [interested.size() -1];
    int other; 

    /*
	level[i] ← ℓ
    last_to_enter[ℓ] ← i
    while last_to_enter[ℓ] = i and there exists k ≠ i, such that level[k] ≥ ℓ
        wait
    */

    for (int i = 0; i < interested.size(); ++i){
    	for (int l = 0; l < interested.size()-1; ++l){
 			interested_threads[i] = l;
 			loser[l] = i;
 			while ( loser[l]==i && k!=i )
    	}
    }

    /*other = 1 - me;
    interested[me] = 1;
    loser = me;
    while (loser == me && interested[other] )
        ;

    /*critical section */
    //interested[me] = 0;
    //*/
}

int main () {

	vector<int> data = { 5, 3, 7, 2, 4, 6, 8 };
	binTree<int> t;


	// for ()
	t.insert(5);
	t.insert(3);
	t.insert(7);
	t.insert(2);
	t.insert(4);
	t.insert(6);
	t.insert(8);

	t.display();


	/*A ax;

	std::thread first (&A::asd, ax);     // spawn new thread that calls foo()
	std::thread second (bar, 0);  // spawn new thread that calls bar(0)

	std::cout << "main, foo and bar now execute concurrently...\n";

	// synchronize threads:
	first.join();                // pauses until first finishes
	second.join();               // pauses until second finishes

	std::cout << "foo and bar completed.\n";*/


	return 0;
}