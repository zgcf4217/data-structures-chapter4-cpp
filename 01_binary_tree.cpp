// 来源：main.tex 代码块1–5、8–24、41–52；保留递归及非递归算法。
#include "container_support.h"

//BTree类的前向说明
template <class elemType>
class BTree;
template <class elemType>
class Node
{   friend class BTree<elemType>;
    private:
        elemType data;       Node *left, *right;
 public:
        Node(): data{}, left(NULL), right(NULL) {};
        Node(const elemType &e, Node* L=NULL, Node *R=NULL)
        {  data = e;  left=L; right=R; };
};

template <class elemType>
class BTree
{
    private:
        Node<elemType> *root;
        Node<elemType>* buildTree(const elemType pre[], int pl, int pr,
                                   const elemType mid[], int ml, int mr);
        int Size (Node<elemType> *t); //求以t为根的二叉树的结点个数。
        int Height (Node<elemType> *t); //求以t为根的二叉树的高度。
        void DelTree(Node<elemType> *t);//删除以t为根的二叉树
        void PreOrder(Node<elemType> *t);
        // 按前序遍历输出以t为根的二叉树的结点的数据值
        void InOrder(Node<elemType> *t);
        // 按中序遍历输出以t为根的二叉树的结点的数据值
        void PostOrder(Node<elemType> *t);
        // 按后序遍历输出以t为根的二叉树的结点的数据值

public:
        BTree(){root=NULL;}
        ~BTree(){ DelTree(); }
        BTree(const BTree&) = delete;
        BTree& operator=(const BTree&) = delete;
        void InOrder1() const; // 第一种非递归中序遍历，保留两种算法
        void PreOrderRecursive(){ PreOrder(root); }
        void InOrderRecursive(){ InOrder(root); }
        void PostOrderRecursive(){ PostOrder(root); }
        void buildFromTraversals(const vector<elemType>& pre, const vector<elemType>& mid);
        int priOver(char ch1, char ch2);
        void buildExpTree(const char* exp); // 单个数字、二元四则运算和括号
        int calExpTree();
        void createTree(const elemType &stopFlag);//创建一棵二叉树
        bool isEmpty () { return (root == NULL);}// 二叉树为空返回true,否则返回false
        Node<elemType> * GetRoot(){ return  root; }
        int Size (); //求二叉树的结点个数。
        int Height (); //求二叉树的高度。
        void DelTree();//删除二叉树
        void PreOrder();// 按前序遍历输出二叉树的结点的数据值
        void InOrder();// 按中序遍历输出二叉树的结点的数据值
        void PostOrder();// 按后序遍历输出二叉树的结点的数据值
        void LevelOrder();// 按层次遍历输出二叉树的结点的数据值
};

template <class elemType>
void BTree<elemType>::createTree(const elemType &stopFlag)
//创建一棵二叉树
{  seqQueue<Node<elemType>*> que;
    elemType e, el, er;     Node<elemType> *p, *pl, *pr;

    cout<<"Please input the value of the root: ";
    DelTree();
    if (!(cin>>e)) throw invalid_argument("缺少根结点");
    if (e== stopFlag) {return;}
    p = new Node<elemType>(e);
    root = p; //根结点为该新创建结点
    que.enQueue(p);

    while (!que.isEmpty())
    {   p = que.front();  //获得队首元素并出队
        que.deQueue();
        cout<<"Please input the value of the left child and the right child of "<<p->data
            <<" using "<< stopFlag <<" as no child: ";
        if (!(cin>>el>>er)) throw invalid_argument("缺少左右孩子");
        if (el!= stopFlag) //该结点有左孩子
        {     pl = new Node<elemType>(el);
             p->left = pl;    que.enQueue(pl);
        }
        if (er!= stopFlag) //该结点有右孩子
        {      pr = new Node<elemType>(er);
               p->right = pr;   que.enQueue(pr);
        }
    }
}

template <class elemType>   //公有
int BTree<elemType>::Size()
{ return Size(root); }

template <class elemType>  //私有
int BTree<elemType>::Size (Node<elemType> *t)
//得到以t为根二叉树结点个数,递归算法实现。
{  if (!t) return 0;
    return 1+Size(t->left)+Size(t->right);    }

template <class elemType>
int BTree<elemType>::Height()
{ return Height(root); }

