// 从原完整tests.cpp拆分，保留原有全部断言。
#include "../01_binary_tree.cpp"
#include "test_support.h"

void testExpressions() {
    BTree<char> t;
    const vector<pair<string,int>> cases={
        {"7*(5-2)-8/2",17}, {"(6+5*(4-2))/2*(8-4)",32},
        {"9-5-2",2}, {"8/3/2",1}, {"(1-8)/3",-2},
        {" 2 + 3 * 4 ",14}, {"0",0}, {"(((9)))",9}};
    require(t.calExpTree()==0,"空表达式树");
    for (const auto& item: cases) {
        t.buildExpTree(item.first.c_str());
        require(t.calExpTree()==item.second,"表达式："+item.first);
    }
    for (const string exp: {"", "()", "1+", ")1(", "(1", "1)", "12+3", "-1", "1a2", "1(2)","1++2"})
        rejects([&]{t.buildExpTree(exp.c_str());},"非法表达式："+exp);
    rejects([&]{t.buildExpTree(nullptr);},"空表达式指针");
    rejects([&]{t.priOver('?', '#');},"无效运算符");
    t.buildExpTree("8/(3-3)");
    rejects([&]{t.calExpTree();},"除零");
    t.buildExpTree("9*9*9*9*9*9*9*9*9*9");
    rejects([&]{t.calExpTree();},"计算溢出");
}
