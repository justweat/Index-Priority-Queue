#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include "IndexPriorityQueue.h"

using namespace std;

int main() {

    vector<int> keys{};
    vector<double> vals{};

    IndexPQ::IndexPriorityQueue<int, double> pq(keys, vals, IndexPQ::IndexPQType{IndexPQ::IndexPQType::MinHeap});

    double lower_bound = -10000;
    double upper_bound = 10000;
    std::uniform_real_distribution<double> random_values(lower_bound,upper_bound);
    std::default_random_engine re(chrono::system_clock::now().time_since_epoch().count());


    for(int i = 0; i < 20000; ++i){

        double a_random_double = random_values(re);
        pair<int, double> t{i, a_random_double};
        pq.push(t.first, t.second);

//        pq.printIPQ();
//        cout << "\n";

        std::uniform_int_distribution<int> random_indices(0,i);
        int index = random_indices(re);
        a_random_double = random_values(re);
        pq.updateKey(index, a_random_double);

//        pq.printIPQ();
//        cout << "\n";

//        this_thread::sleep_for(chrono::seconds(2));

        auto tempPQ = pq;
        vector<double> val_test{};
        while(!tempPQ.empty()){
            val_test.emplace_back(tempPQ.frontValue());
            tempPQ.pop();
        }

        for(size_t j{1}; j < val_test.size(); ++j){
            if(val_test[j] < val_test[j - 1]){
                throw logic_error("Invalid heap");
            }
        }

        cout << "Passed... " << pq.size() << "\n";

    }

    return 0;
}
