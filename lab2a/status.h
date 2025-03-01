#include <cstdio>
#include <vector>
#include <set>
#include "cell.h"
#include "user_interaction.h"
#ifndef LAB2A_STATUS_H
#define LAB2A_STATUS_H

class GameField {
    public:
        explicit GameField(int rows = 20, int cols = 20);
        /*explicit GameField(const std::string & input_file, int rows, int cols);*/
        ~GameField();
        void UpdateField();
        void PrintField();

        void SetRules();

        void CreateRandomField(int rows, int cols);

        int CountNeighbours(int i, int j);

        int CountCells();

        [[nodiscard]] std::vector<std::vector<Cell>>& GetField();
        [[nodiscard]] const int& GetRow() const;
        [[nodiscard]] const int& GetColumn() const;
        [[nodiscard]] const std::string& GetUniverseName() const;
        [[nodiscard]] const std::string& GetRules() const;

    private:
        int row_length_ = 20;
        int colm_length_ = 20;
        std::string universe_name_ = "New Universe"; /** Name of the Universe */
        std::vector<std::vector<Cell>> game_field_; /** Field of the Universe */

        std::string rules_ = "B3/S23";
        std::set<int> birth_numbers_;
        std::set<int> survival_numbers_;

        static bool RulesCorrect(const std::string& rules);
        friend std::istream& operator>>(std::istream& is, GameField& field);
        friend std::ostream& operator<<(std::ostream& os, GameField& field);

        void CalculatingCellStatus(Cell& cell, int neighbours);
};

#endif //LAB2A_STATUS_H
