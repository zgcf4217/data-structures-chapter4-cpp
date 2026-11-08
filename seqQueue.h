// 来源：第三章main.tex代码块29–33，合并课件模板定义与实现。
#ifndef CH3_SEQQUEUE_H
#define CH3_SEQQUEUE_H
#include "containerExceptions.h"
#include <limits>
#include <memory>

template <class elemType>
class seqQueue
{    private:
        elemType *array;
        int maxSize;
        int Front, Rear;
        void doubleSpace(); //扩展队队列元素的存储空间为原来的2倍

    public:
        seqQueue(const seqQueue&) = delete;
        seqQueue& operator=(const seqQueue&) = delete;
        seqQueue(int size=10); //初始化队列元素的存储空间
        bool isEmpty(); //判断队空否，空返回true，否则为false
        bool isFull();  //判断队满否，满返回true，否则为false
        elemType front(); //读取队首元素的值，队首不变
        void enQueue(const elemType &x); //将x进队，成为新的队尾
        void deQueue(); //将队首元素出队
        ~seqQueue(); //释放队列元素所占据的动态数组
};

template <class elemType>
seqQueue<elemType>::seqQueue(int size) //初始化队列元素的存储空间
{
    if (size<2) throw illegalSize();
    array = new elemType[size]; //申请实际的队列存储空间
    if (!array) throw illegalSize();
    maxSize = size;
    Front = Rear = 0;
}

template <class elemType>
bool seqQueue<elemType>::isEmpty()  //判断队空否，空返回true，否则为false
{return Front == Rear;}

template <class elemType>
bool seqQueue<elemType>::isFull() //判断队满否，满返回true，否则为false
{return (Rear+1)%maxSize == Front;}

template <class elemType>
elemType seqQueue<elemType>::front() //读取队首元素的值，队首不变
{    if (isEmpty()) throw outOfBound();    return array[Front];  }

template <class elemType>
void seqQueue<elemType>::enQueue(const elemType &x)  //将x进队，成为新的队尾
{  elemType value=x;
    if (isFull()) doubleSpace();
    array[Rear]=value;
    Rear = (Rear+1)%maxSize;
}
template <class elemType>
void seqQueue<elemType>::deQueue() //将队首元素出队
{  if (isEmpty()) throw outOfBound();
    Front = (Front+1)%maxSize;
}

// Front指向队首，Rear指向下一可写位置，预留一个空槽。
// 扩容必须按逻辑顺序复制，而非直接复制物理下标。
template<class elemType>
void seqQueue<elemType>::doubleSpace() {
    if (maxSize>std::numeric_limits<int>::max()/2) throw std::length_error("队列容量过大");
    int count=Rear>=Front ? Rear-Front : maxSize-(Front-Rear);
    auto replacement=std::make_unique<elemType[]>(maxSize*2);
    for (int i=0; i<count; ++i) replacement[i]=array[(static_cast<long long>(Front)+i)%maxSize];
    delete[] array;
    array=replacement.release();
    Front=0; Rear=count; maxSize*=2;
}
template<class elemType>
seqQueue<elemType>::~seqQueue() { delete[] array; }
#endif
