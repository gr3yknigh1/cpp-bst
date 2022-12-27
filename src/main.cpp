#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

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

    PRINT("Inorder Tree Walk:");
    bst.InorderTreeWalk([](Node<Person>* n) {
        PRINT("key: " << n->key << " name: " << n->value->name << " age: " << n->value->age);
    });

    return 0;
}
