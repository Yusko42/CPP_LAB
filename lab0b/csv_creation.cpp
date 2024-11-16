#include <iostream>
#include <fstream>
#include <algorithm>
#include "csv_creation.h"

CsvCreation::CsvCreation(std::string &output){
    SetName(output);
}

void CsvCreation::SetName(std::string &output){
    output_file = output;
}

bool CsvCreation::Compare(const std::pair<std::string, int>* a,
                          const std::pair<std::string, int>* b) {
    if (a->second == b->second)
        return a->first < b->first;
    return a->second > b->second;
}

void CsvCreation::Sorting(const std::map<std::string, int>& not_ordered){
    for (const auto& pair: not_ordered) {
        words_ordered.push_back(&pair);
    }
    std::sort(words_ordered.begin(), words_ordered.end(), Compare);

}//reinterpret_cast
//<std::pair<std::basic_string<char>, int> *const>(&pair)

int CsvCreation::CsvOutput(const float& words_counted){
    std::ofstream out(output_file);

    if (!out){
        std::cerr << "Error while creating a file!" << std::endl;
        exit(2);
    }
    out << "Word" << ";" << "Frequency" << ";" << "%" << "\n";
    for (auto& pair: words_ordered){
        out << pair->first << ";" << pair->second << ";" <<
        (pair->second/words_counted*100) << "\n";
    }
    out.close();

    std::cout << "Successfully finished!" << std::endl;
    return 0;
}

