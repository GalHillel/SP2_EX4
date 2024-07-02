#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <stack>
#include <set>
#include <algorithm>

// TODO: 1)Improve in-order (remove duplicate nodes)
// TODO: 2)Implement GUI "<<" operator
// TODO: 3)modify the iterators to support more then binary three
// TODO: 4)Add tests

// Forward declaration of iterator classes
template <typename T>
class PreOrderIterator;

template <typename T>
class PostOrderIterator;

template <typename T>
class InOrderIterator;

template <typename T>
class BFSIterator;

template <typename T>
class DFSIterator;

template <typename T>
class HeapIterator;

template <typename T, int K = 2>
class Tree
{
public:
    std::shared_ptr<Node<T>> root;

    void add_root(Node<T> &node)
    {
        root = std::make_shared<Node<T>>(node);
    }

    void add_sub_node(Node<T> &parent_node, Node<T> &child_node)
    {
        auto parent = find_node(root, parent_node.get_value());
        if (parent)
        {
            parent->children.push_back(std::make_shared<Node<T>>(child_node));
        }
    }

    std::shared_ptr<Node<T>> find_node(std::shared_ptr<Node<T>> current, T value)
    {
        if (!current)
            return nullptr;
        if (current->value == value)
            return current;
        for (auto &child : current->children)
        {
            auto found = find_node(child, value);
            if (found)
                return found;
        }
        return nullptr;
    }

    // Pre-Order Iterator
    using PreOrderIter = PreOrderIterator<T>;
    PreOrderIter begin_pre_order() const { return PreOrderIter(root); }
    PreOrderIter end_pre_order() const { return PreOrderIter(nullptr); }

    // Post-Order Iterator
    using PostOrderIter = PostOrderIterator<T>;
    PostOrderIter begin_post_order() const { return PostOrderIter(root); }
    PostOrderIter end_post_order() const { return PostOrderIter(nullptr); }

    // In-Order Iterator
    using InOrderIter = InOrderIterator<T>;
    InOrderIter begin_in_order() const { return InOrderIter(root); }
    InOrderIter end_in_order() const { return InOrderIter(nullptr); }

    // BFS Iterator
    using BFSIter = BFSIterator<T>;
    BFSIter begin_bfs_scan() const { return BFSIter(root); }
    BFSIter end_bfs_scan() const { return BFSIter(nullptr); }

    // DFS Iterator
    using DFSIter = DFSIterator<T>;
    DFSIter begin_dfs_scan() const { return DFSIter(root); }
    DFSIter end_dfs_scan() const { return DFSIter(nullptr); }

    // Heap Iterator
    using HeapIter = HeapIterator<T>;
    HeapIter begin_heap() const { return HeapIter(root); }
    HeapIter end_heap() const { return HeapIter(nullptr); }

    // Range-based for loop support using BFSIter
    BFSIter begin() const { return begin_bfs_scan(); }
    BFSIter end() const { return end_bfs_scan(); }
};

// Pre-Order Iterator Implementation
template <typename T>
class PreOrderIterator
{
    std::stack<std::shared_ptr<Node<T>>> node_stack;

public:
    PreOrderIterator(std::shared_ptr<Node<T>> root);

    bool operator!=(const PreOrderIterator &other) const;

    PreOrderIterator &operator++();

    T operator*() const;
};

template <typename T>
PreOrderIterator<T>::PreOrderIterator(std::shared_ptr<Node<T>> root)
{
    if (root)
        node_stack.push(root);
}

template <typename T>
bool PreOrderIterator<T>::operator!=(const PreOrderIterator &other) const
{
    return !node_stack.empty() || !other.node_stack.empty();
}

template <typename T>
PreOrderIterator<T> &PreOrderIterator<T>::operator++()
{
    auto current = node_stack.top();
    node_stack.pop();
    for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
    {
        node_stack.push(*it);
    }
    return *this;
}

template <typename T>
T PreOrderIterator<T>::operator*() const
{
    return node_stack.top()->get_value();
}

// Post-Order Iterator Implementation
template <typename T>
class PostOrderIterator
{
    std::stack<std::shared_ptr<Node<T>>> node_stack;

public:
    PostOrderIterator(std::shared_ptr<Node<T>> root);

    bool operator!=(const PostOrderIterator &other) const;

    PostOrderIterator &operator++();

    T operator*() const;

private:
    void fill_stack(std::shared_ptr<Node<T>> node);
};

template <typename T>
PostOrderIterator<T>::PostOrderIterator(std::shared_ptr<Node<T>> root)
{
    fill_stack(root);
}

template <typename T>
bool PostOrderIterator<T>::operator!=(const PostOrderIterator &other) const
{
    return !node_stack.empty() || !other.node_stack.empty();
}

template <typename T>
PostOrderIterator<T> &PostOrderIterator<T>::operator++()
{
    if (!node_stack.empty())
    {
        auto node = node_stack.top();
        node_stack.pop();
        return *this;
    }
    return *this;
}

template <typename T>
T PostOrderIterator<T>::operator*() const
{
    return node_stack.top()->get_value();
}

