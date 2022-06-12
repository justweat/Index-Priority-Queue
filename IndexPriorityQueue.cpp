//
// Created by justin on 6/12/22.
//

#include "IndexPriorityQueue.h"
namespace IndexPQ{

    template<class K, class V>
    function<bool(const V&, const V&)> MinHeapComparator =
            [](const V& o1, const V& o2){
                return o1 < o2;
            };

    template<class K, class V>
    function<bool(const V&, const V&)> MaxHeapComparator =
            [](const V& o1, const V& o2){
                return o1 > o2;
            };

    template<class K, class V>
    IndexPriorityQueue<K, V>::IndexPriorityQueue(const vector<K> &keys, const vector<V> &vals, IndexPQType type) {

        this->_keys.template emplace_back();
        this->_vals.template emplace_back();

        auto iter = keys.begin();
        while(iter != keys.end()){
            this->_keys.template emplace_back(*iter++);
        }
        iter = vals.begin();
        while(iter != vals.end()){
            vals.template emplace_back(*iter++);
        }

        this->_size = keys.size();

        if(type == IndexPQType::MinHeap){
            this->comparator = MinHeapComparator<K, V>;
        }else{
            this->comparator = MaxHeapComparator<K, V>;
        }

        heapify();
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapify() {
        size_t index = this->_size - 1;
        size_t mid = index >> 1;
        for(size_t i {index}; i > mid; --i){
            heapSink(i);
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapSink(size_t index) {
        size_t parent = index << 1;
    }

}

