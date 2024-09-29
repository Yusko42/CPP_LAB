#include <iostream>
#include <fstream>
#include <algorithm>
#include "csv_creation.h"

std::string CSV_creation::clean_word(std::string &full_word){
    std::string word;
    for(char c : full_word){
        if(std::isalnum(static_cast<char>(c)))
            word += std::tolower(static_cast<char>(c));
    }
    return word;
}

bool CSV_creation::compare(std::pair<std::string, int>* a,
                           std::pair<std::string, int>* b) {
    if (a->second == b->second)
        return a->first < b->first;
    return a->second > b->second;
}

CSV_creation::CSV_creation(std::string &input, std::string &output) {
    setName(input, output);
};

void CSV_creation::setName(std::string &input, std::string &output){
    input_file = input;
    output_file = output;
}

void CSV_creation::words_from_txt(){
    std::ifstream in(input_file);

    if (!in){
        std::cerr << "Error while opening a file!" << std::endl;;
        exit(1);
    }

    std::string line;
    while (in >> line){
        std::string CleanWord = clean_word(line);
        if (!CleanWord.empty()){
            ++words[CleanWord];
            ++words_counted;
        }
    }
    in.close();
}

void CSV_creation::sorting(){
    for (auto& pair: words)
        words_ordered.push_back(reinterpret_cast
        <std::pair<std::basic_string<char>, int> *const>(&pair));

    std::sort(words_ordered.begin(), words_ordered.end(), compare);

}

int CSV_creation::csv(std::string& output){
    std::ofstream out(output_file);

    if (!out){
        std::cerr << "Error while creating a file!" << std::endl;;
        exit(2);
    }
    out << "Word" << ";" << "Frequency" << ";" << "%" << "\n";
    for (auto& pair: words_ordered){
        out << pair->first << ";" << pair->second << ";" << (pair->second/words_counted*100) << "\n";
    }
    out.close();

    std::cout << "Successfully finished!" << std::endl;
    return 0;
}