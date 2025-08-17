# Ex4: K-ary Tree Container

## Overview
This project implements a generic K-ary tree container that supports various traversal methods. The tree can contain keys of any type, such as numbers, strings, or custom classes like `Complex`. The default configuration is a binary tree (K=2). The project also includes a `Complex` class to demonstrate the use of the tree with complex numbers.

## Features
1. **Pre-Order Traversal**: Scans the tree in the following order: current node -> left subtree -> right subtree.
2. **Post-Order Traversal**: Scans the tree in the following order: left subtree -> right subtree -> current node.
3. **In-Order Traversal**: Scans the tree in the following order: left subtree -> current node -> right subtree.
4. **BFS Traversal**: Scans the tree breadth-first (left to right).
5. **DFS Traversal**: Scans the tree using the DFS algorithm.
6. **Heap Iterator**: Converts a binary tree to a min-heap and provides iterators for the resulting heap.

## Methods
1. **add_root**: Adds the root of the tree. The method takes any node and sets it as the root.
2. **add_sub_node**: Adds a child to a parent node. The method takes a node in the tree and any other node, creating a child for the given node.
3. **begin_pre_order, end_pre_order**: Return iterators for pre-order traversal.
4. **begin_post_order, end_post_order**: Return iterators for post-order traversal.
5. **begin_in_order, end_in_order**: Return iterators for in-order traversal.
6. **begin_bfs_scan, end_bfs_scan**: Return iterators for BFS traversal.
7. **begin_dfs_scan, end_dfs_scan**: Return iterators for DFS traversal.
8. **myHeap**: Converts a binary tree to a min-heap and returns iterators for the resulting heap.

## Dependencies
- C++
- SFML library for GUI

## Classes
1. **Node<T>**: Represents a node in the tree. Contains a value of type `T` and a vector of children nodes.
2. **Tree<T, K=2>**: Represents the K-ary tree container. Contains methods for adding nodes, finding nodes, and various traversals.
3. **Complex**: Represents a complex number with real and imaginary parts. Supports arithmetic operations, comparisons, and stream input/output.

## File Structure
- `Node.hpp`: Defines the `Node` class.
- `Complex.hpp` and `Complex.cpp`: Define the `Complex` class.
- `Tree.hpp`: Defines the `Tree` class and various iterators for traversals.
- `main.cpp`: Demonstrates the functionality of the tree with various types, including doubles, strings, and complex numbers.
- `test.cpp`: Contains comprehensive tests for the `Tree` and `Complex` classes.
- `Makefile`: Defines build rules for the project.

## Building and Running the Project
To build and run the project, you need to install SFML for the GUI with the folowing commands: `sudo apt update` and `sudo apt install libsfml-dev` and for run please enter: `make`

@Raphael_Coeffic
racoeffic@gmail.com
337614747
