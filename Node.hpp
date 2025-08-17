// racoeffic@gmail.com

#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
using namespace std;

// I implement here because it's a template
template <typename T>
class Node {
public:
    T val;
    vector<Node<T>*> children;

    // constructor / destructor
    Node(T val) : val(val) {}
    ~Node() {}

    T getValue() const { return val; }
    vector<Node<T>*> getChildren() const { return this->children; }
    void addChild(const Node<T>& new_child) { children.push_back(new Node<T>(new_child)); }

};

#endif // NODE_HPP
