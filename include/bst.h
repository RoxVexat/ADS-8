// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insert(Node* node, const T& key) {
    if (node == nullptr) {
      return new Node(key);
    }
    if (key < node->key) {
      node->left = insert(node->left, key);
    } else if (key > node->key) {
      node->right = insert(node->right, key);
    } else {
      node->count++;
    }
    return node;
  }

  int depth(Node* node) const {
    if (node == nullptr) {
      return -1;
    }
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }

  Node* find(Node* node, const T& value) const {
    if (node == nullptr || node->key == value) {
      return node;
    }
    if (value < node->key) {
      return find(node->left, value);
    }
    return find(node->right, value);
  }

  void collectAll(Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (node == nullptr) {
      return;
    }
    collectAll(node->left, vec);
    vec.push_back(std::make_pair(node->key, node->count));
    collectAll(node->right, vec);
  }

  void clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    clear(root);
  }

  void insert(const T& key) {
    root = insert(root, key);
  }

  int depth() const {
    return depth(root);
  }

  int search(const T& value) const {
    Node* node = find(root, value);
    if (node == nullptr) {
      return 0;
    }
    return node->count;
  }

  std::vector<std::pair<T, int>> getAllSortedByKey() const {
    std::vector<std::pair<T, int>> vec;
    collectAll(root, vec);
    return vec;
  }

  std::vector<std::pair<T, int>> getAllSortedByFrequency() const {
    std::vector<std::pair<T, int>> vec;
    collectAll(root, vec);
    
    std::sort(vec.begin(), vec.end(),
      [](const std::pair<T, int>& a, const std::pair<T, int>& b) {
        if (a.second != b.second) {
          return a.second > b.second;
        }
        return a.first < b.first;
      });
    
    return vec;
  }

  bool empty() const {
    return root == nullptr;
  }
};

#endif  // INCLUDE_BST_H_
