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
        void push(const K& key, const V& val);
        void contains(const K& key);
        size_t size();
    private:
        void heapify();
        void heapSwim(size_t index);
        void heapSink(size_t index);
        size_t _size;
        vector<K> _keys;
        vector<V> _vals;
        function<bool(const V&, const V&)> comparator;
    };
}



#endif //INDEXPRIORITYQUEUE_INDEXPRIORITYQUEUE_H
