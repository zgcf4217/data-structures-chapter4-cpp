// 来源：代码块25–32；返回的树和编码需由调用者 delete[]。
#include "container_support.h"

//存储Huffman结点
template <class elemType>
struct HuffmanNode
{
    elemType data;
    double weight;
    int parent;
    int left, right;
};

//在所有父亲为0的元素中找最小值的下标
template <class elemType>
int minIndex(HuffmanNode<elemType> Bt[], int k, int m)
{   int i, min = -1; double minWeight = numeric_limits<double>::infinity();//用一个不可能且很大的权值
    for (i=m-1; i>k; i--)
    {   if ((Bt[i].parent==0)&&(Bt[i].weight < minWeight))
        {   min = i;     minWeight = Bt[min].weight;     }
    }
    if (min < 0) throw invalid_argument("找不到可用的哈夫曼结点");
    return min;
 }

template <class elemType>
HuffmanNode<elemType> *BestBinaryTree ( elemType a[],
double w[], int n)
{
    HuffmanNode<elemType> *BBTree;
    int first_min, second_min; //
    if (n<0 || n>numeric_limits<int>::max()/2) throw illegalSize();
    if (n==0) return nullptr;
    if (!a || !w) throw invalid_argument("空数组");
    for (int k=0; k<n; ++k)
        if (!isfinite(w[k]) || w[k]<0) throw invalid_argument("权值必须是有限非负数");
    int m=n*2; //共2n-1个结点,下标为0处不放结点
    int i, j;

   //在数组中从后往前存储叶子结点
    auto storage = make_unique<HuffmanNode<elemType>[]>(m);
    BBTree = storage.get();
    for (j=0; j<n; j++)
    {   i = m-1-j;
        BBTree[i].data = a[j];    BBTree[i].weight = w[j];
        BBTree[i].parent = 0;     BBTree[i].left = 0;
        BBTree[i].right = 0;
    }
    i = n-1; // i is the position which is ready for the first new node

    while (i!=0) //数组左侧尚有未用空间,即新创建的结点个数还不足
    {   first_min = minIndex(BBTree, i, m);
        BBTree[first_min].parent = i;
        second_min = minIndex(BBTree, i, m);
        BBTree[second_min].parent = i;

        BBTree[i].weight = BBTree[first_min].weight + BBTree[second_min].weight;
        BBTree[i].parent = 0;
        BBTree[i].left = first_min; BBTree[i].right = second_min;
        i--;
    }
    return storage.release();
}

template <class elemType>
char ** HuffmanCode ( HuffmanNode<elemType> BBTree[ ], int n )
//n为待编码元素的个数,BBTree数组为Huffman树,数组长度为2n
{
    if (n<0 || n>numeric_limits<int>::max()/2) throw illegalSize();
    if (n>0 && !BBTree) throw invalid_argument("空哈夫曼树");
    seqStack<char> s;
    char **HFCode;
    char zero = '0', one = '1';
    int m, i, j, parent, child;
    //为HFCode创建空间
    HFCode = new char* [n];
    for (i=0; i<n; i++)
        HFCode[i] = new char[n+1]; //每位元素编码最长n-1位,+1为n=1时储备
            m=2*n; //BBTree数组长度
    if (n==0) return HFCode; //没有元素
    if (n==1) //元素个数为1
    {
        HFCode[0][0] = '0', HFCode[0][1] = '\0';
        return HFCode;
    }

    for (i=m-1; i>=n; i--)
    {
        child=i;
        parent = BBTree[child].parent;
        while (parent!=0)
        {
            if (BBTree[parent].left==child)
                s.push(zero);
            else
                s.push(one);
            child = parent;
            parent = BBTree[parent].parent;
        }

   //在数组中从后往前存储叶子结点
        j=0;
        while (!s.isEmpty())
        {
            HFCode[m-i-1][j] = s.top();
            s.pop();
            j++;
        }
        HFCode[m-i-1][j] = '\0';
    }
    return HFCode;
}

