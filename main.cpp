/**
 * Demo app for Ex4
 */
#include <iostream>
#include <string>
#include "src/node.hpp"
#include "src/tree.hpp"

using namespace std;

int main()
{
    Node<double> root_node = Node<double>(1.1);
    Tree<double> tree; // Binary tree that contains doubles.
    tree.add_root(root_node);
    Node<double> n1 = Node<double>(1.2);
    Node<double> n2 = Node<double>(1.3);
    Node<double> n3 = Node<double>(1.4);
    Node<double> n4 = Node<double>(1.5);
    Node<double> n5 = Node<double>(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /       \
     *    1.2      1.3
     *   /  \      /
     *  1.4  1.5  1.6
     */

        cout << "Pre-Order Traversal:" << endl;
        for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node)
        {
            cout << *node << " ";
        } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
        std::cout << std::endl;

        cout << "Post-Order Traversal:" << endl;
        for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node)
        {
            cout << *node << " ";
        } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
        std::cout << std::endl;
        
        std::cout << "In-Order Traversal:" << std::endl;
        for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node)
        {
            std::cout << *node << " ";
        } // prints: 1.4, 1.2, 1.5, 1.1, 1.6, 1.3
        std::cout << std::endl;

        cout << "BFS Traversal:" << endl;
        for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node)
        {
            cout << *node << " ";
        } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
        std::cout << std::endl;

        cout << "Range-Based For Loop:" << std::endl;
        for (auto node : tree)
        {
            cout << node << " ";
        } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
        std::cout << std::endl;

    //cout << tree << endl;

    Tree<double, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.add_root(root_node);
    three_ary_tree.add_sub_node(root_node, n1);
    three_ary_tree.add_sub_node(root_node, n2);
    three_ary_tree.add_sub_node(root_node, n3);
    three_ary_tree.add_sub_node(n1, n4);
    three_ary_tree.add_sub_node(n2, n5);

    // The tree should look like:
    /**
     *       root = 1.1
     *     /      |     \
     *    1.2    1.3    1.4
     *   /        |
     *  1.5      1.6
     */

    /*cout << "Pre-Order Traversal:" << endl;
    for (auto node = three_ary_tree.begin_pre_order(); node != three_ary_tree.end_pre_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1, 1.2, 1.4, 1.5, 1.3, 1.6
    std::cout << std::endl;

    cout << "Post-Order Traversal:" << endl;
    for (auto node = three_ary_tree.begin_post_order(); node != three_ary_tree.end_post_order(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.4, 1.5, 1.2, 1.6, 1.3, 1.1
    std::cout << std::endl;

    std::cout << "In-Order Traversal:" << std::endl;
    for (auto node = three_ary_tree.begin_in_order(); node != three_ary_tree.end_in_order(); ++node)
    {
        std::cout << *node << " ";
    }
    std::cout << std::endl;

    cout << "BFS Traversal:" << endl;
    for (auto node = three_ary_tree.begin_bfs_scan(); node != three_ary_tree.end_bfs_scan(); ++node)
    {
        cout << *node << " ";
    } // prints: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    std::cout << std::endl;

    cout << "Range-Based For Loop:" << std::endl;
    for (auto node : three_ary_tree)
    {
        cout << node << " ";
    } // same as BFS: 1.1, 1.2, 1.3, 1.4, 1.5, 1.6
    std::cout << std::endl;*/

    return 0;
}
