#include "user_interaction.h"
#include <iostream>
#include <cstring>

GUI::GUI() : iterations_(0), offline_mode_(false) {}
const bool &GUI::GetIfOfflineMode() const { return offline_mode_; }
const int &GUI::GetIterations() const { return iterations_; }
const std::string& GUI::GetInputFile() { return input_file_; }
const std::string& GUI::GetOutputFile() { return output_file_; }
bool GUI::isHelpMode() const { return help_mode_; }

//Выводить если пользователь попросил либо что-то кривое всунул
void GUI::PrintHelp() {
    std::cout << "Usage: <filename> [options]" << std::endl;
    std::cout << "The options you can use:" << std::endl;
    std::cout << "\t-f\t--file\t\t[filename]\t Name of input file" << std::endl;
    std::cout << "\t-o\t--output\t[filename]\t Name of output file" << std::endl;
    std::cout << "\t-i\t--iterations\t[number]\t Number of iterations (for offline mode)" << std::endl;
    std::cout << "\t-h\t--help\t Print command help" << std::endl;
    std::cout << "\t \t \t " << std::endl;
}

bool GUI::ConsoleParser(int argc, char* argv[]) {
    std::string arg;
    for(int i = 1; i < argc; ++i) {
        arg = argv[i];
        if (arg == "-f" || arg == "--file") {
            if (i + 1 < argc)
                input_file_ = argv[++i];
            else {
                std::cerr << "ERROR: no input file name provided. \n"
                             "Please enter '-h' ot '--help' for list of commands." << std::endl;
                return false;
            }
        }
        else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc)
                output_file_ = argv[++i];
            else {
                std::cerr << "ERROR: no file name provided. \n"
                             "Please enter '-h' ot '--help' for list of commands." << std::endl;
                return false;
            }
        }
        else if (arg == "-i" || arg == "--iterations") {
            if (i + 1 < argc) {
                iterations_ = std::stoi(argv[++i]);
                if (iterations_ <= 0) {
                    std::cerr << "ERROR: number of iterations cannot be less than 1." << std::endl;
                    return false;
                }
            }
            else {
                std::cerr << "ERROR: no number of iterations provided. \n"
                             "Please enter '-h' ot '--help' for list of commands." << std::endl;
                return false;
            }
        }
        else if (arg == "-h" || arg == "--help") {
            PrintHelp();
            help_mode_ = true;
        }
    }
    offline_mode_ = isOfflineMode();
    return true;
}

bool GUI::isOfflineMode() {
    if (iterations_ > 0) {
        if (output_file_.empty()) {
            std::cerr << std::string("WARNING: number of iterations provided,"
                                     " but no output file name provided for offline mode.\n"
                                     "Online mode will be activated.\n") << std::endl;
            return false;
        }
        return true;
    }
    return false;
}
