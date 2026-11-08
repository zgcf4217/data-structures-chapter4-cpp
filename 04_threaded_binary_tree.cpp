// 来源：代码块33–40；threaded 命名空间隔离同名 Node/BTree。
#include "container_support.h"
namespace threaded {

//BTree类的前向说明
template <class elemType>
class BTree;
template <class elemType>
class Node
{   friend class BTree<elemType>;
    private:
        elemType data;       Node *left, *right;

        int leftFlag;  //用于标识是否线索,0时为孩子,1时为线索
        int rightFlag; //用于标识是否线索, 0时为孩子, 1时为线索
    public:
        Node(){data=elemType{}; left=NULL; right=NULL; leftFlag = 0; rightFlag=0;};
        Node(const elemType &e, Node* L=NULL, Node *R=NULL)
        {  data = e;
           left=L; right=R; leftFlag = 0; rightFlag=0;
        };
};

template <class elemType>
class BTree
{
    private:
        Node<elemType> *root;
        bool threaded_ = false;
        Node<elemType> *first;  //线索中的首结点

        void clear(Node<elemType>* p) {
            if (!p) return;
            if (p->leftFlag==0) clear(p->left);
            if (p->rightFlag==0) clear(p->right);
            delete p;
        }
    public:
        BTree(){root=NULL; first=NULL;}
        ~BTree(){clear(root);}
        BTree(const BTree&) = delete;
        BTree& operator=(const BTree&) = delete;
        void createTree(const elemType &stopFlag);//创建一棵二叉树
        bool isEmpty () { return (root == NULL);}// 二叉树为空返回true,否则返回false
        void ThreadMid();// 建立中序线索
        void ThreadMidVisit(); //在中序线索树上进行中序遍历
        void ThreadMidPreVisit(); //在中序线索树上进行前序遍历
};

template <class elemType>
void BTree<elemType>::ThreadMid()
{
    if (threaded_) return; // 重复调用不沿线索再次递归
    if (!root) { first=NULL;return;}
    threaded_=true;
    seqStack<Node<elemType> *> s1;
    seqStack<int> s2;
    Node<elemType> *p, *pre;
    int flag, zero=0, one=1;
    pre = NULL;   first = NULL;
    s1.push(root); s2.push(zero);

    while (!s1.isEmpty())
    {   flag = s2.top(); s2.pop();
        p = s1.top(); //读取栈顶元素

        if (flag==one)
        {   s1.pop();
            if (!first) first = p;
            if (p->right)
            //有右子压右子,没有进入下一轮循环
            {  s1.push(p->right);   s2.push(zero);   }
            //加中序遍历线索
            if (!p->left)
            {  p->leftFlag = 1; p->left = pre; }
            if (pre && (!pre->right))
            {  pre->rightFlag=1; pre->right = p;  }
            pre = p;
        }

        else
        {   s2.push(one);
            if (p->left)
            //有左子压左子
            {   s1.push(p->left); s2.push(zero); }
        }
    }//while
    //遍历序列中最后一个结点后继为空
    p->rightFlag=1;
}

template <class elemType>
void BTree<elemType>::ThreadMidVisit()
{   if (!threaded_) ThreadMid();
    if (!first) return;
    Node<elemType> *p;   p = first;
    while (p)
    {   cout<<p->data;
        //找p的后继元素
        if (p->rightFlag==0) //如果有右子
        {   p = p->right;
            //沿右子的左分支一路向左
            while (p->leftFlag==0)
                p = p->left; //左子为空时必为线索
        }
        else p = p->right; //无右子直接用后继线索
    }
    cout<<endl;  }

template <class elemType>
void BTree<elemType>::ThreadMidPreVisit()
{   if (!threaded_) ThreadMid();
    Node<elemType> *p;    p = root;
    while (p)
    {   cout<<p->data;
        if (p->leftFlag==0)  p = p->left;
        else
       {    if (p->rightFlag==0)   p = p->right;
            else
            {   while (p&&(p->rightFlag==1))
                p = p->right;
                if (!p) { cout<<endl; return; }
                p = p->right;
            }
        }
    }
    cout<<endl;
}

// 补齐课件仅声明的 createTree：与普通二叉树相同的按层次输入方式。
template<class elemType>
void BTree<elemType>::createTree(const elemType& stopFlag) {
    clear(root); root=nullptr; first=nullptr; threaded_=false;
    elemType e, el, er;
    if (!(cin>>e)) throw invalid_argument("缺少根结点");
    if (e==stopFlag) return;
    root=new Node<elemType>(e);
    seqQueue<Node<elemType>*> q;
    q.enQueue(root);
    while (!q.isEmpty()) {
        auto p=q.front(); q.deQueue();
        if (!(cin>>el>>er)) throw invalid_argument("缺少左右孩子");
        if (el!=stopFlag) { p->left=new Node<elemType>(el); q.enQueue(p->left); }
        if (er!=stopFlag) { p->right=new Node<elemType>(er); q.enQueue(p->right); }
    }
}
} // namespace threaded
