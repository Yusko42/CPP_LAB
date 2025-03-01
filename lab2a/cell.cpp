#include "cell.h"

Cell::Cell() : live_status(false), next_status(false) {}
Cell::Cell(bool status) : live_status(status), next_status(false) {}

bool Cell::IsAlive() const { return live_status; }
void Cell::SetStatus(bool status) { live_status = status; }
void Cell::SetNextStatus(bool status) { next_status = status; }
void Cell::UpdateState() { live_status = next_status; }
