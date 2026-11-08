// 来源：第三章main.tex代码块34–38，合并课件模板定义与实现。
#ifndef CH3_LINKQUEUE_H
#define CH3_LINKQUEUE_H
#include "containerExceptions.h"
#include <limits>
#include <memory>

template <class elemType>
class linkQueue;

template <class elemType>
class LinkQueueNode
{  friend class linkQueue<elemType>;
    private:
        elemType data;
        LinkQueueNode *next;
    public:
        LinkQueueNode(): data{}, next(nullptr) {}
        LinkQueueNode(const elemType &x, LinkQueueNode *p = nullptr)
        { data = x; next = p;}
};

template <class elemType>
class linkQueue
{ private:
        LinkQueueNode<elemType> *Front, *Rear;
    public:
        linkQueue(const linkQueue&) = delete;
        linkQueue& operator=(const linkQueue&) = delete;
        linkQueue(){Front = Rear = nullptr; }; //初始化链式队列，使得其为空队
        bool isEmpty() {return !Front; }; //判断队空否，空返回true，否则为false
        bool isFull(){return false; };  //判断队满否，满返回true，否则为false
        elemType front(); //读取队首元素的值，队首不变
        void enQueue(const elemType &x); //将x进队，成为新的队尾
        void deQueue(); //将队首元素出队
        ~linkQueue(); //释放队列元素所占据的动态数组
};

template <class elemType>
elemType linkQueue<elemType>::front() //读取队首元素的值，队首不变
{
    if (isEmpty()) throw outOfBound();
    return Front->data;
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)  //将x进队，成为新的队尾
{  if (!Rear)
        Front = Rear = new LinkQueueNode<elemType>(x);
    else
    { Rear->next = new LinkQueueNode<elemType>(x);
      Rear = Rear->next;
    }
}

template <class elemType>
void linkQueue<elemType>::deQueue() //将队首元素出队
{   if (isEmpty()) throw outOfBound();

    LinkQueueNode<elemType> *tmp = Front;
    Front = Front->next;
    delete tmp;

    if (!Front) Rear = nullptr;
}

template <class elemType>
linkQueue<elemType>::~linkQueue() //释放链式队列所占空间
{  LinkQueueNode<elemType> *p;     p= Front;

    while (p)
    {       Front=Front->next;
             delete p;    p=Front;
    }
}

#endif
