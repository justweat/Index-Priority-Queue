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
    IndexPriorityQueue<K, V>::IndexPriorityQueue(const vector<K> &keys, const vector<V> &vals) {
        this->_vals.template emplace_back();

        size_t n = vals.size();

        for(size_t i {1}; i <= n; ++i){
            this->_vals.template emplace_back(pair<K, V>{keys[i - 1], vals[i - 1]});
        }

        for(size_t i = 1; i <= n; ++i){
            this->_keyMap.insert(pair<K, size_t>{keys[i - 1], i});
        }
    }

    template<class K, class V>
    IndexPriorityQueue<K, V>::IndexPriorityQueue(const vector<K> &keys, const vector<V> &vals, IndexPQType type) : IndexPriorityQueue<K, V>(keys, vals){
        if(type == IndexPQType::MinHeap){
            this->comparator = MinHeapComparator<K, V>;
        }else{
            this->comparator = MaxHeapComparator<K, V>;
        }
        heapify();
    }

    template<class K, class V>
    IndexPriorityQueue<K, V>::IndexPriorityQueue(const vector<K> &keys, const vector<V> &vals, function<bool(V, V)> comparator) : IndexPriorityQueue(keys, vals){
        this->comparator = comparator;
        heapify();
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapify() {
        size_t size = this->_vals.size();
        size_t mid = size >> 1;
        for(size_t i {mid}; i > 0; --i){
            heapSink(i);
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapSwim(size_t index) {
        size_t parent = index >> 1;
        if(parent > 0){
            if(this->comparator(this->_vals[index].second, this->_vals[parent].second)){

                this->_keyMap.at(this->_vals[parent].first) = index;
                this->_keyMap.at(this->_vals[index].first) = parent;

                swap(this->_vals[index], this->_vals[parent]);

                heapSwim(parent);
            }
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapSink(size_t index) {
        size_t n = this->_vals.size();
        size_t left_child = index << 1;
        size_t right_child = left_child + 1;
        size_t variant;
        if(left_child < n && this->comparator(this->_vals[left_child].second,  this->_vals[index].second)){
            variant = left_child;
        }else{
            variant = index;
        }
        if(right_child < n && this->comparator(this->_vals[right_child].second,  this->_vals[variant].second)){
            variant = right_child;
        }
        if(variant != index){
            this->_keyMap.at(this->_vals[index].first) = variant;
            this->_keyMap.at(this->_vals[variant].first) = index;
            swap(this->_vals[index], this->_vals[variant]);
            heapSink(variant);
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K,V>::updateKey(const K& key, const V& val){
        size_t n = this->_vals.size();
        size_t pos = this->_keyMap.at(key);
        this->_vals[pos].second = val;
        size_t left_child = pos << 1;
        size_t right_child = left_child + 1;
        auto parent = pos >> 1;
        if(left_child < n && this->comparator(this->_vals[left_child].second, this->_vals[pos].second) || right_child < n && this->comparator(this->_vals[right_child].second,  this->_vals[pos].second)){
            heapSink(pos);
        }else if(parent > 0 && this->comparator(this->_vals[pos].second, this->_vals[parent].second)){
            heapSwim(pos);
        }
    }

    template<class K, class V>
   void IndexPriorityQueue<K, V>::push(const K &key, const V &val) {
       this->_vals.template emplace_back(pair<K,V>{key, val});
       size_t index = this->_vals.size() - 1;
       this->_keyMap.insert(pair<K, size_t>{key, index});
       heapSwim(index);
   }

   template<class K, class V>
   void IndexPriorityQueue<K, V>::pop(){
       pair<K, V> top = this->_vals[1];
       popHeapMaintenance();
   }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::popHeapMaintenance() {
        pair<K, V> back = this->_vals.back();
        this->_vals.pop_back();
        this->_vals[1] = back;
        this->_keyMap.at(back.first) = 1;
        heapSink(1);
    }

    template<class K, class V>
    V IndexPriorityQueue<K, V>::frontValue() {
        return this->_vals[1].second;
    }

    template<class K, class V>
    K IndexPriorityQueue<K, V>::frontKey() {
        return this->_vals[1].first;
    }

    template<class K, class V>
    pair<K, V> IndexPriorityQueue<K, V>::frontKV() {
        return this->_vals[1];
    }

    template<class K, class V>
    bool IndexPriorityQueue<K, V>::contains(const K &key) {
        return this->_keyMap.find(key) != this->_keyMap.end();
    }

    template<class K, class V>
    bool IndexPriorityQueue<K, V>::empty() {
        return this->_vals.size() == 1;
    }

    template<class K, class V>
    size_t IndexPriorityQueue<K, V>::size() {
        return this->_vals.size() - 1;
    }

    template class IndexPriorityQueue<int, double>;

}

