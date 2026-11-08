// 来源：第三章main.tex代码块1–4，合并课件模板定义与实现。
#ifndef CH3_SEQSTACK_H
#define CH3_SEQSTACK_H
#include "containerExceptions.h"
#include <limits>
#include <memory>

template <class elemType>
class seqStack
{private:
    elemType *array; //栈存储数组，存放实际的数据元素。
    int Top; //栈顶下标。
    int maxSize; //栈中最多能存放的元素个数。
    void doubleSpace();

public:
    seqStack(const seqStack&) = delete;
    seqStack& operator=(const seqStack&) = delete;
    seqStack(int initSize = 100); //初始化顺序栈
    bool isEmpty () { return ( Top == -1 ); } ; //栈空返回true,否则返回false。
    bool isFull () { return (Top == maxSize-1); };//栈满返回true,否则返回false。
    elemType top ();// 返回栈顶元素的值，不改变栈顶
    void push (const elemType &e );//将元素e压入栈顶，使其成为新的栈顶。
    void pop (); //将栈顶元素弹栈。
    ~seqStack(){ delete []array;}; //释放栈占用的动态数组
};

template <class elemType>
seqStack<elemType>::seqStack(int initSize)//初始化顺序栈
{   if (initSize<1) throw illegalSize();
    array = new elemType[initSize];
    if (!array) throw illegalSize();
    Top=-1;    maxSize=initSize;
}
template <class elemType>
elemType seqStack<elemType>::top ()// 返回栈顶元素的值，不改变栈顶
{   if (isEmpty()) throw outOfBound();
    return array[Top];
}

template <class elemType>
void seqStack<elemType>::push(const elemType &e )
//将元素e压入栈顶，使其成为新的栈顶元素。
{    elemType value=e; // 扩容前复制，避免传入内部元素的引用失效
     if (isFull()) doubleSpace();
      //栈满时从新分配2倍的空间，并将原空间内容拷入
     array[Top+1] = value;
     ++Top; // 新结点放入新的栈顶位置。
}
template <class elemType>
void seqStack<elemType>::pop()//将栈顶元素弹栈。
{   if (Top==-1) throw outOfBound();
    Top--;
}

// 课件只给声明：补齐容量翻倍，先成功复制，再释放旧空间。
template<class elemType>
void seqStack<elemType>::doubleSpace() {
    if (maxSize>std::numeric_limits<int>::max()/2) throw std::length_error("栈容量过大");
    auto replacement=std::make_unique<elemType[]>(maxSize*2);
    for (int i=0; i<=Top; ++i) replacement[i]=array[i];
    delete[] array;
    array=replacement.release();
    maxSize*=2;
}
#endif
