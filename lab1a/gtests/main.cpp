#include "bitarray.h"

int main() {
    BitArray new_array(32, 4294967295);
    new_array.push_back(0);
    new_array.push_back(1);
    new_array.PrintData(1);


    /*BitArray ba(10);
    for (auto v: ba){
        std::cout << v << " ";
    }
    std::cout << std::endl;*/

    return 0;
}
