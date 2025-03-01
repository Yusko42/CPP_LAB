#ifndef LAB2A_CELL_H
#define LAB2A_CELL_H

class Cell {
public:
    Cell();
    explicit Cell(bool status);

    [[nodiscard]] bool IsAlive() const;
    void SetStatus(bool status);
    void SetNextStatus(bool status);
    void UpdateState();
private:
    bool live_status; /** состояние клетки */
    bool next_status; /** следующее состояние */
};

#endif //LAB2A_CELL_H
