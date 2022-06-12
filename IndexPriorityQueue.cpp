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
            heapSwim(i);
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapSwim(size_t index) {
        size_t parent = index >> 1;
        if(parent > 0){
            if(this->comparator(this->_vals[index], this->_vals[parent])){

                swap(this->_vals[index], this->_vals[parent]);

                this->_keyMap.at(parent) = index;
                this->_keyMap.at(index) = parent;

                heapSwim(parent);
            }
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapSink(size_t index) {
        size_t n = this->v_cont.size();
        size_t left_child = index << 1;
        size_t right_child = left_child + 1;
        size_t variant;
        if(left_child < n && this->comparator(this->v_cont[left_child],  this->v_cont[index])){
            variant = left_child;
        }else{
            variant = index;
        }
        if(right_child < n && this->comparator(this->v_cont[variant],  this->v_cont[right_child])){
            variant = right_child;
        }
        if(variant != index){
            swap(this->_vals[index], this->_vals[variant]);
            this->_keyMap.at(index) = variant;
            this->_keyMap.at(variant) = index;
            heapSink(variant);
        }
    }

}

