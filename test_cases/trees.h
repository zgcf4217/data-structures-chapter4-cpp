// 从原完整tests.cpp拆分，保留原有全部断言。
#include "../01_binary_tree.cpp"
#include "../04_threaded_binary_tree.cpp"
#include "test_support.h"

void testTrees() {
    const vector<string> samples={"#", "A # #", "A B C D # # E # # # #",
                                  "A B # C # # #", "A # B # C # #"};
    const vector<string> pre={"","A","ABDCE","ABC","ABC"};
    const vector<string> mid={"","A","DBACE","CBA","ABC"};
    const vector<string> post={"","A","DBECA","CBA","CBA"};
    const vector<string> level={"","A","ABCDE","ABC","ABC"};
    for (size_t k=0; k<samples.size(); ++k) {
        BTree<char> t;
        create(t,samples[k]);
        require(t.Size()==static_cast<int>(pre[k].size()),"结点数");
        require(t.Height()==(k==0 ? 0 : k==1 ? 1 : 3),"高度");
        require(t.isEmpty()==(k==0),"空树判定");
        require((t.GetRoot()==nullptr)==(k==0),"根指针");
        require(capture([&]{t.PreOrder();})==pre[k],"非递归前序");
        require(capture([&]{t.PreOrderRecursive();})==pre[k],"递归前序");
        require(capture([&]{t.InOrder1();})==mid[k],"中序算法一");
        require(capture([&]{t.InOrder();})==mid[k],"中序算法二");
        require(capture([&]{t.InOrderRecursive();})==mid[k],"递归中序");
        require(capture([&]{t.PostOrder();})==post[k],"非递归后序");
        require(capture([&]{t.PostOrderRecursive();})==post[k],"递归后序");
        require(capture([&]{t.LevelOrder();})==level[k],"层次遍历");
        t.buildFromTraversals(vector<char>(pre[k].begin(),pre[k].end()),
                              vector<char>(mid[k].begin(),mid[k].end()));
        require(capture([&]{t.PostOrder();})==post[k],"重构后序");
        create(t,"#"); require(t.isEmpty(),"重复建树清理旧树");
        t.DelTree(); require(t.isEmpty(),"重复删除");
        threaded::BTree<char> thread;
        create(thread,samples[k]);
        thread.ThreadMid(); thread.ThreadMid();
        require(capture([&]{thread.ThreadMidVisit();})==mid[k],"线索中序及重复线索化");
        require(capture([&]{thread.ThreadMidPreVisit();})==pre[k],"线索前序");
        create(thread,"A # #");
        require(capture([&]{thread.ThreadMidVisit();})=="A","线索树重复建树和自动线索化");
    }
    BTree<char> tree;
    rejects([&]{tree.buildFromTraversals({'A'},{});},"重构长度错误");
    rejects([&]{tree.buildFromTraversals({'A','A'},{'A','A'});},"重构重复元素");
    rejects([&]{tree.buildFromTraversals({'A'},{'B'});},"重构元素不一致");
    rejects([&]{tree.buildFromTraversals({'A','B','C'},{'C','A','B'});},"重构子区间不一致");
    rejects([&]{create(tree,"A #");},"普通树输入不完整");
    threaded::BTree<char> threadedTree;
    rejects([&]{create(threadedTree,"A #");},"线索树输入不完整");
    BTree<int> integers;
    integers.buildFromTraversals({2,1,3},{1,2,3});
    require(integers.Size()==3,"整型模板实例化");
}
