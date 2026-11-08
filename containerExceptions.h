#ifndef COURSE_CONTAINER_EXCEPTIONS_H
#define COURSE_CONTAINER_EXCEPTIONS_H
#include <stdexcept>
// 两章共用异常类型，避免课件各头文件中的重复定义。
class illegalSize : public std::invalid_argument {
public: illegalSize() : std::invalid_argument("非法容器大小") {}
};
class outOfBound : public std::out_of_range {
public: outOfBound() : std::out_of_range("空容器") {}
};
#endif