template <class elemType>
int BTree<elemType>::Height(Node<elemType> *t)
//得到以t为根二叉树的高度,递归算法实现。
{
    if (!t) {
        return 0;
    }
    const int hl = Height(t->left);
    const int hr = Height(t->right);
    if (hl >= hr) {
        return 1 + hl;
    }
    return 1 + hr;
}

template <class elemType>
void BTree<elemType>::DelTree()
{  DelTree(root);    root = NULL;   }

template <class elemType>
void BTree<elemType>::DelTree(Node<elemType> *t)
//删除以t为根的二叉树,递归算法实现
{  if (!t) return;       DelTree(t->left);       DelTree(t->right);
    delete t;   }

template <class elemType>
void BTree<elemType>::LevelOrder()
//层次遍历二叉树算法的实现。
{   seqQueue<Node<elemType> *> que;
    Node<elemType> *p;

    if (!root) return; //二叉树为空
    que.enQueue(root);

while (!que.isEmpty())
    {
        p = que.front();
        que.deQueue();
        cout << p->data;
        if (p->left) que.enQueue(p->left);
        if (p->right) que.enQueue(p->right);
    }
    cout << endl;
}

template <class elemType>
void BTree<elemType>::PreOrder(Node<elemType> *t)
//前序遍历以t为根二叉树递归算法的实现。
{  if (!t) return;
    cout << t->data;

    PreOrder(t->left);
    PreOrder(t->right);
}

template <class elemType>
void BTree<elemType>:: PreOrder()
{
    if (!root) return;
    Node<elemType> *p;
    seqStack<Node<elemType> *> s;
    s.push(root);
    while (!s.isEmpty())
    {
        p = s.top(); s.pop();
        cout << p->data;
        if (p->right) s.push(p->right);
        if (p->left) s.push(p->left);
    }
    cout << endl;
}

template <class elemType>
void BTree<elemType>::InOrder(Node<elemType> *t)
//中序遍历以t为根二叉树递归算法的实现。
{  if (!t) return;

    InOrder(t->left);
    cout << t->data;
    InOrder(t->right);
}

template <class elemType>
void BTree<elemType>::InOrder1() const
{  if (!root) return;
    seqStack<Node<elemType> *> s;  s.push(root);
    Node<elemType> *p;  p=root;
while(p->left) {s.push(p->left); p=p->left;}

while( !s.isEmpty())
    {  p=s.top(); s.pop();   cout<<p->data;
       if ( p->right)  { s.push(p->right);  p=p->right;
                        while(p->left) {s.push(p->left); p=p->left;}
                        }
     }
}

template <class elemType>
void BTree<elemType>:: InOrder()
{
    if (!root) return;
    seqStack<Node<elemType> *> s1;
    seqStack<int> s2;
    Node<elemType> *p;
    int flag;
    int zero = 0, one = 1;
    p = root;
    s1.push(p); s2.push(zero);
    while (!s1.isEmpty())
    {   flag = s2.top(); s2.pop();
        p = s1.top();  //读取栈顶元素
        if (flag == 1)  //二次出栈,则访问
        {
            s1.pop();
            cout << p->data;

            if (!p->right) continue;
            //有右子压右子,没有进入下一轮循环
            s1.push(p->right);
            s2.push(zero);
        }
        else  //首次出栈,则入栈,标1
        {
            s2.push(one);
            if (p->left)  //有左子压左子
            {
                s1.push(p->left);
                s2.push(zero);
            }
        }
    }  //end while
    cout << endl;
}  //end

template <class elemType>
void BTree<elemType>::PostOrder(Node<elemType> *t)
//后序遍历以t为根二叉树递归算法的实现。
{
    if (!t) return;
    PostOrder(t->left);
    PostOrder(t->right);
    cout << t->data;
}

template <class elemType>
void BTree<elemType>:: PostOrder()
//后序遍历的非递归算法实现。
{
    if (!root) return;
    Node<elemType> *p;
    seqStack<Node<elemType> *> s1;
    seqStack<int> s2;
    int zero = 0, one = 1, two = 2;
    int flag;
    s1.push(root);
    s2.push(zero);
    while (!s1.isEmpty())
    {
        flag = s2.top(); s2.pop();
        p = s1.top();
        switch(flag) {
            case 2:

                s1.pop();
                cout << p->data;
                break;
            case 1:
                s2.push(two);
                if (p->right) {
                    s1.push(p->right);
                    s2.push(zero);}
                break;
            case 0:
                s2.push(one);
                if (p->left) {
                    s1.push(p->left);
                    s2.push(zero);}
                break;
        };  //switch
    }  //while
    cout << endl;}  //end

