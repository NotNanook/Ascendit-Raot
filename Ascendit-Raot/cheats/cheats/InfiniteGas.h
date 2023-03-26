#include "Cheat.h"

class InfiniteGas : public Cheat {
public:
	InfiniteGas() : Cheat("Infinite Gas", "Combat", { VK_NUMPAD1 }) {}

	void onRenderUpdate() override;
};

extern InfiniteGas infiniteGas;

