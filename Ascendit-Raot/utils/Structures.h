#pragma once
#include <string>

struct PlayerMain {
	char pad_0000[32]; //0x0000
	struct MovementManager* movementManager; //0x0020
	char pad_0028[40]; //0x0028
	struct EquipmentManager* equipmentManager; //0x0050
	struct ActionManager* actionManager; //0x0058
	struct CombatManager* combatManager; //0x0060
}; //Size: 0x0068

struct MovementManager {
	char pad_0000[40]; //0x0000
	struct LocalPlayerState* localPlayerState; //0x0028
	char pad_0030[8]; //0x0030
	struct GroundLocomotion* groundLocomotion; //0x0038
}; //Size: 0x0040

struct CombatManager {
	char pad_0000[48]; //0x0000
	struct ParryHandler* parryHandler; //0x0030
	char pad_0038[8]; //0x0038
	struct AttackHandlerLeft* attackLeft; //0x0040
	struct AttackHandlerRight* attackRight; //0x0048
	char pad_0050[32]; //0x0050
	float missedAttackTime; //0x0070
}; //Size: 0x0074

struct LocalPlayerState {
	char pad_0000[16]; //0x0000
	struct GroundDetectorModule* grounddetectorModule; //0x0010
	char pad_0018[35]; //0x0018
	bool isEmoting; //0x003B
	char pad_003C[4]; //0x003C
	bool canAttackLeft; //0x0040
	char pad_0041[127]; //0x0041
	bool isSelectingEmote; //0x00C0
	bool isAnimationLocked; //0x00C1
	bool isInteractionLocked; //0x00C2
}; //Size: 0x00C3

struct GroundDetectorModule {
	char pad_0000[64]; //0x0000
	float slopeAngle; //0x0040
}; //Size: 0x0044

struct GroundLocomotion {
	char pad_0000[64]; //0x0000
	float groundSpeed; //0x0040
	float attackStartTime; //0x0044
	float attackSpeedMultiplier; //0x0048
	float colliderRadius; //0x004C
}; //Size: 0x0050

struct EquipmentManager {
	char pad_0000[40]; //0x0000
	struct GasModule* gasModule; //0x0028
	struct StressModule* stressModule; //0x0030
	char pad_0038[32]; //0x0038
}; //Size: 0x0058

struct GasModule {
	char pad_0000[24]; //0x0000
	float gasPercent; //0x0018
}; //Size: 0x001C

struct StressModule {
	char pad_0000[24]; //0x0000
	float currentStress; //0x0018
}; //Size: 0x001C

struct ActionManager {
	char pad_0000[56]; //0x0000
	struct ReloadModule* reloadModule; //0x0038
	char pad_0040[8]; //0x0040
	struct DodgeModule* dodgeModule; //0x0048
}; //Size: 0x0050

struct ReloadModule {
	char pad_0000[40]; //0x0000
	bool canReloadLeft; //0x0028
	bool canReloadRight; //0x0029
	bool advancedReloaded; //0x002A
	char pad_002B[1]; //0x002B
	float reloadDuration; //0x002C
}; //Size: 0x0030

struct DodgeModule {
	char pad_0000[40]; //0x0000
	bool isActive; //0x0028
	char pad_0029[3]; //0x0029
	float progress; //0x002C
}; //Size: 0x0030

struct ParryHandler {
	char pad_0000[40]; //0x0000
	bool isParrying; //0x0028
}; //Size: 0x0029

struct AttackHandlerLeft {
	char pad_0000[64]; //0x0000
	bool isActive; //0x0040
	bool isAttackSuccessful; //0x0041
	bool canOverStressFromMiss; //0x0042
	char pad_0043[1]; //0x0043
	bool attackChargePercent; //0x0044
}; //Size: 0x0045

struct AttackHandlerRight {
	char pad_0000[64]; //0x0000
	bool isActive; //0x0040
	bool isAttackSuccessful; //0x0041
	bool canOverStressFromMiss; //0x0042
	char pad_0043[1]; //0x0043
	bool attackChargePercent; //0x0044
}; //Size: 0x0045

struct HoldableItem {
	char pad_0000[48]; //0x0000
	int maxAmmo; //0x0030
	bool N0000015C; //0x0034
	char pad_0035[2]; //0x0035
	bool infiniteAmmo; //0x0037
	bool hasSharedAmmoAndDurability; //0x0038
	char pad_0039[119]; //0x0039
	int isLeftLoaded; //0x00B0
	int isRightLoaded; //0x00B4
}; //Size: 0x00B8

struct CharacterObject {
	char pad_0000[104]; //0x0000
	struct Transform* RigRootTransform; //0x0068
	char pad_0070[24]; //0x0070
	int8_t militaryRegiment; //0x0088
	char pad_0089[55]; //0x0089
	struct HoldableItem* equipedItem; //0x00C0
}; //Size: 0x00C8

struct WeaponParryData {
	char pad_0000[16]; //0x0000
	bool hasParryInvulnerability; //0x0010
	char pad_0011[3]; //0x0011
	float defensiveWindowTime; //0x0014
}; //Size: 0x0018

struct MirrorClientObject {
	char pad_0000[104]; //0x0000
	std::string userName; //0x0068
};

struct Vector3 {
	float x;
	float y;
	float z;
};

struct Transform {};

struct UnityScene {};

enum CursorLockMode {
	None,
	Locked,
	Confined
};