template <typename T>
void PostOrderIterator<T>::fill_stack(std::shared_ptr<Node<T>> node)
{
    if (!node)
        return;

    std::stack<std::shared_ptr<Node<T>>> temp_stack;
    temp_stack.push(node);

    while (!temp_stack.empty())
    {
        auto current = temp_stack.top();
        temp_stack.pop();

        node_stack.push(current);

        for (auto child : current->children)
        {
            temp_stack.push(child);
        }
    }
}

// In-Order Iterator Implementation
template <typename T>
class InOrderIterator
{
public:
    using NodePtr = std::shared_ptr<Node<T>>;

    InOrderIterator(NodePtr root);
    bool operator!=(const InOrderIterator &other) const;
    InOrderIterator &operator++();
    T operator*() const;

private:
    void fill_stack(NodePtr node);
    std::stack<std::pair<NodePtr, size_t>> node_stack; // Pair of node and current child index
};

template <typename T>
InOrderIterator<T>::InOrderIterator(NodePtr root)
{
    fill_stack(root);
}

template <typename T>
bool InOrderIterator<T>::operator!=(const InOrderIterator &other) const
{
    return !node_stack.empty() || !other.node_stack.empty();
}

template <typename T>
InOrderIterator<T> &InOrderIterator<T>::operator++()
{
    auto [current, index] = node_stack.top();
    node_stack.pop();
    ++index;
    if (index < current->children.size())
    {
        node_stack.push({current, index});
        fill_stack(current->children[index]);
    }
    return *this;
}

template <typename T>
T InOrderIterator<T>::operator*() const
{
    return node_stack.top().first->value;
}

template <typename T>
void InOrderIterator<T>::fill_stack(NodePtr node)
{
    if (!node)
        return;
    // Start by pushing the leftmost path onto the stack
    NodePtr current = node;
    while (current)
    {
        node_stack.push({current, 0});

        if (!current->children.empty())
        {
            current = current->children[0];
        }
        else
        {
            current = nullptr;
        }
    }
}

// BFS Iterator Implementation
template <typename T>
class BFSIterator
{
    std::queue<std::shared_ptr<Node<T>>> node_queue;

public:
    BFSIterator(std::shared_ptr<Node<T>> root);

    bool operator!=(const BFSIterator &other) const;

    BFSIterator &operator++();

    T operator*() const;
};

template <typename T>
BFSIterator<T>::BFSIterator(std::shared_ptr<Node<T>> root)
{
    if (root)
        node_queue.push(root);
}

template <typename T>
bool BFSIterator<T>::operator!=(const BFSIterator &other) const
{
    return !node_queue.empty() || !other.node_queue.empty();
}

template <typename T>
BFSIterator<T> &BFSIterator<T>::operator++()
{
    if (!node_queue.empty())
    {
        auto current = node_queue.front();
        node_queue.pop();
        for (auto &child : current->children)
        {
            node_queue.push(child);
        }
    }
    return *this;
}

template <typename T>
T BFSIterator<T>::operator*() const
{
    return node_queue.front()->get_value();
}

// DFS Iterator Implementation
template <typename T>
class DFSIterator
{
    std::stack<std::shared_ptr<Node<T>>> node_stack;

public:
    DFSIterator(std::shared_ptr<Node<T>> root);

    bool operator!=(const DFSIterator &other) const;

    DFSIterator &operator++();

    T operator*() const;
};

template <typename T>
DFSIterator<T>::DFSIterator(std::shared_ptr<Node<T>> root)
{
    if (root)
        node_stack.push(root);
}

template <typename T>
bool DFSIterator<T>::operator!=(const DFSIterator &other) const
{
    return !node_stack.empty() || !other.node_stack.empty();
}

template <typename T>
DFSIterator<T> &DFSIterator<T>::operator++()
{
    if (!node_stack.empty())
    {
        auto current = node_stack.top();
        node_stack.pop();
        for (auto it = current->children.rbegin(); it != current->children.rend(); ++it)
        {
            node_stack.push(*it);
        }
    }
    return *this;
}

template <typename T>
T DFSIterator<T>::operator*() const
{
    return node_stack.top()->get_value();
}

// Heap Iterator Implementation
template <typename T>
class HeapIterator
{
    std::vector<T> heap;
    size_t index;

public:
    HeapIterator(std::shared_ptr<Node<T>> root);

    bool operator!=(const HeapIterator &other) const;

    HeapIterator &operator++();

    T operator*() const;

private:
    void heapify(std::shared_ptr<Node<T>> node);
};

template <typename T>
HeapIterator<T>::HeapIterator(std::shared_ptr<Node<T>> root) : index(0)
{
    if (root)
        heapify(root);
}

template <typename T>
bool HeapIterator<T>::operator!=(const HeapIterator &other) const
{
    return index < heap.size();
}

template <typename T>
HeapIterator<T> &HeapIterator<T>::operator++()
{
    ++index;
    return *this;
}

template <typename T>
T HeapIterator<T>::operator*() const
{
    return heap[index];
}

template <typename T>
void HeapIterator<T>::heapify(std::shared_ptr<Node<T>> node)
{
    if (!node)
        return;
    heap.push_back(node->get_value());
    for (auto &child : node->children)
    {
        heapify(child);
    }
    std::make_heap(heap.begin(), heap.end(), std::greater<T>());
}

#endif