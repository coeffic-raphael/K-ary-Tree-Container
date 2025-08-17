// racoeffic@gmail.com

#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include <stack>
#include <queue>
#include <sstream>
#include <cstddef>
#include <vector>
#include <string>
#include <type_traits>
#include <map>
#include <iomanip> 
#include <stdexcept>
#include <iostream>
#include <SFML/Graphics.hpp>  // SFML library for the GUI

using namespace std;

const float node_size = 35.0f;

template <typename T>
class PreOrderIterator {
private:
    Node<T>* current;
    std::stack<Node<T>*> stack;

public:
    PreOrderIterator(Node<T>* root) : current(nullptr) {
        if (root) {
            stack.push(root);
            current = root; 
        }
    }

    Node<T>* operator*() const {
        return current;
    }

    PreOrderIterator& operator++() {
        if (stack.empty()) {
            current = nullptr;
            return *this;
        }
        current = stack.top();
        stack.pop();
        auto children = current->getChildren();
        for (auto it = children.rbegin(); it != children.rend(); ++it) {
            stack.push(*it);
        }
        current = stack.empty() ? nullptr : stack.top();
        return *this;
    }

    bool operator!=(const PreOrderIterator& other) const {
        return current != other.current;
    }

    bool operator==(const PreOrderIterator& other) const {
        return current == other.current;
    }
};

template <typename T>
class InOrderIterator {
    std::stack<Node<T>*> stack;
    Node<T>* current;

    void pushLeft(Node<T>* node) {
        while (node) {
            stack.push(node);
            node = (node->getChildren().size() > 0) ? node->getChildren().front() : nullptr;
        }
    }

public:
    using iterator_category = std::input_iterator_tag;
    using value_type = Node<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = Node<T>**;
    using reference = Node<T>*;

    InOrderIterator(Node<T>* root) : current(nullptr) {
        pushLeft(root);
        if (!stack.empty()) {
            current = stack.top();
        }
    }

    InOrderIterator() : current(nullptr) {}

    reference operator*() const {
        return current;
    }

    pointer operator->() const {
        return &current;
    }

    InOrderIterator& operator++() {
        if (stack.empty()) {
            current = nullptr;
            return *this;
        }

        Node<T>* node = stack.top();
        stack.pop();

        if (!node->getChildren().empty()) {
            auto children = node->getChildren();
            if (children.size() > 1) {
                pushLeft(children[1]);
            }
        }

        current = stack.empty() ? nullptr : stack.top();
        return *this;
    }

    bool operator!=(const InOrderIterator& other) const {
        return current != other.current;
    }

    bool operator==(const InOrderIterator& other) const {
        return current == other.current;
    }
};

template <typename T>
class PostOrderIterator {
    std::stack<Node<T>*> stack;
    std::stack<Node<T>*> output;
    Node<T>* current;
    void traverse(Node<T>* node) {
        if (!node) return;
        stack.push(node);
        while (!stack.empty()) {
            Node<T>* current = stack.top();
            stack.pop();
            output.push(current);
            for (auto child : current->getChildren()) {
                stack.push(child);
            }
        }
    }
public:
    using iterator_category = std::input_iterator_tag;
    using value_type = Node<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = Node<T>**;
    using reference = Node<T>*;

    PostOrderIterator(Node<T>* root) : current(nullptr) {
        traverse(root);
        if (!output.empty()) {
            current = output.top();
        }
    }

    PostOrderIterator() : current(nullptr) {}

    reference operator*() const {
        return output.top();
    }

    pointer operator->() const {
        return &output.top();
    }

    PostOrderIterator& operator++() {
        if (!output.empty()) {
            output.pop();
        }
        current = output.empty() ? nullptr : output.top();
        return *this;
    }

    bool operator!=(const PostOrderIterator& other) const {
        return current != other.current;
    }

    bool operator==(const PostOrderIterator& other) const {
        return current == other.current;
    }
};
template <typename T>
class BFSIterator {
private:
    Node<T>* current;
    std::queue<Node<T>*> queue;

public:
    BFSIterator(Node<T>* root) : current(nullptr) {
        if (root) {
            queue.push(root);
            current = root; 
        }
    }

