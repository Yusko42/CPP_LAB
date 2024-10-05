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

    TxtReading txtread(input_file);
    txtread.WordsFromTxt();

    CsvCreation csvout(output_file);
    csvout.Sorting(const_cast<std::map<std::string, int> &>(txtread.GetMap()));
    csvout.CsvOutput(const_cast<float &>(txtread.GetCount()));

    return 0;
}