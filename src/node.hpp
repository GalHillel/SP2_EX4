#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

template <typename T>
class Node
{
public:
    T value;
    std::vector<std::shared_ptr<Node<T>>> children;

    Node(T val) : value(val) {}

    T get_value() const { return value; }
};

#endif