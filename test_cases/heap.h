// 从原完整tests.cpp拆分，保留原有全部断言。
#include "../priorityQueue.h"
#include <random>
#include "test_support.h"

void testHeap() {
    mt19937 random(42);
    uniform_int_distribution<int> values(-1000,1000);
    for (int n: {1,2,3,10,100,1000}) {
        vector<int> input;
        for (int i=0; i<n; ++i) input.push_back(values(random));
        priorityQueue<int> bottomUp(input.data(),n);
        priorityQueue<int> recursive(input.data(),n,true);
        priorityQueue<int> alternative(input.data(),n,false);
        priorityQueue<int> incremental(2);
        for (int value: input) incremental.enQueue(value);
        sort(input.begin(),input.end());
        for (int value: input) {
            require(bottomUp.front()==value,"自底向上建堆排序对照"); bottomUp.deQueue();
            require(recursive.front()==value,"递归建堆排序对照"); recursive.deQueue();
            require(alternative.front()==value,"构造函数另一分支"); alternative.deQueue();
            require(incremental.front()==value,"逐个入队与反复扩容"); incremental.deQueue();
        }
        require(bottomUp.isEmpty() && recursive.isEmpty() && incremental.isEmpty(),"出队至空");
    }
    priorityQueue<int> heap(2);
    require(heap.isEmpty(),"初始空堆");
    rejects([&]{heap.front();},"空堆读首");
    rejects([&]{heap.deQueue();},"空堆出队");
    heap.enQueue(3); require(heap.isFull(),"满堆");
    heap.deQueue(); heap.enQueue(2); require(heap.front()==2,"清空后再入队");
    rejects([]{priorityQueue<int> invalid(1);},"过小容量");
    rejects([]{priorityQueue<int> invalid(nullptr,0);},"空数组建堆");
    priorityQueue<double> floating; floating.enQueue(1.5); floating.enQueue(0.2);
    require(floating.front()==0.2,"小数模板实例化");
}
