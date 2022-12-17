#pragma once


template<typename K, typename V>
struct Pair {
    K first;
    V second;
};

template<typename K, typename V>
struct Node {
    Node* left;
    Node* right;
    Pair<K, V> value;
};

template<typename K, typename V>
class BST {
public:
    BST() {}

    void Push(Pair<K, V> pair);
    void Push(K key, V value);

    void Remove(K key);

    V Get(K key) const;
    bool Has(K key) const;
    unsigned long GetCount() const;

    // @TODO: Iterator

private:
    Node<K, V> m_Root;
    unsigned long m_Count;
};

