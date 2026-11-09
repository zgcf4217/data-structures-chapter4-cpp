#include "../02_recursion_examples.cpp"
#include "test_support.h"
void testRecursion() {
    require(capture([]{print(3);})=="*********","递归打印");
    require(capture([]{print(0);}).empty(),"递归打印终止条件");
    require(p(0)==1 && p(5)==120 && p(12)==479001600,"递归阶乘");
    rejects([]{p(13);},"阶乘溢出");
}