    Node<T>* operator*() const {
        return current;
    }

    BFSIterator& operator++() {
        if (queue.empty()) {
            current = nullptr;
            return *this;
        }
        current = queue.front();
        queue.pop();
        for (auto child : current->getChildren()) {
            queue.push(child);
        }
        current = queue.empty() ? nullptr : queue.front();
        return *this;
    }

    bool operator!=(const BFSIterator& other) const {
        return current != other.current;
    }

    bool operator==(const BFSIterator& other) const {
        return current == other.current;
    }
};
template <typename T>
class DFSIterator {
   private:
    Node<T>* current;
    std::stack<Node<T>*> stack;

   public:
    DFSIterator(Node<T>* root) : current(nullptr) {
         
        if (root != nullptr) {
            stack.push(root);
            ++(*this);  // Initialize the iterator to the first element
        }
    }

    DFSIterator& operator++() {
        if (stack.empty()) {
            current = nullptr;
            return *this;
        }
        current = stack.top();
        stack.pop();
        for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
            if (*it != nullptr) {
                stack.push(*it);
            }
        }
        return *this;
    }

    Node<T>* operator*() {
        return current;
    }


    bool operator==(const DFSIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const DFSIterator& other) const {
        return !(*this == other);
    }
};



template <typename T>
class HeapIterator {
private:
    std::vector<Node<T>*> heap;
    void fill_heap(Node<T>* root) {
        if (root == nullptr) {
            return;
        }
        heap.push_back(root);
        for (auto child : root->getChildren()) {
            fill_heap(child);
        }
    }

public:
    using iterator_category = std::input_iterator_tag;
    using value_type = Node<T>*;
    using difference_type = std::ptrdiff_t;
    using pointer = Node<T>**;
    using reference = Node<T>*;

    HeapIterator(Node<T>* root) {
        if (root != nullptr) {
            fill_heap(root);
            std::make_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) { return a->getValue() > b->getValue(); });
        }
    }

    HeapIterator() {}

    reference operator*() const {
        return heap.front();
    }

    pointer operator->() const {
        return &heap.front();
    }

    HeapIterator& operator++() {
        if (!heap.empty()) {
            std::pop_heap(heap.begin(), heap.end(), [](Node<T>* a, Node<T>* b) { return a->getValue() > b->getValue(); });
            heap.pop_back();
        }
        return *this;
    }

    bool operator!=(const HeapIterator&) const {
        return !heap.empty();
    }

    bool operator==(const HeapIterator&) const {
        return heap.empty();
    }
};

template <typename T, int K = 2>
class Tree
{
private:
    Node<T> *root;
    int k; // max num of children

    void destructor(Node<T> *node) {
        if (node == nullptr) return;
        for (auto child : node->getChildren())
            destructor(child);
        delete node;
    }

public:
    Tree() : root(nullptr){ this->k = K; }
    ~Tree() { destructor(root); }
    Node<T>* getRoot() const { return this->root; }
    int get_k() const { return k; }

    void add_root(const Node<T> &node) {
        if (root != nullptr)
            throw runtime_error("The tree already has a root");
        root = new Node<T>(node.getValue());
    }

    void add_sub_node(const Node<T> &parent, const Node<T> &child) {
        Node<T> *parent_ptr = find_node(root, parent.getValue());
        if (parent_ptr == nullptr)
            throw runtime_error("The tree doesn't contain this parent node");

        if (parent_ptr->children.size() >= (size_t)this->k)
            throw runtime_error("This node already has the max number of children");

        parent_ptr->addChild(child);
    }

    Node<T> *find_node(Node<T> *node, const T &value) {
        if (node == nullptr)
            return nullptr;
        if (node->getValue() == value)
            return node;
        for (auto child : node->getChildren()) {
            Node<T> *found = find_node(child, value);
            if (found != nullptr)
                return found;
        }
        return nullptr;
    }

