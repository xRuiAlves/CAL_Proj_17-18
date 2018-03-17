#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "defs.h"

class Exception {
public:
    Exception() {}
};


class InvalidNodeId : public Exception {
public:
    InvalidNodeId(){}
};

class NodeNotFound : public Exception {
public:
    NodeNotFound(u_int id) : id(id) {}

    u_int id;
};





#endif //EXCEPTIONS_H