template <class elemType>
Node<elemType> *BTree<elemType>::
buildTree(const elemType pre[], int pl, int pr,
          const elemType mid[], int ml, int mr)
//pre数组存储了前序遍历序列,pl为序列左边界下标,
//pr为序列右边界下标。
//mid数组存储了中序遍历序列,ml为序列左边界下标,
//mr为序列右边界下标。
{
    Node<elemType> *p;
    int i, pos, num;
    int lpl, lpr, lml, lmr;  //左子树中前序的左右边界、中序的左右边界
    int rpl, rpr, rml, rmr;  //右子树中前序的左右边界、中序的左右边界

    if (pl > pr) return NULL;
    // 先校验当前子区间，再分配结点。

    //找根在中序中的位置和左子树中结点个数
    for (i = ml; i <= mr; i++)
        if (mid[i] == pre[pl]) break;
    if (i > mr || pr-pl != mr-ml) throw invalid_argument("遍历序列不一致");
    p = new Node<elemType>(pre[pl]);
    try {
    pos = i;  //子树根在中序中的下标
    num = pos-ml;  //子树根的左子树中结点的个数
    //找左子树的前序、中序序列下标范围
    lpl = pl + 1; lpr = pl + num;

    lml = ml; lmr = pos - 1;
    p->left = buildTree(pre, lpl, lpr, mid, lml, lmr);
    //找右子树的前序、中序序列下标范围
    rpl = pl + num + 1; rpr = pr;
    rml = pos + 1; rmr = mr;
    p->right = buildTree(pre, rpl, rpr, mid, rml, rmr);
    return p;
    } catch (...) { DelTree(p); throw; }
}

template <class elemType>
int BTree<elemType>::priOver(const char ch1, const char ch2)
//比较操作符优先级的函数,ch1为新读入操作符,ch2为操作符栈栈顶操作符
//当ch1优先级比ch2高,函数返回1; 低或相同时返回-1;右、左括号时返回0。
{   switch (ch1)
    {   case '(': return 1; //左括号优先级在栈外是最高
        case ')': if (ch2!='(') return -1;
                  //右括号和栈顶四则运算操作符比,总是优先级最低
                  else return 0; //右括号和栈顶的左括号比,优先级一样
        case '*':
        case '/': if ((ch2=='*') || (ch2=='/')) return -1; //相同运算,栈中优先级高
                  else return 1; //只要栈顶不是乘除,优先级肯定比栈顶操作符高
        case '+':
        case '-': //只要栈顶不是hash和左括号,都比栈顶优先级高
                  if ((ch2 =='#')||(ch2 == '(')) return 1;
                  else  return -1;
    };
    throw invalid_argument("不支持的运算符");
}

//根据一个表达式字符串建立表达式树2
template <class elemType>
void BTree<elemType>::buildExpTree(const char *exp)
{
    if (!exp) throw invalid_argument("空表达式指针");
    string compact;
    for (const char* q=exp; *q; ++q)
        if (!isspace(static_cast<unsigned char>(*q))) compact += *q;
    bool needOperand=true;
    int depth=0;
    for (char c: compact) {
        if (c>='0' && c<='9') {
            if (!needOperand) throw invalid_argument("仅支持单个数字操作数");
            needOperand=false;
        } else if (c=='(') {
            if (!needOperand) throw invalid_argument("缺少运算符");
            ++depth;
        } else if (c==')') {
            if (needOperand || --depth<0) throw invalid_argument("括号不匹配");
        } else if (c=='+' || c=='-' || c=='*' || c=='/') {
            if (needOperand) throw invalid_argument("缺少操作数，不支持一元运算");
            needOperand=true;
        } else throw invalid_argument("非法字符");
    }
    if (needOperand || depth) throw invalid_argument("表达式不完整");
    DelTree();
    exp=compact.c_str();
    vector<unique_ptr<Node<elemType>>> allocated;
    auto makeNode = [&](elemType e, Node<elemType>* l=nullptr, Node<elemType>* r=nullptr) {
        allocated.push_back(make_unique<Node<elemType>>(e,l,r));
        return allocated.back().get();
    };
    seqStack<char> opStack; //操作符栈
    seqStack<Node<elemType>*> subTStack;
    //子树栈

    Node<elemType> *p, *left, *right;
    char hash = '#', ch;
    opStack.push(hash);

     while (*exp)
    {
        if ((*exp>='0')&&(*exp<='9'))
        //读入数字
        {
            p = makeNode(*exp);
            subTStack.push(p);
        }
        else //读入操作符（包括括号)
        {
            ch = opStack.top(); //读opStack栈顶

         //将opStack栈顶所有比新读入操作符优先级
         //高的弹出来处理
            while (priOver(*exp,ch)==-1)
            {
                opStack.pop(); //opStack栈顶出栈
                right = subTStack.top(); subTStack.pop();
                left   = subTStack.top(); subTStack.pop();
                p = makeNode(ch, left, right);
                //构建新操作数结点

                subTStack.push(p); //新操作数压栈
                ch = opStack.top();
            }

    //当前opStack栈顶不比新读入的操作符
    //优先级高
            if (priOver(*exp,ch)==0)
            //优先级一样,即分别为右左括号
            opStack.pop(); //左括号弹出扔掉即可。
            else opStack.push(*exp); //opStack栈顶
            //操作符比新读入的操作符优先级低,
            //新读入操作符直接压栈
        };
        exp++;
    }

     //将opStack栈中所有操作符弹空
    ch = opStack.top();
    while (ch!='#')
    {
        opStack.pop();
        right = subTStack.top(); subTStack.pop();
        left  = subTStack.top(); subTStack.pop();
        p = makeNode(ch, left, right);
        subTStack.push(p);

        ch = opStack.top();
    }
    //操作数栈numStack中剩余的唯一的
    //元素即二叉树的根
    root = subTStack.top(); subTStack.pop();
    for (auto& node: allocated) node.release();
}

