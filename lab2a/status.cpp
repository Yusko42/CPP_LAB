#include <string>
#include <fstream>
#include <random>
#include <sstream>
#include <iostream>
#include "status.h"
#include "user_interaction.h"

GameField::GameField(int rows, int cols) : row_length_(rows), colm_length_(cols),
    game_field_(rows, std::vector<Cell>(rows)) {};

GameField::~GameField() = default;

bool GameField::RulesCorrect(const std::string& rules) {
    if (rules[0] != 'B') return false;
    if (rules.rfind('/') == std::string::npos) return false;

    size_t slash = rules.find('/');
    if (rules[slash+1] != 'S') return false;
    if ((slash + 2) > rules.size()) return false;

    std::string birth = rules.substr(1, slash - 1);
    std::string survive = rules.substr(slash + 2);

    if (birth.empty() || survive.empty()) return false;

    for (char n: birth)
        if (!std::isdigit(n)) return false;

    for (char n: survive)
        if (!std::isdigit(n)) return false;

    return true;
}

std::istream& operator>>(std::istream& is, GameField& field) {
    std::string line;
    bool first_checked = false;

    while(std::getline(is, line)) {
        if (line.empty()) continue;

        //Case: string is not (x,y)-cell
        if (line[0] == '#') {
            if (line != "#Life 1.06" & !first_checked)
                is.setstate(std::ios::failbit);
            first_checked = true;

            if (line.substr(0,2) == "#N") {
                field.universe_name_ = line.substr(3);
            }

            if (line.substr(0,2) == "#R") {
                field.rules_ = line.substr(3);
                if (!field.RulesCorrect(field.rules_)) {
                    is.setstate(std::ios::failbit);
                    return is;
                }
            }

            if (line.substr(0,2) == "#S") {
                size_t slash = line.find('/');

                //Нужна обработка ошибок при некорректном переводе
                field.colm_length_ = stoi(line.substr(3, slash - 3));
                field.row_length_ = stoi(line.substr(slash + 1));
            }
        } else {
            std::istringstream iss(line);
            int x, y;

            if (iss >> x >> y) {
                int wrap_x = (x % field.GetRow() + field.GetRow()) % field.GetRow();
                int wrap_y = (y % field.GetColumn() + field.GetColumn()) % field.GetColumn();

                if (field.game_field_[wrap_x][wrap_y].IsAlive())
                    std::cout << "WARNING: two similar cells in file: ("
                    << wrap_x << ", " << wrap_y <<")\n" << std::endl;

                //Теперь даже отрицательные координаты могут быть записаны
                if (wrap_x >= 0 && wrap_x <= field.GetRow() || wrap_y >= 0 && wrap_y <= field.GetColumn()) {
                    field.game_field_[wrap_x][wrap_y].SetStatus(true);
                }
            } else {
                is.setstate(std::ios::failbit);
                return is;
            }
        }
    }

    is.clear();
    return is;
}

std::ostream& operator<<(std::ostream& os, GameField& field) {
    os << "#Life 1.06\n";
    os << "#N " << field.GetUniverseName() << "\n";
    os << "#R " << field.GetRules() << "\n";

    for (int y = 0; y < field.GetColumn(); ++y)
        for (int x = 0; x < field.GetRow(); ++x) {
            if (field.game_field_[x][y].IsAlive()) {
                os << x << " " << y << "\n";
            }
        }

    os.flush(); // Сбрасываем буфер
    return os;
}

//Случайное поле
void GameField::CreateRandomField(int rows, int cols) {
    game_field_ = std::vector<std::vector<Cell>>(rows,std::vector<Cell>(cols));
    row_length_ = rows;
    colm_length_ = cols;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    // Заполнение поля случайными значениями
    for (int x = 0; x < rows; ++x) {
        for (int y = 0; y < cols; ++y) {
            game_field_[x][y].SetStatus(dis(gen));
        }
    }
}


std::vector<std::vector<Cell>> &GameField::GetField() {
    return game_field_;
}
const int& GameField::GetRow() const { return row_length_; }
const int& GameField::GetColumn() const { return colm_length_; }
const std::string &GameField::GetUniverseName() const { return universe_name_; }
const std::string &GameField::GetRules() const { return rules_; }

int GameField::CountNeighbours(int i, int j){
    int counter = 0;

    auto wrap = [](int idx, int size) {
        return (idx + size) % size;
    };

    for (int i_idx = -1; i_idx <= 1; ++i_idx) {
        for (int j_idx = -1; j_idx <= 1; ++j_idx) {
            if (i_idx == 0 && j_idx == 0)
                continue;
            int ni = wrap(i + i_idx, row_length_);
            int nj = wrap(j + j_idx, colm_length_);
            if (game_field_[ni][nj].IsAlive())
                ++counter;
        }
    }
    return counter;
}

void GameField::SetRules() {
    size_t slash = rules_.find('/');
    std::string birth = rules_.substr(1, slash - 1);
    std::string survive = rules_.substr(slash + 2);

    for (auto n: birth)
        birth_numbers_.insert(n - '0');
    for (auto n: survive)
        survival_numbers_.insert(n - '0');
}

void GameField::CalculatingCellStatus(Cell& cell, int neighbours){
    if (cell.IsAlive()){
        cell.SetNextStatus(survival_numbers_.count(neighbours) > 0);
    }
    else {
        cell.SetNextStatus(birth_numbers_.count(neighbours) > 0);
    }
}

void GameField::UpdateField(){
    for (int y = 0; y < colm_length_; ++y){
        for (int x = 0; x < row_length_; ++x){
            int count = CountNeighbours(x, y);
            CalculatingCellStatus(game_field_[x][y], count);
        }
    }

    for (int y = 0; y < colm_length_; ++y) {
        for (int x = 0; x < row_length_; ++x) {
            game_field_[x][y].UpdateState();
        }
    }
}

void GameField::PrintField() {
    std::cout << "Name: " << GetUniverseName() << std::endl;
    std::cout << "Rules: " << GetRules() << std::endl;
    for (int y = 0; y < colm_length_; ++y) {
        for (int x = 0; x < row_length_; ++x) {
            if (game_field_[x][y].IsAlive()) printf("*");
            else printf(" ");
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

//GameLogic::GameLogic(GameField& field) : iterations_(0), field_(field) {}

//FOR THE EXPERIMENTAL PURPOSES
int GameField::CountCells() {
    int counter = 0;
    for (int y = 0; y < colm_length_; ++y) {
        for (int x = 0; x < row_length_; ++x) {
            counter += game_field_[x][y].IsAlive();
        }
    }
    return counter;
}
