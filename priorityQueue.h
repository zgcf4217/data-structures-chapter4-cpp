#ifndef CH4_PRIORITY_QUEUE_H
#define CH4_PRIORITY_QUEUE_H
// 来源：代码块53–62；两种建堆算法均保留。
#include "container_support.h"

template <class elemType>
class priorityQueue
{   private:
        elemType *array;   int maxSize,currentLen;
        void doubleSpace(); //扩展队队列元素的存储空间
        void adjust(int hole); //调整下标为hole的元素,使成为小顶堆
        void build(int r); //递归调整

    public:
        priorityQueue(int size=10); //建立空优先级队列
        priorityQueue(elemType a[], int n);
        // 第三参数为 true 时采用课件的另一种递归建堆法。
        priorityQueue(elemType a[], int n, bool recursive);
        priorityQueue(const priorityQueue&) = delete;
        priorityQueue& operator=(const priorityQueue&) = delete; //建立非空优先级队列,即建小顶堆
        bool isEmpty() {return currentLen==0;};  //判断队空否
        bool isFull() {return (currentLen==maxSize-1);};  //判断队满否
        elemType front(); //读取队首元素的值,队首不变
        void enQueue(const elemType &x); //将x进队,成为新的队尾
        void deQueue(); //将队首元素出队
        ~priorityQueue (){delete []array; }; //释放队列元素所占据的动态数组
};

template <class elemType>
priorityQueue<elemType>::priorityQueue (int size) //建立空优先级队列
{
    if (size<2) throw illegalSize();
    array = new elemType[size]; //申请实际的队列存储空间
    if (!array) throw illegalSize();
    maxSize = size;
    currentLen = 0;
}

template <class elemType>
priorityQueue<elemType>::priorityQueue (elemType a[], int n) //建立优先级队列
{
    if (n<1 || n>numeric_limits<int>::max()-10 || !a) throw illegalSize();
    array = new elemType[n+10]; //申请实际的队列存储空间,多10,支持入队
    if (!array) throw illegalSize();
    maxSize = n+10;     currentLen = n;
    for (int i=1; i<=n; i++)    array[i] = a[i-1];
    for (int i=n/2; i>=1; i--)     adjust(i);   //首次建立小顶堆
}

template <class elemType>
priorityQueue<elemType>::priorityQueue (elemType a[], int n, bool recursive) //另一种方法建立优先级队列
{
    if (n<1 || n>numeric_limits<int>::max()-10 || !a) throw illegalSize();
    array = new elemType[n+10]; //申请实际的队列存储空间,多10,支持入队
    if (!array) throw illegalSize();
    maxSize = n+10;     currentLen = n;
    for (int i=0; i<n; i++) array[i+1]=a[i];
    if (recursive) build(1);
    else for (int i=n/2; i>=1; --i) adjust(i);
}

template <class elemType>
void priorityQueue<elemType>::build (int r) //调整为优先级队列
{
    if (r>currentLen/2) return;
    build(2*r);  //将左子树调整为堆
    build(2*r+1);  //将右子树调整为堆
    adjust(r);
}

template <class elemType>
void priorityQueue<elemType>:: adjust(int hole)
//反复向下调整hole的位置
{
    int minChild;      elemType x;
    x = array[hole];
    while (true)
    {    minChild = 2*hole;  //hole的左子下标

        if (minChild>currentLen) break;
        if (minChild+1<=currentLen) //hole还有右子
        if (array[minChild+1]< array[minChild])
               minChild++; //右子最小

        if (x<array[minChild]) break;
        array[hole] = array[minChild];
        hole = minChild;  //继续向下调整
    }

    array[hole] = x;
}
    //比较次数最多为：二叉树的高度

template <class elemType>
elemType priorityQueue<elemType>::front() //读取队首元素的值,队首不变
{    if (isEmpty()) throw outOfBound();    return array[1];  }

template <class elemType>
void priorityQueue<elemType>::deQueue() //将队首元素出队
{   if (isEmpty()) throw outOfBound();
    array[1] = array[currentLen];   currentLen--;
    if (currentLen>0) adjust(1);
}

template <class elemType>
void priorityQueue<elemType>::enQueue(const elemType &x)  //将x进队
{   elemType value=x;
    if (isFull()) doubleSpace();
    int hole ; //hole位置向上调整
    currentLen++;
    for (hole= currentLen; hole > 1 && value < array[ hole/ 2 ]; hole /= 2 )
        array[ hole ] = array[ hole / 2 ];
    array[ hole ] = value;
}
//比较次数最多为二叉树高度,故入队时间效率为$O(log_2⁡n$)

// 补齐课件仅声明的扩容函数。
template<class elemType>
void priorityQueue<elemType>::doubleSpace() {
    if (maxSize>numeric_limits<int>::max()/2) throw length_error("队列容量过大");
    auto replacement=make_unique<elemType[]>(maxSize*2);
    for (int i=1; i<=currentLen; ++i) replacement[i]=array[i];
    delete[] array;
    array=replacement.release();
    maxSize*=2;
}

#endif // CH4_PRIORITY_QUEUE_H
