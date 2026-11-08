// 来源：代码块6–7；修正中文标点，补充阶乘溢出检查。
#include "container_support.h"

void  print(int n)
{  if (n<=0) return;
   cout<<"***"<<endl;
   print(n-1);
}

int  p(int n)
{  if (n<=1) return 1;
   if (n>12) throw overflow_error("阶乘超出常见32位 int 范围");
   return n*p(n-1);
}

