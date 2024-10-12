#ifndef LAB0B_TXT_READING_H
#define LAB0B_TXT_READING_H

#include <iostream>
#include <map>
#include <vector>

class TxtReading {
private:
    std::string input_file; //in.txt
    std::map<std::string, int> words;

    float words_counted = 0.0;
    std::string CleanWord(std::string&);
    void SetName(std::string&);
public:
    explicit TxtReading(std::string&);

    void WordsFromTxt();
    const std::map<std::string, int>& GetMap() const;
    const float& GetCount() const;
};

#endif //LAB0B_TXT_READING_H
