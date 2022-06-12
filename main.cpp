#include <iostream>
#include <vector>
#include "IndexPriorityQueue.h"

using namespace std;

int main() {

    vector<int> keys{1,2,3,4,5,6,7,8,9,10};
    vector<double> vals{4.4,10.10,6.6,2.2,1.1,7.7,8.8,9.9,3.3,5.5};

    IndexPQ::IndexPriorityQueue<int, double> pq(keys, vals, IndexPQ::IndexPQType{IndexPQ::IndexPQType::MinHeap});
    while(!pq.empty()){
        cout << pq.peekKV().first << " " << pq.peekKV().second << endl;
        pq.pop();
    }

    return 0;
}
