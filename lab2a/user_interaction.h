#ifndef LAB2A_USER_INTERACTION_H
#define LAB2A_USER_INTERACTION_H
#include <string>

class GUI {
public:
    GUI();
    ~GUI() = default;
    bool ConsoleParser(int argc, char* argv[]);
    [[nodiscard]] const bool& GetIfOfflineMode() const;
    [[nodiscard]] const int& GetIterations() const;
    const std::string& GetInputFile();
    const std::string& GetOutputFile();
    [[nodiscard]] bool isHelpMode() const;
private:
    bool offline_mode_;
    bool help_mode_ = false;
    int iterations_;
    std::string input_file_;

    std::string output_file_;
    bool isOfflineMode();
    static void PrintHelp();
};

#endif //LAB2A_USER_INTERACTION_H
