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
        this->_heap.template emplace_back();

        size_t n = vals.size();

        for(size_t i {1}; i <= n; ++i){
            this->_heap.template emplace_back(pair<K, V>{keys[i - 1], vals[i - 1]});
        }

        for(size_t i = 1; i <= n; ++i){
            this->_keyMap.insert(pair<K, size_t>{keys[i - 1], i});
        }
    }

    template<class K, class V>
    IndexPriorityQueue<K, V>::IndexPriorityQueue(const vector<K> &keys, const vector<V> &vals, IndexPQType type) : IndexPriorityQueue<K, V>(keys, vals){
        if(type == IndexPQType::MinHeap){
            this->_comparator = MinHeapComparator<K, V>;
        }else{
            this->_comparator = MaxHeapComparator<K, V>;
        }
        heapify();
    }

    template<class K, class V>
    IndexPriorityQueue<K, V>::IndexPriorityQueue(const vector<K> &keys, const vector<V> &vals, function<bool(V, V)> comparator) : IndexPriorityQueue(keys, vals){
        this->_comparator = comparator;
        heapify();
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapify() {
        size_t size = this->_heap.size();
        size_t mid = size >> 1;
        for(size_t i {mid}; i > 0; --i){
            heapSink(i);
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapSwim(size_t index) {
        size_t parent = index >> 1;
        if(parent > 0){
            if(this->_comparator(this->_heap[index].second, this->_heap[parent].second)){

                this->_keyMap.at(this->_heap[parent].first) = index;
                this->_keyMap.at(this->_heap[index].first) = parent;

                swap(this->_heap[index], this->_heap[parent]);

                heapSwim(parent);
            }
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::heapSink(size_t index) {
        size_t n = this->_heap.size();
        size_t left_child = index << 1;
        size_t right_child = left_child + 1;
        size_t variant;
        if(left_child < n && this->_comparator(this->_heap[left_child].second, this->_heap[index].second)){
            variant = left_child;
        }else{
            variant = index;
        }
        if(right_child < n && this->_comparator(this->_heap[right_child].second, this->_heap[variant].second)){
            variant = right_child;
        }
        if(variant != index){
            this->_keyMap.at(this->_heap[index].first) = variant;
            this->_keyMap.at(this->_heap[variant].first) = index;
            swap(this->_heap[index], this->_heap[variant]);
            heapSink(variant);
        }
    }

    template<class K, class V>
    void IndexPriorityQueue<K,V>::updateKey(const K& key, const V& val){
        if(!this->contains(key)){
            throw logic_error("IndexPQ does not contain key for updating");
        }
        if(this->empty()){
            throw logic_error("IndexPQ is empty");
        }
        size_t n = this->_heap.size();
        size_t pos = this->_keyMap.at(key);
        this->_heap[pos].second = val;
        size_t left_child = pos << 1;
        size_t right_child = left_child + 1;
        auto parent = pos >> 1;
        if(left_child < n && this->_comparator(this->_heap[left_child].second, this->_heap[pos].second) || right_child < n && this->_comparator(this->_heap[right_child].second, this->_heap[pos].second)){
            heapSink(pos);
        }else if(parent > 0 && this->_comparator(this->_heap[pos].second, this->_heap[parent].second)){
            heapSwim(pos);
        }
    }

    template<class K, class V>
   void IndexPriorityQueue<K, V>::push(const K &key, const V &val) {
       this->_heap.template emplace_back(pair<K,V>{key, val});
       size_t index = this->_heap.size() - 1;
       this->_keyMap.insert(pair<K, size_t>{key, index});
       heapSwim(index);
   }

   template<class K, class V>
   void IndexPriorityQueue<K, V>::pop(){
       if(this->empty()){
           throw logic_error("IndexPQ is empty");
       }
       pair<K, V> top = this->_heap[1];
       popHeapMaintenance();
   }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::popHeapMaintenance() {
        pair<K, V> back = this->_heap.back();
        this->_heap.pop_back();
        this->_heap[1] = back;
        this->_keyMap.at(back.first) = 1;
        heapSink(1);
    }

    template<class K, class V>
    V IndexPriorityQueue<K, V>::frontValue() {
        if(this->empty()){
            throw logic_error("IndexPQ is empty");
        }
        return this->_heap[1].second;
    }

    template<class K, class V>
    K IndexPriorityQueue<K, V>::frontKey() {
        if(this->empty()){
            throw logic_error("IndexPQ is empty");
        }
        return this->_heap[1].first;
    }

    template<class K, class V>
    pair<K, V> IndexPriorityQueue<K, V>::frontKV() {
        if(this->empty()){
            throw logic_error("IndexPQ is empty");
        }
        return this->_heap[1];
    }

    template<class K, class V>
    bool IndexPriorityQueue<K, V>::contains(const K &key) {
        return this->_keyMap.find(key) != this->_keyMap.end();
    }

    template<class K, class V>
    bool IndexPriorityQueue<K, V>::empty() {
        return this->_heap.size() == 1;
    }

    template<class K, class V>
    size_t IndexPriorityQueue<K, V>::size() {
        return this->_heap.size() - 1;
    }

    template<class K, class V>
    V IndexPriorityQueue<K, V>::keyValue(const K &key) {
        if(!this->contains(key)){
            throw logic_error("IndexPQ does not contain key for updating");
        }
        return this->_heap[this->_keyMap.at(key)].second;
    }

    template<class K, class V>
    vector<K> IndexPriorityQueue<K, V>::keysWithValue(const V &val) {
        auto iter = this->_heap.begin();
        auto end = this->_heap.end();
        vector<K> keys{};
        while(iter != end){
            if(iter->second == val){
                keys.template emplace_back(iter->second);
            }
            ++iter;
        }
        return keys;
    }

    template<class K, class V>
    void IndexPriorityQueue<K, V>::printIPQ() {
        IndexPriorityQueue<K,V> tempIPQ = *this;
        while(!tempIPQ.empty()){
            cout << tempIPQ.frontKey() << " -> " << tempIPQ.frontValue() << "\n";
            tempIPQ.pop();
        }
    }

//    template<class K, class V>
//    ostream &operator<<(ostream &os, const IndexPriorityQueue<K, V> &ipq) {
//        return IndexPriorityQueue<K,V>::printIPQ();
//    }

    template class IndexPriorityQueue<int, double>;

}

