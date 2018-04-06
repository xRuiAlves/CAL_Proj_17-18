#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "defs.h"

class Exception {
public:
    Exception() {}
};


class InvalidNodeId : public Exception {
private:
public:
    InvalidNodeId(u_int id) : id(id) {}

    u_int id;
};

class NodeNotFound : public Exception {
public:
    NodeNotFound(u_int id) : id(id) {}

    u_int id;
};

class GraphLoadFailed : public Exception {
public:
    GraphLoadFailed(const std::string & fileName) : fileName(fileName) {}

    std::string fileName;
};





#endif //EXCEPTIONS_H
