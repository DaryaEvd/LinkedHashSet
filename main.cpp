#include "linkedhashset.hpp"

int main() {
    linkedhs set1;
    set1.insert(element(19, "Dasha"));

    set1.insert(element(19, "Dasha"));

    set1.insert(element(18, "Dasha"));

    set1.insert(element(19, "Nastya"));

    set1.insert(element(19, "Olya"));
    
    set1.insert(element(19, "Nadya"));
 
    set1.print();
    std::cout<< "============" << std::endl;
    set1.remove(element(18, "Dasha"));
    set1.print();

    return 0;
}
