#ifndef LAB0B_CSV_CREATION_H
#define LAB0B_CSV_CREATION_H

#include <iostream>
#include <map>
#include <vector>

class CsvCreation {
private:
    std::string input_file; //in.txt
    std::string output_file; //out.csv

    std::map<std::string, int> words;
    std::vector<std::pair<std::string, int>*> words_ordered;

    float words_counted = 0.0;

    static bool Compare(std::pair<std::string, int>*, std::pair<std::string, int>*);
    std::string CleanWord(std::string&);

public:
    CsvCreation(std::string&, std::string&);
    void SetName(std::string&, std::string&);

    void WordsFromTxt();
    void Sorting();
    int CsvOutput();
};

#endif //LAB0B_CSV_CREATION_H
