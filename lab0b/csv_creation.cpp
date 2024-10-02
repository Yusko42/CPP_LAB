#include <iostream>
#include <fstream>
#include <algorithm>
#include "csv_creation.h"

bool CsvCreation::Compare(std::pair<std::string, int>* a,
                          std::pair<std::string, int>* b) {
    if (a->second == b->second)
        return a->first < b->first;
    return a->second > b->second;
}

std::string CsvCreation::CleanWord(std::string &full_word){
    std::string word;
    for(char c : full_word){
        if(std::isalnum(static_cast<char>(c)))
            word += std::tolower(static_cast<char>(c));
    }
    return word;
}

CsvCreation::CsvCreation(std::string &input, std::string &output) {
    SetName(input, output);
}

void CsvCreation::SetName(std::string &input, std::string &output){
    input_file = input;
    output_file = output;
}

void CsvCreation::WordsFromTxt(){
    std::ifstream in(input_file);

    if (!in){
        std::cerr << "Error while opening a file!" << std::endl;
        exit(1);
    }

    std::string line;
    while (in >> line){
        std::string clean_word = CleanWord(line);
        if (!clean_word.empty()){
            ++words[clean_word];
            ++words_counted;
        }
    }
    in.close();
}

void CsvCreation::Sorting(){
    for (auto& pair: words)
        words_ordered.push_back(reinterpret_cast
        <std::pair<std::basic_string<char>, int> *const>(&pair));

    std::sort(words_ordered.begin(), words_ordered.end(), Compare);

}

int CsvCreation::CsvOutput(){
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