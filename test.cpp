// racoeffic@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Complex.hpp"
#include "Node.hpp"
#include "Tree.hpp"
#include <iostream>


using namespace std;


TEST_CASE("Complex addition") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex result = c1 + c2;
    CHECK(result == Complex(4.0, 6.0));

    c1 += c2;
    CHECK(c1 == Complex(4.0, 6.0));
}

TEST_CASE("Complex subtraction") {
    Complex c1(5.0, 6.0);
    Complex c2(3.0, 2.0);
    Complex result = c1 - c2;
    CHECK(result == Complex(2.0, 4.0));

    c1 -= c2;
    CHECK(c1 == Complex(2.0, 4.0));
}

TEST_CASE("Complex multiplication") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex result = c1 * c2;
    CHECK(result == Complex(-5.0, 10.0));

    c1 *= c2;
    CHECK(c1 == Complex(-5.0, 10.0));
}

TEST_CASE("Complex division") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex result = c1 / c2;
    CHECK(result.getReal() == doctest::Approx(0.44));
    CHECK(result.getImaginary() == doctest::Approx(0.08));

    c1 /= c2;
    CHECK(c1.getReal() == doctest::Approx(0.44));
    CHECK(c1.getImaginary() == doctest::Approx(0.08));
}

TEST_CASE("Complex negation") {
    Complex c1(3.0, 4.0);
    Complex result = -c1;
    CHECK(result == Complex(-3.0, -4.0));
}

TEST_CASE("Complex comparison operators") {
    Complex c1(1.0, 2.0);
    Complex c2(3.0, 4.0);
    Complex c3(1.0, 2.0);

    CHECK(c1 == c3);
    CHECK(c1 != c2);
    CHECK(c1 < c2);
    CHECK(c1 <= c2);
    CHECK(c2 > c1);
    CHECK(c2 >= c1);
}

TEST_CASE("Complex extreme cases") {
    Complex c1(1e10, 1e10);
    
    Complex c0(0, 0);
    CHECK_THROWS(c1 / c0); // Division by zero
}

TEST_CASE("Complex input/output stream operators") {
    Complex c(1,2);
    std::stringstream ss;
    ss << "3.0 4.0";
    ss >> c;
    CHECK(c == Complex(3.0, 4.0));

    ss.clear();
    ss.str("");
    ss << c;
    CHECK(ss.str() == "3+4i");
}
    
TEST_CASE("Tree: Add root and sub-nodes") {
    Tree<double> tree;

    Node<double> root_node(1.1);
    tree.add_root(root_node);
    CHECK(tree.getRoot()->getValue() == 1.1);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    CHECK(tree.getRoot()->getChildren().size() == 2);

    tree.add_sub_node(n1, n3);
    CHECK(tree.getRoot()->getChildren()[0]->getChildren().size() == 1);
}

TEST_CASE("Tree: Find node") {
    Tree<double> tree;
    Node<double> root_node(1.1);
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);

    Node<double>* found = tree.find_node(tree.getRoot(), 1.2);
    CHECK(found->getValue() == 1.2);

    found = tree.find_node(tree.getRoot(), 2.0);
    CHECK(found == nullptr);
}

TEST_CASE("Tree: Exceptions") {
    Tree<double> tree;
    Node<double> root_node(1.1);
    Node<double> n1(1.2);
    Node<double> n2(1.3);

    CHECK_THROWS_AS(tree.add_sub_node(root_node, n1), std::runtime_error);

    tree.add_root(root_node);
    CHECK_THROWS_AS(tree.add_root(root_node), std::runtime_error);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    CHECK_THROWS_AS(tree.add_sub_node(root_node, Node<double>(1.4)), std::runtime_error);
}

TEST_CASE("Tree: Pre-order traversal") {
    Tree<double> tree;
    Node<double> root_node(1.1);
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    stringstream ss;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        ss << (*node)->getValue() << " ";
    }
    CHECK(ss.str() == "1.1 1.2 1.4 1.5 1.3 1.6 ");
}

TEST_CASE("Tree: In-order traversal") {
    Tree<double> tree;
    Node<double> root_node(1.1);
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    stringstream ss;
    for (auto node = tree.begin_in_order(); node != tree.end_in_order(); ++node) {
        ss << (*node)->getValue() << " ";
    }
    CHECK(ss.str() == "1.4 1.2 1.5 1.1 1.6 1.3 ");
}

