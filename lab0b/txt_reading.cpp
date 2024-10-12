#include <iostream>
#include <fstream>
#include "txt_reading.h"


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
        exit(1); //return лучше бы поставить throw, try
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