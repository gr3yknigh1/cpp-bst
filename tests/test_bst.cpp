#include <string>
#include <criterion/criterion.h>

#include "bst/bst.hpp"

Test(test_bst, BST_Init) {
    BST<int, std::string> bst;

    cr_expect(true);
}
