#pragma once
#include <string>

template<typename T>
struct Node {
    Node* left;
    Node* right;

    std::string key;
    const T* value;

    Node(const std::string& _key, const T* _value)
        : left(nullptr),
          right(nullptr),
          key(_key),
          value(_value) {}
};

template<typename T>
class BST {
public:
    BST() : _root(nullptr), _length(0) {}

    Node<T>* Insert(Node<T>* root, const std::string& key, const T* value) {
        if (root == nullptr) {
            root = new Node<T>(key, value);
            _length++;
            return root;
        }

        Node<T>* current;

        if (key < root->key) {
            current = Insert(root->left, key, value);
            root->left = current;
        } else if (key > root->key) {
            current = Insert(root->right, key, value);
            root->right = current;
        } else {
            root->value = value;
        }

        return root;
    }

    Node<T>* Insert(std::string key, const T* value) {
        _root = Insert(_root, key, value); return _root;
    }

    const T* Search(const Node<T>* root, const std::string& key) const {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->key == key) {
            return root->value;
        }

        if (key < root->key) {
            return Search(root->left, key);
        } else {
            return Search(root->right, key);
        }
    }

    const T* Search(const std::string& key) const {
        return Search(_root, key);
    }

    Node<T>* Delete(const std::string& key) {
        _root = Delete(_root, key);
        return _root;
    }

    Node<T>* Delete(Node<T>* root, const std::string& key) {
        if (root == nullptr) { return root; }

        if (root->key > key) {
            root->left = (Node<T>*)Delete(root->left, key);
            return root;
        } else if (root->key < key) {
            root->right = (Node<T>*)Delete(root->right, key);
            return root;
        }

        if (root->left == nullptr) {
            Node<T>* temp = root->right;
            _length--;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node<T>* temp = root->left;
            _length--;
            delete root;
            return temp;
        } else {
            Node<T>* parent = (Node<T>*)root;
            Node<T> *successor = root->right;
            while (successor->left != nullptr) {
                parent = successor;
                successor = successor->left;
            }

            if (parent != root)
                parent->left = successor->right;
            else
                parent->right = successor->right;

            root->value = successor->value;
            root->key = successor->key;
            delete successor;
            _length--;
            return root;
        }
    }

    Node<T>* GetMax() const {
        return GetMax(_root);
    }

    Node<T>* GetMax(Node<T>* root) const {
        Node<T>* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current;
    }

    unsigned long GetCount() const { return _length; }

    void InorderTreeWalk(void visit(Node<T>* node)) {
        return InorderTreeWalk(_root, visit);
    }

    void InorderTreeWalk(Node<T>* root, void visit(Node<T>* node)) {
        if (root != nullptr) {
            InorderTreeWalk(root->left, visit);
            visit(root);
            InorderTreeWalk(root->right, visit);
        }
    }

private:
    Node<T>* _root;
    unsigned long _length;
};
