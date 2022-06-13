#include <iostream>
#include <vector>
#include "IndexPriorityQueue.h"

using namespace std;

int main() {

    vector<int> keys{1,2,3,4,5,6,7,8,9,10,11};
    vector<double> vals{4.4,10.10,6.6,2.2,1.1,7.7,8.8,9.9,3.3,5.5,-2.2};

    IndexPQ::IndexPriorityQueue<int, double> pq(keys, vals, IndexPQ::IndexPQType{IndexPQ::IndexPQType::MinHeap});

    pq.updateKey(2, -1);
    pq.updateKey(11, 500);
    pq.push(12, -5);
    pq.push(13, 3.4);
    pq.updateKey(13, -10);
    pq.push(14, 5.6);
    pq.updateKey(14, -1000);
    pq.updateKey(14, 1000);

    while(!pq.empty()){
        cout << pq.frontKV().first << " " << pq.frontKV().second << endl;
        pq.pop();
    }

    return 0;
}
