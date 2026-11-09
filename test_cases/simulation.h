// 从原完整tests.cpp拆分，保留原有全部断言。
#include "../06_queue_simulation.cpp"
#include "test_support.h"

void testSimulator() {
    // 一柜台，每1单位来一人，服务3单位，五人等待0、2、4、6、8，均值4。
    simulator one(1,1,1,3,3,5);
    require(one.avgWaitTime()==4,"单服务台精确结果");
    // 两柜台同样五人，等待0、0、1、1、2，整数均值0。
    simulator two(2,1,1,3,3,5);
    require(two.avgWaitTime()==0,"多服务台精确结果");
    simulator simultaneous(1,0,0,3,3,5);
    require(simultaneous.avgWaitTime()==6,"同时到达精确结果");
    simulator zero(1,0,0,0,0,30);
    require(zero.avgWaitTime()==0,"零服务时间与同一时刻事件");
    simulator enough(10,0,0,100,100,10);
    require(enough.avgWaitTime()==0,"充足服务台");
    simulator a(3,0,2,1,9,500,123), b(3,0,2,1,9,500,123);
    auto wait=a.avgWaitTime();
    require(wait>=0 && wait==b.avgWaitTime(),"固定随机种子可复现");
    rejects([]{simulator bad(0,1,2,1,2,10);},"零柜台");
    rejects([]{simulator bad(1,1,2,1,2,0);},"零顾客");
    rejects([]{simulator bad(1,2,1,1,2,10);},"上下界倒置");
    rejects([]{simulator bad(1,1,2,-1,2,10);},"负服务时间");
}
