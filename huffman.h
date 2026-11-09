// 从原完整tests.cpp拆分，保留原有全部断言。
#include "../03_huffman.cpp"
#include "test_support.h"

void testHuffman() {
    char values[]={'A','B','C','D'};
    auto verify=[&](vector<double> weights, double expected) {
        const int n=static_cast<int>(weights.size());
        unique_ptr<HuffmanNode<char>[]> tree(BestBinaryTree(values,weights.data(),n));
        char** codes=HuffmanCode(tree.get(),n);
        vector<string> strings;
        for (int i=0; i<n; ++i) strings.emplace_back(codes[i]);
        for (int i=0; i<n; ++i) delete[] codes[i];
        delete[] codes;
        double wpl=0;
        for (int i=0; i<n; ++i) {
            require(!strings[i].empty(),"哈夫曼编码非空");
            wpl+=weights[i]*strings[i].size();
            for (int j=0; j<n; ++j)
                if (i!=j) require(strings[j].rfind(strings[i],0)!=0,"哈夫曼前缀性质");
        }
        require(abs(wpl-expected)<1e-8,"最优带权路径长度");
        if (n>0) require(tree[1].parent==0,"哈夫曼根");
    };
    verify({},0); verify({2},2); verify({1,2,3,4},19);
    verify({0.2,0.1,0.9},1.5); // 原版 minWeight 为 int，会截断小数，漏选最小项。
    verify({10000,20000,30000},90000); // 超过原版 9999 哨兵。
    verify({0,0,0},0); verify({1,1,1,1},8);
    double bad=-1;
    rejects([&]{delete[] BestBinaryTree(values,&bad,1);},"负权值");
    bad=numeric_limits<double>::infinity();
    rejects([&]{delete[] BestBinaryTree(values,&bad,1);},"无限权值");
    rejects([&]{delete[] BestBinaryTree<char>(nullptr,nullptr,-1);},"负叶子数");
    rejects([&]{delete[] HuffmanCode<char>(nullptr,1);},"空哈夫曼树");
}
