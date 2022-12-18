#include <iostream>
#include <string>
#include <vector>

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

#define PRINT(X) std::cout << X << std::endl;

struct Person {
    std::string name;
    unsigned int age;
};


int RandInt(int min, int max) {
    /*
     * Values in range: [min, max]
     * */
    return min + rand() % (max - min + 1);
}

const std::string GenerateString(unsigned long length) {
    std::string string;
    for (unsigned long i = 0; i < length; i++) {
        string += (char)RandInt(65, 90);
    }
    return string;
}

const std::vector<Person> GeneratePersons(unsigned long count) {
    std::vector<Person> persons;
    persons.reserve(count);

    for (unsigned long i = 0; i < count; i++) {
        persons.emplace_back(
            (Person){ GenerateString(10), (unsigned int)RandInt(1, 99) });
    }

    return persons;
}

int main() {

    BST<Person> bst;
    auto persons = GeneratePersons(100);

    for (auto & p : persons) {
        bst.Insert(GenerateString(5), &p);
    }

    // Person p1 = { "Ilya", 19 };
    // Person p2 = { "Tolya", 18 };
    // Person p3 = { "Vaidm", 20 };
    // Person p4 = { "Kolya", 20 };
    // Person p5 = { "Seraphom", 20 };
    //
    // bst.Insert("key1", &p1);
    // bst.Insert("key2", &p2);
    // bst.Insert("key3", &p3);
    // bst.Insert("key5", &p4);
    // bst.Insert("key10", &p5);
    // // bst.Delete("key5");
    //
    // auto v = bst.Search("key5");
    // if (v != nullptr) {
    //     PRINT(v->name);
    // }
    //
    //
    // PRINT("-- Count:");
    // PRINT(bst.GetCount());
    //
    // PRINT("-- Max:");
    // PRINT(bst.GetMax()->key);

    // for (auto n : bst) {
    //     PRINT(n.key);
    // }

    PRINT("Inorder Tree Walk:");
    bst.InorderTreeWalk([](Node<Person>* n) {
        PRINT("key: " << n->key << " name: " << n->value->name << " age: " << n->value->age);
    });

    return 0;
}
