#include <iostream>
#include <fstream>
#include <string>
#include "csv_creation.h"

int main(int argc, char* argv[]) {
    //setlocale(LC_ALL, "");
    std::string input_file = argv[1];
    std::string output_file = argv[2];

    if (argc > 3){
        std::cout << "That is too much!" << std::endl;
        exit(0);
    }

    CsvCreation creation(input_file, output_file);

    creation.WordsFromTxt();
    creation.Sorting();
    creation.CsvOutput();

    return 0;
}