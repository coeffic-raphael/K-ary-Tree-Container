// racoeffic@gmail.com

#include <iostream>
#include "Node.hpp"
#include "Tree.hpp" 
#include "Complex.hpp"

using namespace std;
int main()
{
    // Binary tree
    Node<double> root_node = Node<double>(0.0);
    Tree<double> double_tree; // Binary tree that contains doubles.
    double_tree.add_root(root_node);

    Node<double> n1 = Node<double>(0.1);
    Node<double> n2 = Node<double>(0.2);
    Node<double> n3 = Node<double>(1.0);
    Node<double> n4 = Node<double>(1.1);
    Node<double> n5 = Node<double>(2.0);

    try
    {
        double_tree.add_root(root_node); 
    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl; // this tree already has a root
    }
    
    double_tree.add_sub_node(root_node, n1);
    double_tree.add_sub_node(root_node, n2);
    try
    {
        double_tree.add_sub_node(root_node, n3); 
    }
    catch (const runtime_error &e)
    {
        cout << e.what() << endl; // this node already have the max num of children
    }
    double_tree.add_sub_node(n1, n3);
    double_tree.add_sub_node(n1, n4);
    double_tree.add_sub_node(n2, n5);

    
    cout << double_tree;  // Print on the GUI

    // print the tree with the iterators 
    cout << "Pre-Order:" << endl;
    for (auto node = double_tree.begin_pre_order(); node != double_tree.end_pre_order(); ++node)
        cout << (*node)->getValue() << endl;

    cout << "In-Order" << endl;
    for (auto node = double_tree.begin_in_order(); node != double_tree.end_in_order(); ++node) 
        cout << (*node)->getValue() << endl;
    
    cout << "Post-Order:" << endl;
    for (auto node = double_tree.begin_post_order(); node != double_tree.end_post_order(); ++node)
        cout << (*node)->getValue() << endl;

    cout << "BFS Traversal:" << endl;
    for (auto node = double_tree.begin_bfs_scan(); node != double_tree.end_bfs_scan(); ++node) 
        cout << (*node)->getValue() << endl;
    

    cout << "DFS Traversal:" << endl;
    for (auto node = double_tree.begin_dfs_scan(); node != double_tree.end_dfs_scan(); ++node) 
        cout << (*node)->getValue() << endl;
    

    cout << "myHeap Traversal:" << endl;
    for (auto node = double_tree.begin_heap(); node != double_tree.end_heap(); ++node) 
        cout << (*node)->getValue() << endl;

    

    // Tree with Complex numbers and up to 5 children per node
    Tree<Complex, 5> complex_tree;
    Node<Complex> complex_root_node = Node<Complex>(Complex(1, 2));
    complex_tree.add_root(complex_root_node);

    Node<Complex> c1 = Node<Complex>(Complex(3, 4));
    Node<Complex> c2 = Node<Complex>(Complex(5, 6));
    Node<Complex> c3 = Node<Complex>(Complex(7, 8));
    Node<Complex> c4 = Node<Complex>(Complex(9, 10));
    Node<Complex> c5 = Node<Complex>(Complex(11, 12));
    Node<Complex> c6 = Node<Complex>(Complex(13, 14));

    complex_tree.add_sub_node(complex_root_node, c1);
    complex_tree.add_sub_node(complex_root_node, c2);
    complex_tree.add_sub_node(complex_root_node, c3);
    complex_tree.add_sub_node(complex_root_node, c4);
    complex_tree.add_sub_node(complex_root_node, c5);
    complex_tree.add_sub_node(c1, c6);


    std::cout << "Pre-order traversal:" << std::endl;
    for (auto node = complex_tree.begin_pre_order(); node != complex_tree.end_pre_order(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "Post-order traversal:" << std::endl;
    for (auto node = complex_tree.begin_post_order(); node != complex_tree.end_post_order(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "In-order traversal:" << std::endl;
    for (auto node = complex_tree.begin_in_order(); node != complex_tree.end_in_order(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "BFS traversal:" << std::endl;
    for (auto node = complex_tree.begin_bfs_scan(); node != complex_tree.end_bfs_scan(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "DFS traversal:" << std::endl;
    for (auto node = complex_tree.begin_dfs_scan(); node != complex_tree.end_dfs_scan(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    cout << "myHeap Traversal:" << endl;
    for (auto node = complex_tree.begin_heap(); node != complex_tree.end_heap(); ++node)
        cout << (*node)->getValue() << endl;   
    cout << complex_tree;

    

    Node<std::string> avraham("Avraham");
    Tree<std::string, 12> tree;
    tree.add_root(avraham);

    Node<std::string> yitshak("Yitshak");
    Node<std::string> ishmael("Ishmael");
    tree.add_sub_node(avraham, yitshak);
    tree.add_sub_node(avraham, ishmael);

    Node<std::string> yaakov("Yaakov");
    Node<std::string> essav("Essav");
    tree.add_sub_node(yitshak, yaakov);
    tree.add_sub_node(yitshak, essav);

    Node<std::string> reuven("Reuven");
    Node<std::string> shimon("Shimon");
    Node<std::string> levi("Levi");
    Node<std::string> yehuda("Yehuda");
    Node<std::string> dan("Dan");
    Node<std::string> naftali("Naftali");
    Node<std::string> gad("Gad");
    Node<std::string> asher("Asher");
    Node<std::string> yissachar("Yissachar");
    Node<std::string> zevulun("Zevulun");
    Node<std::string> yosef("Yosef");
    Node<std::string> binyamin("Binyamin");

    tree.add_sub_node(yaakov, reuven);
    tree.add_sub_node(yaakov, shimon);
    tree.add_sub_node(yaakov, levi);
    tree.add_sub_node(yaakov, yehuda);
    tree.add_sub_node(yaakov, dan);
    tree.add_sub_node(yaakov, naftali);
    tree.add_sub_node(yaakov, gad);
    tree.add_sub_node(yaakov, asher);
    tree.add_sub_node(yaakov, yissachar);
    tree.add_sub_node(yaakov, zevulun);
    tree.add_sub_node(yaakov, yosef);
    tree.add_sub_node(yaakov, binyamin);

    std::cout << "Pre-order traversal:" << std::endl;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "Post-order traversal:" << std::endl;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "In-order traversal:" << std::endl;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "BFS traversal:" << std::endl;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }
    std::cout << std::endl;

    std::cout << "DFS traversal:" << std::endl;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        std::cout << (*node)->getValue() << " ";
    }

    cout << "myHeap Traversal:" << endl;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node)
        cout << (*node)->getValue() << endl;
    std::cout << std::endl;
    cout << tree;

    return 0;
}