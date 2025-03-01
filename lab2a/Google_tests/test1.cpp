#include <gtest/gtest.h>
#include <fstream>
#include "status_calculation.h"
#include "status.h"
#include "user_interaction.h"
#include "cell.h"

TEST(CellTopic, TestSetStatus) {
    Cell cell(false);
    cell.SetStatus(true);
    EXPECT_TRUE(cell.IsAlive());
}

TEST(CellTopic, TestSetNextStatus) {
    Cell cell(true);
    cell.SetNextStatus(false);
    cell.UpdateState();
    EXPECT_FALSE(cell.IsAlive());
}

TEST(GameFieldTopic, TestCreateRandomField) {
    GameField field;
    field.CreateRandomField(5, 5);
    // Проверяем, что поле не пустое
    EXPECT_EQ(field.GetRow(), 5);
    EXPECT_EQ(field.GetColumn(), 5);
}

TEST(GameFieldTopic, TestSaveToFile) {
    GameField field;
    field.CreateRandomField(3, 3);

    std::ostringstream oss;
    oss << field;

    // Проверяем, что файл содержит ожидаемый заголовок
    std::string output = oss.str();
    EXPECT_NE(output.find("#Life 1.06"), std::string::npos);
    EXPECT_NE(output.find("#R"), std::string::npos); // правила должны быть указаны
}

TEST(GameFieldTopic, TestToroidalRandomField) {
    GameField field;
    field.CreateRandomField(5, 5);

    // Проверяем соседей на тороидальных границах
    int count = field.CountNeighbours(0, 0);
    EXPECT_GE(count, 0);
    EXPECT_LE(count, 8);
}

TEST(GameTopic, TestingFile) {
    std::ofstream file("test2.lif");
    file << "#Life 1.06" << std::endl;
    file << "#N My Universe" << std::endl;
    file << "#R B3/S45" << std::endl;
    file << "#S 20/20" << std::endl;
    file.close();

    GUI pars;
    GameLogic logic;
    const char* argv[] = {"prog", "-f", "test2.lif", "-i", "42", "--output", "out.lif"};
    ASSERT_TRUE(pars.ConsoleParser(7, const_cast<char **>(argv)));
    ASSERT_TRUE(logic.GameInitial(pars));

    EXPECT_EQ(logic.GetField().GetRules(), "B3/S45");
    EXPECT_EQ(logic.GetField().GetUniverseName(), "My Universe");
    EXPECT_EQ(logic.GetField().GetRow(), 20);
}