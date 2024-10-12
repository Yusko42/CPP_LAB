#ifndef LAB0B_CSV_CREATION_H
#define LAB0B_CSV_CREATION_H

#include <iostream>
#include <map>
#include <vector>

class CsvCreation{
private:
    std::string output_file; //out.csv
    std::vector<std::pair<const std::string, int>*> words_ordered;

    static bool Compare(const std::pair<const std::string, int>*, const std::pair<const std::string, int>*);
    void SetName(std::string&);
public:
    explicit CsvCreation(std::string&);

    void Sorting(const std::map<std::string, int>&);
    int CsvOutput(const float&);
};

#endif //LAB0B_CSV_CREATION_H