//用后序遍历方法计算一个表达式树的值
template <class elemType>
int BTree<elemType>::calExpTree()
{
    //后序遍历
    if (!root) return 0;

    Node<elemType> *p;
    seqStack<Node<elemType> *> s1;
    seqStack<int> s2;

    seqStack<int> numStack;

    int zero=0, one=1, two=2;
    int flag, num=0, num1, num2;

    s1.push(root); s2.push(zero);
    while (!s1.isEmpty())
    {
        flag = s2.top(); s2.pop();
        p = s1.top();
        switch(flag)
        {

 case 2:
    s1.pop();
    //cout << p->data;
    //访问结点时,开始处理：
    //见数字压数字栈,见操作符弹
    //两数字计算,计算结果压数字栈
    if ((p->data>='0')&&(p->data<='9'))
    {
           num = p->data-'0';
           numStack.push(num);
    }

    else
    {   num2 = numStack.top(); numStack.pop();
        num1 = numStack.top(); numStack.pop();
        long long result=0;
        switch (p->data)
        {
           case '+': result = static_cast<long long>(num1)+num2; break;
           case '-': result = static_cast<long long>(num1)-num2; break;
           case '*': result = static_cast<long long>(num1)*num2; break;
           case '/':
             if (num2==0) throw domain_error("除数不能为零");
             result = static_cast<long long>(num1)/num2; break;
           default: throw invalid_argument("不是合法表达式树");
        }
        if (result<numeric_limits<int>::min() || result>numeric_limits<int>::max())
            throw overflow_error("表达式计算超出 int 范围");
        num=static_cast<int>(result);
        numStack.push(num);
    }
    break;

case 1: s2.push(two);
        if (p->right)
        {
            s1.push(p->right);
            s2.push(zero);
        }
        break;
case 0: s2.push(one);
        if (p->left)
        {
            s1.push(p->left);
            s2.push(zero);
        }
        break;

           };//switch
    }//while
    //get the result of the expression tree
    num = numStack.top(); numStack.pop();
    return num;
}

// 补充安全入口：元素必须互异；辅助函数沿用课件的闭区间划分。
template<class elemType>
void BTree<elemType>::buildFromTraversals(const vector<elemType>& pre,
                                         const vector<elemType>& mid) {
    if (pre.size()!=mid.size() || pre.size()>static_cast<size_t>(numeric_limits<int>::max()))
        throw invalid_argument("遍历序列长度不一致或过长");
    for (size_t i=0; i<pre.size(); ++i) {
        if (count(pre.begin(), pre.end(), pre[i])!=1 || count(mid.begin(), mid.end(), pre[i])!=1)
            throw invalid_argument("遍历序列必须包含相同且互异的元素");
    }
    int n=static_cast<int>(pre.size());
    Node<elemType>* newRoot=buildTree(pre.data(),0,n-1,mid.data(),0,n-1);
    DelTree();
    root=newRoot;
}
