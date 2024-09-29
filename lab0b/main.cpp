#include <iostream>
#include <fstream>
#include <string>
#include "csv_creation.h"

int main(int argc, char* argv[]) {
    setlocale(LC_ALL, "");

    std::string input_file = argv[1];
    std::string output_file = argv[2];

    std::string line;
    std::ifstream in(input_file);

    if (argc != 3){
        std::cout << "Not enough information!" << std::endl;
        exit(0);
    }

    CSV_creation creation(input_file, output_file);
    creation.words_from_txt();
    creation.sorting();
    creation.csv(output_file);

    return 0;
}