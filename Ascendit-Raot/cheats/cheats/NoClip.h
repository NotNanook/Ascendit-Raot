#include "Cheat.h"

class NoClip : public Cheat {
public:
	NoClip() : Cheat("NoClip", "Misc", { VK_NUMPAD4 }) {}

	void onRenderUpdate() override;
	void onDisable() override;
};

extern NoClip noClip;

