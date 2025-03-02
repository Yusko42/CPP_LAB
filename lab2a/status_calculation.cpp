#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "status_calculation.h"
#include "user_interaction.h"
#include "status.h"

#include <cstdlib>
#include <chrono>
#include <thread>

GameLogic::GameLogic() /*: iterations_(0)*/ = default;

void GameLogic::iteration(const int& iter_number) {
    field_.SetRules();

    for (int i = 0; i < iter_number; ++i)
        field_.UpdateField();
}

GameField &GameLogic::GetField() { return field_; }

void GameLogic::GenerateRandomField() {
    GameField new_field(20, 20);
    new_field.CreateRandomField(20, 20);
    field_ = new_field;
}

bool GameLogic::GameInitial(GUI& parser) {
    std::ifstream input_file(parser.GetInputFile());
    std::ofstream output_file(parser.GetOutputFile());

    if (!input_file.is_open()) {
        std::cerr << "WARNING: Input file cannot be opened." << std::endl;
    }

    if (parser.GetIfOfflineMode()) {
        if (parser.GetInputFile().empty() || !input_file.is_open()) {
            std::cout << "Random universe will be generated.\n" << std::endl;
            //инициализация для рандомного поля
            GenerateRandomField();
            iteration(parser.GetIterations());
            output_file << field_;
            std::cout << "\nOFFLINE: success!\n" << std::endl;
        } else {
            input_file >> field_;
            if (!input_file) {
                std::cerr << "ERROR: loading field from file failed." << std::endl;
                return false;
            }
            output_file << field_;
            std::cout << "\nOFFLINE: success!\n" << std::endl;
        }
    } else {
        if (parser.GetInputFile().empty() || !input_file.is_open()) {
            std::cout << "Random universe will be generated.\n" << std::endl;
            //Генерация поля, ожидание команд от пользователя
            GenerateRandomField();
        } else {
            //Полная логика: чтение, ожидание команд от игрока
            input_file >> field_;
        }
    }
    return true;
}

void GameLogic::Launch() {
    std::string command_line;
    std::cout << "Please enter your option in terminal:" << std::endl;
    while (true) {
        std::getline(std::cin, command_line);

        if (!ParsingString(command_line))
            break;
    }
}

bool GameLogic::ParsingString(std::string& line) {
    std::istringstream iss(line);
    std::string command;

    iss >> command;

    if (command == "dump") {
        std::string output_name;
        if (iss >> output_name) {
            if (output_name.empty())
                std::cerr << "ERROR: no output file name provided!" << std::endl;
            std::ofstream output_file(output_name);
            if (!output_file.is_open())
                std::cerr << "ERROR: couldn't open the file!" << std::endl;
            else
                output_file << field_;
            std::cout << "Success!" << std::endl;
        }
    }

    else if (command == "tick" || command == "t") {
        int iter_number = 1;
        if (iss >> iter_number) iteration(iter_number);
        else iteration(1);
        field_.PrintField();
    }

    else if (command == "exit") {
        return false;
    }

    else if (command == "play") {
        int iter_number = 1;
        if (iss >> iter_number) PlayLive(iter_number);
        else PlayLive(1);
    }

    else if (command == "help") {
        std::cout << "\tdump <filename> -- save the universe as a file" << std::endl
                  << "\ttick <N=1> or t <N=1> -- calculate and print the result after N iterations" << std::endl
                  << "\texit -- close the game and exit the program" << std::endl
                  << "\thelp -- print command help\n" << std::endl;
    }
    else {
        std::cout << "No such a command; "
                     "please enter 'help' for the list of available commands\n" << std::endl;
    }
    return true;

}

//FOR EXPERIMENTAL PURPOSES: WORKS WITH WINDOWS SYSTEM ONLY!
//Sorry for system("cls"), I know this is pure evil...

//exclusive: something like "play 42" - display all 42 iter-s of the field.
//If there is no cells left, this GAME is OVER!
/*
 * bool GameLogic::PlayLive(int iterations) {
    if (iterations <= 0) {
        std::cerr << "WARNING: number of iterations cannot be less than 0.\n";
        return false;
    }
    field_.SetRules();
    int local_int = 0;

    using namespace std::this_thread;
    using namespace std::chrono;

    while (local_int < iterations) {
        //clearing the screen
        std::system("cls");

        field_.UpdateField();
        field_.PrintField();

        //if GAME OVER...
        if (field_.CountCells() == 0) {
            std::cout << "\t GAME OVER \t\n" <<
            "All cells are dead from the " << local_int << "iteration.\n" << std::endl;
            std::cout << "Thank You for playing!";
            return true;
        }

        //usleep or something
        sleep_for(nanoseconds(50));
        sleep_until(system_clock::now() + seconds(1));
        ++local_int;
    }
    std:: cout << "DONE: " << local_int << " iterations." << std::endl;
    return true;
}
 */
