#ifndef CH4_TEST_SUPPORT_H
#define CH4_TEST_SUPPORT_H
#include "../container_support.h"
#include <sstream>
int checks=0;
void require(bool ok, const string& what) {
    ++checks;
    if (!ok) throw runtime_error("检查失败："+what);
}
template<class F> void rejects(F action, const string& what) {
    bool caught=false;
    try { action(); } catch (const exception&) { caught=true; }
    require(caught,what);
}
// RAII恢复标准流，测试失败也不留下被销毁的 streambuf。
struct StreamRestore {
    ios& stream;
    streambuf* previous;
    StreamRestore(ios& s, streambuf* buffer): stream(s),previous(s.rdbuf(buffer)) {}
    ~StreamRestore() { stream.rdbuf(previous); stream.clear(); }
};
template<class F> string capture(F action) {
    ostringstream out;
    StreamRestore restore(cout,out.rdbuf());
    action();
    string result=out.str();
    result.erase(remove(result.begin(),result.end(),'\n'),result.end());
    return result;
}
template<class Tree> void create(Tree& tree, const string& values) {
    istringstream in(values);
    StreamRestore restore(cin,in.rdbuf());
    capture([&]{ tree.createTree('#'); });
}


#endif