    // Pre-order
    PreOrderIterator<T> begin_pre_order() { return PreOrderIterator<T>(root); }
    PreOrderIterator<T> end_pre_order() { return PreOrderIterator<T>(nullptr); }

    // In-order
    InOrderIterator<T> begin_in_order() { return InOrderIterator<T>(root); }
    InOrderIterator<T> end_in_order() { return InOrderIterator<T>(nullptr); }

    // Post-order
    PostOrderIterator<T> begin_post_order() { return PostOrderIterator<T>(root); }
    PostOrderIterator<T> end_post_order() { return PostOrderIterator<T>(nullptr); }

    // BFS
    BFSIterator<T> begin_bfs_scan() { return BFSIterator<T>(root); }
    BFSIterator<T> end_bfs_scan() { return BFSIterator<T>(nullptr); }

    // DFS
    DFSIterator<T> begin_dfs_scan() { return DFSIterator<T>(root); }
    DFSIterator<T> end_dfs_scan() { return DFSIterator<T>(nullptr); }

    // Heap
    HeapIterator<T> begin_heap() { return HeapIterator<T>(root); }
    HeapIterator<T> end_heap() { return HeapIterator<T>(nullptr); }

    /*
    * From here, I use SFML library for create a GUI that prints the tree
    */

    void helpForPrint(sf::RenderWindow &window, sf::Font &font) {
        if (this->root == nullptr) return;

        map<Node<T>*, sf::Vector2f> positions;
        float x = window.getSize().x / 2;
        float y = node_size * 6;
        float initialSpacing = window.getSize().x / 4; // Initial horizontal spacing
        float verticalSpacing = node_size * 6; // Increased vertical spacing between parent and children

        std::stack<std::tuple<Node<T>*, float, float, float>> stack;
        // Compute the localizations
        stack.push(std::make_tuple(root, x, y, initialSpacing));

        while (!stack.empty()) {
            auto [node, x, y, spacing] = stack.top();
            stack.pop();

            positions[node] = sf::Vector2f(x, y);

            float childSpacing = spacing / 1.5f; // Adjust horizontal spacing between children
            float childY = y + verticalSpacing; // Increase vertical spacing between levels
            float childX = x - childSpacing * (node->getChildren().size() - 1) / 2.0f;

            for (auto child : node->getChildren()) {
                stack.push(std::make_tuple(child, childX, childY, childSpacing));
                childX += childSpacing;
            }
        }

        for (auto &node : positions) {
            sf::CircleShape circle(node_size);
            circle.setFillColor(sf::Color::Magenta);
            circle.setOrigin(node_size, node_size);
            circle.setPosition(node.second);

            sf::Text text;
            text.setFont(font);
            if constexpr (is_same<T, string>::value) {
                text.setString(node.first->getValue());
            } else {
                ostringstream oss;
                oss << fixed << setprecision(1) << node.first->getValue();
                text.setString(oss.str());
            }
            text.setCharacterSize(15);
            text.setFillColor(sf::Color::White);
            text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
            text.setPosition(node.second);

            window.draw(circle);
            window.draw(text);

            sf::Vector2f line_start = node.second + sf::Vector2f(0, node_size / 1.5);

            for (auto child : node.first->getChildren()) {
                sf::Vertex line[] = {
                    sf::Vertex(line_start),
                    sf::Vertex(positions.at(child))
                };
                window.draw(line, 2, sf::Lines);
            }
        }
    }

    friend ostream &operator<<(ostream &os, Tree<T, K> &tree) {
        Node<T> *root = tree.getRoot();

        if(root == nullptr) {
            os << "Empty tree, no data for print a GUI" << endl;
            return os;
        }

        os << "Draw the tree, please see the GUI" << endl;

        sf::Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Error with the font\n" << endl;
            return os;
        }

        sf::RenderWindow window(sf::VideoMode(1500, 1000), "Tree GUI____@Raphael_Coeffic");
        window.setVerticalSyncEnabled(true);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            window.clear(sf::Color::Black);
            tree.helpForPrint(window, font);
            window.display();
        }

        return os;
    }

    



};

#endif // TREE_HPP
