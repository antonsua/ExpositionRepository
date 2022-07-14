#include "Spinner.h"

Spinner::Spinner(Game* game) : Entity(game) {
}

Spinner::~Spinner() {
}

void Spinner::endMovement(bool timeOut) {
	send(&Message(BOARD_SPINNED));
}

void Spinner::endResizing() {
	send(&Message(BOARD_SPINNED_SIZE));
}