TEST_CASE("Tree: Post-order traversal") {
    Tree<double> tree;
    Node<double> root_node(1.1);
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    stringstream ss;
    for (auto node = tree.begin_post_order(); node != tree.end_post_order(); ++node) {
        ss << (*node)->getValue() << " ";
    }
    CHECK(ss.str() == "1.4 1.5 1.2 1.6 1.3 1.1 ");
}

TEST_CASE("Tree: BFS traversal") {
    Tree<double> tree;
    Node<double> root_node(1.1);
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    stringstream ss;
    for (auto node = tree.begin_bfs_scan(); node != tree.end_bfs_scan(); ++node) {
        ss << (*node)->getValue() << " ";
    }
    CHECK(ss.str() == "1.1 1.2 1.3 1.4 1.5 1.6 ");
}

TEST_CASE("Tree: DFS traversal") {
    Tree<double> tree;
    Node<double> root_node(1.1);
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    stringstream ss;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        ss << (*node)->getValue() << " ";
    }
    CHECK(ss.str() == "1.1 1.2 1.4 1.5 1.3 1.6 ");
}

TEST_CASE("Tree: Heap traversal") {
    Tree<double> tree;
    Node<double> root_node(1.1);
    tree.add_root(root_node);

    Node<double> n1(1.2);
    Node<double> n2(1.3);
    Node<double> n3(1.4);
    Node<double> n4(1.5);
    Node<double> n5(1.6);

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);
    tree.add_sub_node(n1, n4);
    tree.add_sub_node(n2, n5);

    stringstream ss;
    for (auto node = tree.begin_heap(); node != tree.end_heap(); ++node) {
        ss << (*node)->getValue() << " ";
    }
    CHECK(ss.str() == "1.1 1.2 1.3 1.4 1.5 1.6 ");
}

TEST_CASE("Tree with Complex values") {
    Tree<Complex> tree;
    Node<Complex> root_node(Complex(1, 2));
    tree.add_root(root_node);

    Node<Complex> n1(Complex(3, 4));
    Node<Complex> n2(Complex(5, 6));
    Node<Complex> n3(Complex(7, 8));

    tree.add_sub_node(root_node, n1);
    tree.add_sub_node(root_node, n2);
    tree.add_sub_node(n1, n3);

    stringstream ss;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        ss << (*node)->getValue() << " ";
    }
    CHECK(ss.str() == "1+2i 3+4i 7+8i 5+6i ");
}

TEST_CASE("Tree with string values") {
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

    stringstream ss;
    for (auto node = tree.begin_dfs_scan(); node != tree.end_dfs_scan(); ++node) {
        ss << (*node)->getValue() << " ";
    }
    CHECK(ss.str() == "Avraham Yitshak Yaakov Reuven Shimon Levi Yehuda Dan Naftali Gad Asher Yissachar Zevulun Yosef Binyamin Essav Ishmael ");
}


TEST_CASE("Extreme cases for Tree") {
    Tree<double> tree;

    // Case: Empty tree
    stringstream ss_empty;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        ss_empty << (*node)->getValue() << " ";
    }
    CHECK(ss_empty.str().empty());

    // Case: Single node tree
    Node<double> root_node(1.1);
    tree.add_root(root_node);
    stringstream ss_single;
    for (auto node = tree.begin_pre_order(); node != tree.end_pre_order(); ++node) {
        ss_single << (*node)->getValue() << " ";
    }
    CHECK(ss_single.str() == "1.1 ");

    // Case: Deep tree with single path
    Tree<double> deep_tree;
    Node<double> deep_root(0.1);
    deep_tree.add_root(deep_root);
    Node<double>* last_node = &deep_root;
    for (int i = 2; i <= 1000; ++i) {
        Node<double> new_node(i * 0.1);
        deep_tree.add_sub_node(*last_node, new_node);
        last_node = deep_tree.find_node(deep_tree.getRoot(), i * 0.1);
    }
    
    stringstream ss_deep;
    for (auto node = deep_tree.begin_pre_order(); node != deep_tree.end_pre_order(); ++node) {
        ss_deep << (*node)->getValue() << " ";
    }
    CHECK(ss_deep.str().size() > 1000);

}