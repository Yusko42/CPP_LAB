#include <iostream>
#include <fstream>
#include <algorithm>
#include "csv_creation.h"

TxtReading::TxtReading(std::string &input) {
    SetName(input);
}

void TxtReading::SetName(std::string &input){
    input_file = input;
}

std::string TxtReading::CleanWord(std::string &full_word){
    std::string word;
    for(char c : full_word){
        if(std::isalnum(static_cast<char>(c)))
            word += std::tolower(static_cast<char>(c));
    }
    return word;
}

const std::map<std::string, int> & TxtReading::GetMap() const{
    return words;
}

const float & TxtReading::GetCount() const{
    return words_counted;
}

void TxtReading::WordsFromTxt(){
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

CsvCreation::CsvCreation(std::string &output){
    SetName(output);
}

void CsvCreation::SetName(std::string &output){
    output_file = output;
}

bool CsvCreation::Compare(std::pair<std::string, int>* a,
                          std::pair<std::string, int>* b) {
    if (a->second == b->second)
        return a->first < b->first;
    return a->second > b->second;
}

void CsvCreation::Sorting(std::map<std::string, int>& not_ordered){
    for (auto& pair: not_ordered)
        words_ordered.push_back(reinterpret_cast
        <std::pair<std::basic_string<char>, int> *const>(&pair));

    std::sort(words_ordered.begin(), words_ordered.end(), Compare);

}

int CsvCreation::CsvOutput(float& words_counted){
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

