// 在线编辑器直接运行：默认只编译二叉树基础检查，降低峰值内存。
// 完整检查由run_checks.sh依次用CH4_TEST_GROUP=1..6编译运行。
#ifndef CH4_TEST_GROUP
#define CH4_TEST_GROUP 0
#endif
#define CH4_NO_MAIN
#if CH4_TEST_GROUP == 0
#include "01_binary_tree.cpp"
int main() {
    try {
        BTree<char> tree;
        tree.buildFromTraversals({'A','B','D','C','E'}, {'D','B','A','C','E'});
        if (tree.Size()!=5 || tree.Height()!=3) {
            std::cerr<<"二叉树大小/高度检查失败\n";
            return 1;
        }
        std::cout<<"Preorder: "; tree.PreOrder();
        std::cout<<"Inorder: "; tree.InOrder();
        std::cout<<"Postorder: "; tree.PostOrder();
        tree.buildExpTree("7*(5-2)-8/2");
        if (tree.calExpTree()!=17) {
            std::cerr<<"表达式求值检查失败\n";
            return 1;
        }
        tree.DelTree();
        if (!tree.isEmpty()) return 1;
        std::cout<<"Basic checks passed. Run run_checks.sh for all tests.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 1;
    }
}
#else
#if CH4_TEST_GROUP == 1
#include "test_cases/trees.h"
#define CH4_RUN_TEST testTrees
#elif CH4_TEST_GROUP == 2
#include "test_cases/expressions.h"
#define CH4_RUN_TEST testExpressions
#elif CH4_TEST_GROUP == 3
#include "test_cases/huffman.h"
#define CH4_RUN_TEST testHuffman
#elif CH4_TEST_GROUP == 4
#include "test_cases/heap.h"
#define CH4_RUN_TEST testHeap
#elif CH4_TEST_GROUP == 5
#include "test_cases/simulation.h"
#define CH4_RUN_TEST testSimulator
#elif CH4_TEST_GROUP == 6
#include "test_cases/recursion.h"
#define CH4_RUN_TEST testRecursion
#else
#error CH4_TEST_GROUP must be in range 0..6
#endif
int main() {
    try {
        CH4_RUN_TEST();
        std::cout<<"Group "<<CH4_TEST_GROUP<<" passed: "<<checks<<" checks.\n";
        return 0;
    } catch (const std::exception& e) {
        std::cerr<<e.what()<<'\n';
        return 1;
    }
}
#endif
