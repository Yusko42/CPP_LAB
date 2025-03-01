#include "status.h"

#ifndef LAB2A_STATUS_CALCULATION_H
#define LAB2A_STATUS_CALCULATION_H

class GameLogic {
public:
    //explicit GameLogic(GameField& field);
    explicit GameLogic();
    ~GameLogic() = default;

    GameField& GetField();

    bool GameInitial(GUI &parser);
    void Launch();
private:
    //int iterations_;
    GameField field_;

    void GenerateRandomField();
    bool ParsingString(std::string& line);
    void iteration(const int& iter_number);

    //FOR EXPERIMENTAL PURPOSES:
    //bool PlayLive(int iterations);
};

#endif //LAB2A_STATUS_CALCULATION_H
