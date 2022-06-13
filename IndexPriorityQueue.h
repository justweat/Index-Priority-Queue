//
// Created by justin on 6/12/22.
//

#ifndef INDEXPRIORITYQUEUE_INDEXPRIORITYQUEUE_H
#define INDEXPRIORITYQUEUE_INDEXPRIORITYQUEUE_H

#include <vector>
#include <unordered_map>
#include <iterator>
#include <functional>

namespace IndexPQ{
    using namespace std;

    enum class IndexPQType {MinHeap, MaxHeap};

    template<class K, class V>
    class IndexPriorityQueue {
    public:
        IndexPriorityQueue() = delete;
        IndexPriorityQueue(const vector<K> &keys, const vector<V> &vals, function<bool(V, V)>);
        IndexPriorityQueue(const vector<K> &keys, const vector<V>& vals, IndexPQType);
        IndexPriorityQueue(const vector<K> &keys, const vector<V>& vals);
        void push(const K& key, const V& val);
        bool contains(const K& key);
        size_t size();
        void updateKey(const K& key, const V& val);
        V frontValue();
        K frontKey();
        pair<K, V> frontKV();
        void pop();
        bool empty();
    private:
        void heapify();
        void heapSwim(size_t index);
        void heapSink(size_t index);
        void popHeapMaintenance();
//        size_t _size;
        unordered_map<K, size_t> _keyMap;
        vector<pair<K, V>> _vals;
        function<bool(const V&, const V&)> comparator;
    };
}



#endif //INDEXPRIORITYQUEUE_INDEXPRIORITYQUEUE_H
