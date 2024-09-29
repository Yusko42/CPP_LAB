#ifndef LAB0B_CSV_CREATION_H
#define LAB0B_CSV_CREATION_H

#include <iostream>
#include <map>
#include <vector>

class CSV_creation {
private:
    std::string input_file; //in.txt
    std::string output_file; //out.csv

    std::map<std::string, int> words;
    std::vector<std::pair<std::string, int>*> words_ordered;

    float words_counted = 0.0;

    static bool compare(std::pair<std::string, int>*, std::pair<std::string, int>*);
    std::string clean_word(std::string&);

public:
    CSV_creation(std::string&, std::string&);
    void setName(std::string&, std::string&);

    void words_from_txt();
    void sorting();
    int csv(std::string&);
};

#endif //LAB0B_CSV_CREATION_H
