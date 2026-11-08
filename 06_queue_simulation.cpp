// 来源：main.tex 代码块63–70；将分开的到达/离开事件处理插入主循环。
// 块63为说明性伪代码，原文完整保留在00_raw_extracted.cpp。
#include "container_support.h"
#include <random>
#include "priorityQueue.h"

class simulator {
    int noOfServer;
    int arrivalLow, arrivalHigh;
    int serviceTimeLow, serviceTimeHigh;
    int customNum;
    mt19937 randomEngine;
    struct eventT {
        long long time=0;
        int type=0; // 0：到达，1：离开
        // 同时发生时先处理离开，减少零时间间隔下的歧义。
        bool operator<(const eventT& e) const {
            if (time!=e.time) return time<e.time;
            return type>e.type;
        }
    };
    void validate() const {
        if (noOfServer<=0 || customNum<=0 || arrivalLow<0 || arrivalHigh<arrivalLow ||
            serviceTimeLow<0 || serviceTimeHigh<serviceTimeLow)
            throw invalid_argument("柜台数、顾客数须为正数，时间上下界须非负且有序");
    }
public:
    simulator();
    // 补充非交互构造函数，固定种子用于复现和检查。
    simulator(int servers, int arrivalLo, int arrivalHi, int serviceLo,
              int serviceHi, int customers, unsigned seed=42)
      : noOfServer(servers), arrivalLow(arrivalLo), arrivalHigh(arrivalHi),
        serviceTimeLow(serviceLo), serviceTimeHigh(serviceHi), customNum(customers),
        randomEngine(seed) { validate(); }
    long long avgWaitTime(); // 沿用课件整数平均值，扩大累加范围。
};

simulator::simulator() : randomEngine(random_device{}()) {
    cout<<"请输入柜台数：";
    if (!(cin>>noOfServer)) throw invalid_argument("柜台数输入错误");
    cout<<"请输入到达时间间隔的上下界（最小间隔时间 最大间隔时间）：";
    if (!(cin>>arrivalLow>>arrivalHigh)) throw invalid_argument("到达间隔输入错误");
    cout<<"请输入服务时间的上下界（服务时间下界 服务时间上界）：";
    if (!(cin>>serviceTimeLow>>serviceTimeHigh)) throw invalid_argument("服务时间输入错误");
    cout<<"请输入模拟的顾客数：";
    if (!(cin>>customNum)) throw invalid_argument("顾客数输入错误");
    validate();
}

long long simulator::avgWaitTime() {
    int serverBusy=0;
    long long totalWaitTime=0;
    linkQueue<eventT> waitQueue;
    priorityQueue<eventT> eventQueue;
    uniform_int_distribution<int> arrivalTime(arrivalLow,arrivalHigh);
    uniform_int_distribution<int> serviceTime(serviceTimeLow,serviceTimeHigh);
    eventT currentEvent;
    for (int i=0; i<customNum; ++i) {
        currentEvent.time+=arrivalTime(randomEngine);
        eventQueue.enQueue(currentEvent);
    }
    while (!eventQueue.isEmpty()) {
        // 两种队列的 deQueue 均为 void，先 front 再 deQueue。
        currentEvent=eventQueue.front();
        eventQueue.deQueue();
        const long long currentTime=currentEvent.time;
        switch (currentEvent.type) {
        case 0:
            if (serverBusy<noOfServer) {
                ++serverBusy;
                currentEvent.time=currentTime+serviceTime(randomEngine);
                currentEvent.type=1;
                eventQueue.enQueue(currentEvent);
            } else waitQueue.enQueue(currentEvent);
            break;
        case 1:
            if (!waitQueue.isEmpty()) {
                currentEvent=waitQueue.front();
                waitQueue.deQueue();
                const long long wait=currentTime-currentEvent.time;
                if (totalWaitTime>numeric_limits<long long>::max()-wait)
                    throw overflow_error("累计等待时间超出范围");
                totalWaitTime+=wait;
                currentEvent.time=currentTime+serviceTime(randomEngine);
                currentEvent.type=1;
                eventQueue.enQueue(currentEvent);
            } else --serverBusy;
            break;
        }
    }
    return totalWaitTime/customNum;
}

#ifndef CH4_NO_MAIN
int main() {
    try {
        simulator sim;
        cout<<"平均等待时间："<<sim.avgWaitTime()<<endl;
        return 0;
    } catch (const exception& e) {
        cerr<<"错误："<<e.what()<<endl;
        return 1;
    }
}
#endif
