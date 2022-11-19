#include "linkedhashset.hpp"

int main() {
    // linkedhs set1;

    // set1.insert(element(0, "Anton")); // the same hash
    // set1.insert(element(13, "Olya"));
    // set1.insert(element(13, "Olya"));
    // set1.insert(element(5, "Kapop")); // the same hash
    // set1.insert(element(71, "Kirill"));
    // set1.insert(element(36, "Gosha"));

    // set1.print();
    // std::cout << "size of set1 is " << set1.size() << std::endl;
    // std::cout << "============" << std::endl;

    // set1.remove(element(0, "Anton"));
    // linkedhs assignSet1;
    // assignSet1 = set1;
    // std::cout << "after assignment:" << std::endl;
    // assignSet1.print();
    // std::cout << "size of assignSet1 is " << assignSet1.size()
    //           << std::endl;
    // std::cout << "============" << std::endl;

    // assignSet1.remove(element(36, "Gosha"));
    // linkedhs set2(assignSet1);
    // std::cout << "after copying:" << std::endl;
    // set2.print();
    // std::cout << "size of set2 is " << set2.size() << std::endl;
    // std::cout << "============" << std::endl;

    // set1.remove(element(0, "Anton"));
    // set1.remove(element(13, "Olya"));

    // set1.remove(element(5, "Kapop"));
    // set1.remove(element(5, "Kapop"));
    // set1.remove(element(71, "Kirill"));
    // set1.remove(element(0, "Anton"));
    // set1.remove(element(36, "Gosha"));

    // std::cout << "after removing:" << std::endl;
    // std::cout << "size of set1 is " << set1.size() << std::endl;
    // set1.print();
    // std::cout << "============" << std::endl;

    // linkedhs set3;
    // for (int i = 0; i < 10; i++){
    //     set1.insert(element(i, "Name"));
    // }

    // linkedhs set4;
    // for (int i = 0; i < 10; i++){
    //     set2.insert(element(i, "Name"));
    // }
    // if (set3 == set4){
    //     std::cout<< "set3 == set4" << std::endl;
    // }

    linkedhs set5;
    for (int i = 0; i < 3; i++) {
        set5.insert(element(i, "student girls"));
    }

    linkedhs set6;
    for (int i = 0; i < 2; i++) {
        set6.insert(element(i, "student boys"));
    }

    set6.swap(set5);
    std::cout << "after swapping set5 is" << std::endl;
    set5.print();
    std::cout << "===========" << std::endl;
    std::cout << "after swapping set6 is" << std::endl;
    set6.print();

    std::cout << "================================" << std::endl;

    linkedhs set7;
    for (int i = 0; i < 5; i++) {
        set7.insert(element(i, "student cats"));
    }

    linkedhs set8;
    for (int i = 0; i < 3; i++) {
        set8.insert(element(i, "student dogs"));
    }

    set8.swap(set7);
    std::cout << "after swapping set7 is" << std::endl;
    set7.print();
    std::cout << "===========" << std::endl;
    std::cout << "after swapping set8 is" << std::endl;
    set8.print();

    return 0;
}
