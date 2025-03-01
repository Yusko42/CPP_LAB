#include <iostream>
#include "status.h"
#include "user_interaction.h"
#include "status_calculation.h"

int main(int argc, char** argv) {
    GUI pars;
    if (!pars.ConsoleParser(argc, argv)){
        if (pars.isHelpMode())
            return 0;
        else {
            std::cerr << "ERROR: parsing closed." << std::endl;
        }
    }
    GameLogic logic;

    if (!logic.GameInitial(pars)) return 1;
    logic.Launch();

    return 0;
}
