
#ifndef NODE_
#define NODE_
  template<class T>
  class BinaryNode {
  public:
    T data;
    BinaryNode<T> *left;
    BinaryNode<T> *right;
    BinaryNode(T d) : data(d), left(nullptr), right(nullptr) { };
  };
#endif

#ifndef MYTREE_
#define MYTREE_
#include<iostream>
#include<typeinfo>
  template<class T>
  class BinarySearchTree {
  public:  //basic functions
    void remove(T item) {
      remove(item, root);
    };
    void insert(T item) {
      insert(item, root);
    };
    BinaryNode<T>* find(T item) {
      return find(item, root);
    };
    long int getNodes() {
      return nodes;
    };
    BinarySearchTree() { root = nullptr; };

    BinaryNode<T>* getRoot() {
      return *&root;
    };

    void printPreorder(BinaryNode<T>* root)
    {
      if (root == nullptr)
        std::cout << "root is nullptr\n";
        return;

      // First print data of node
      std::cout << root->data << std::endl;

      // Then recur on left subtree
      printPreorder(root->left);

      // Now recur on right subtree
      printPreorder(root->right);
    }

  private:
    BinaryNode<T>* root;
    long int nodes = 0;
    void remove(T x, BinaryNode<T> *&t) {
      if (t == nullptr) return;   // Item not found; do nothing
      if (x < t->data)
        remove(x, t->left);
      else if (x > t->data)
        remove(x, t->right);
      else {
        BinaryNode<T>* oldNode;
        if (t->left == nullptr) { // has a right child or no children
          oldNode = t;
          t = t->right;
          delete oldNode;
          return;
        }
        else if (t->right == nullptr) { //has a left child
          oldNode = t;
          t = t->left;
          delete oldNode;
          return;
        }
        //has two children
        oldNode = findMin(t->right);
        t->data = oldNode->data;
        remove(t->data, t->right);
      }
      nodes--;
    };
    BinaryNode<T> *find(T item, BinaryNode<T> *t){
      if (t == nullptr)
      {
        return nullptr;
      }
      else if (item < t->data)
      {
        return find(item, t->left);
      }
      else if (item > t->data)
      {
        return find(item, t->right);
      }
      else
      {
        return t;    // Match
      }
    };
    void insert(T item, BinaryNode<T> *&t) {
      if (t == nullptr) {
        t = new BinaryNode<T>(item);
        root = t;
        nodes++;
      }
      else if (item < t->data){
        insert(item, t->left);
      }
      else if (item > t->data){
       insert(item, t->right);
      }
      else {};  // Duplicate entry; do nothing
    };
  };
#endif