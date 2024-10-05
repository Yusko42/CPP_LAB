#ifndef LAB0B_CSV_CREATION_H
#define LAB0B_CSV_CREATION_H

#include <iostream>
#include <map>
#include <vector>

class TxtReading {
private:
    std::string input_file; //in.txt
    std::map<std::string, int> words;

    float words_counted = 0.0;
    std::string CleanWord(std::string&);
public:
    explicit TxtReading(std::string&);
    void SetName(std::string&);

    void WordsFromTxt();
    const std::map<std::string, int> & GetMap() const;
    const float & GetCount() const;
};

class CsvCreation{
private:
    std::string output_file; //out.csv
    std::vector<std::pair<std::string, int>*> words_ordered;

    static bool Compare(std::pair<std::string, int>*, std::pair<std::string, int>*);
public:
    explicit CsvCreation(std::string&);
    void SetName(std::string&);

    void Sorting(std::map<std::string, int>&);
    int CsvOutput(float&);
};

#endif //LAB0B_CSV_CREATION_H
