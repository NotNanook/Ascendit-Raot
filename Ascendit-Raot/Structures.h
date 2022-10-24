#pragma once

class PlayerMain
{
public:
	char pad_0000[32]; //0x0000
	class MovementManager* movementManager; //0x0020
	char pad_0028[40]; //0x0028
	class EquipmentManager* equipmentManager; //0x0050
	class ActionManager* actionManager; //0x0058
	class CombatManager* combatManager; //0x0060
}; //Size: 0x0068

class MovementManager
{
public:
	char pad_0000[40]; //0x0000
	class LocalPlayerState* localPlayerState; //0x0028
	char pad_0030[8]; //0x0030
	class GroundLocomotion* groundLocomotion; //0x0038
}; //Size: 0x0040

class CombatManager
{
public:
	char pad_0000[48]; //0x0000
	class ParryHandler* parryHandler; //0x0030
	char pad_0038[8]; //0x0038
	class AttackHandlerLeft* attackLeft; //0x0040
	class AttackHandlerRight* attackRight; //0x0048
	char pad_0050[32]; //0x0050
	float missedAttackTime; //0x0070
}; //Size: 0x0074

class LocalPlayerState
{
public:
	char pad_0000[16]; //0x0000
	class GroundDetectorModule* grounddetectorModule; //0x0010
	char pad_0018[35]; //0x0018
	bool isEmoting; //0x003B
	char pad_003C[4]; //0x003C
	bool canAttackLeft; //0x0040
	char pad_0041[127]; //0x0041
	bool isSelectingEmote; //0x00C0
	bool isAnimationLocked; //0x00C1
	bool isInteractionLocked; //0x00C2
}; //Size: 0x00C3

class GroundDetectorModule
{
public:
	char pad_0000[64]; //0x0000
	float slopeAngle; //0x0040
}; //Size: 0x0044

class GroundLocomotion
{
public:
	char pad_0000[64]; //0x0000
	float groundSpeed; //0x0040
	float attackStartTime; //0x0044
	float attackSpeedMultiplier; //0x0048
	float colliderRadius; //0x004C
}; //Size: 0x0050

class EquipmentManager
{
public:
	char pad_0000[40]; //0x0000
	class GasModule* gasModule; //0x0028
	class StressModule* stressModule; //0x0030
	char pad_0038[32]; //0x0038
}; //Size: 0x0058

class GasModule
{
public:
	char pad_0000[24]; //0x0000
	float gasPercent; //0x0018
}; //Size: 0x001C

class StressModule
{
public:
	char pad_0000[24]; //0x0000
	float currentStress; //0x0018
}; //Size: 0x001C

class ActionManager
{
public:
	char pad_0000[56]; //0x0000
	class ReloadModule* reloadModule; //0x0038
	char pad_0040[8]; //0x0040
	class DodgeModule* dodgeModule; //0x0048
}; //Size: 0x0050

class ReloadModule
{
public:
	char pad_0000[40]; //0x0000
	bool canReloadLeft; //0x0028
	bool canReloadRight; //0x0029
	bool advancedReloaded; //0x002A
	char pad_002B[1]; //0x002B
	float reloadDuration; //0x002C
}; //Size: 0x0030

class DodgeModule
{
public:
	char pad_0000[40]; //0x0000
	bool isActive; //0x0028
	char pad_0029[3]; //0x0029
	float progress; //0x002C
}; //Size: 0x0030

class ParryHandler
{
public:
	char pad_0000[40]; //0x0000
	bool isParrying; //0x0028
}; //Size: 0x0029

class AttackHandlerLeft
{
public:
	char pad_0000[64]; //0x0000
	bool isActive; //0x0040
	bool isAttackSuccessful; //0x0041
	bool canOverStressFromMiss; //0x0042
	char pad_0043[1]; //0x0043
	bool attackChargePercent; //0x0044
}; //Size: 0x0045

class AttackHandlerRight
{
public:
	char pad_0000[64]; //0x0000
	bool isActive; //0x0040
	bool isAttackSuccessful; //0x0041
	bool canOverStressFromMiss; //0x0042
	char pad_0043[1]; //0x0043
	bool attackChargePercent; //0x0044
}; //Size: 0x0045

class HoldableItem
{
public:
	char pad_0000[51]; //0x0000
	bool infiniteAmmo; //0x0034
	bool hasSharedAmmoAndDurability; //0x0035
	bool isSingleShotUse; //0x0036
	char pad_0037[25]; //0x0037
	bool allowsHookedReloads; //0x0050
	bool allowsHookedUsage; //0x0051
	bool allowsBurstCharging; //0x0052

};

class CharacterObject
{
public:
	char pad_0000[104]; //0x0000
	class Transform *RigRootTransform; //0x0068
	char pad_0070[24]; //0x0070
	int8_t militaryRegiment; //0x0088
	char pad_0089[55]; //0x0089
	class HoldableItem *holdableItem; //0x00C0
}; //Size: 0x00D0

class WeaponParryData
{
public:
	char pad_0000[16]; //0x0000
	bool hasParryInvulnerability; //0x0010
	char pad_0011[3]; //0x0011
	float defensiveWindowTime; //0x0014
}; //Size: 0x0018

class MirrorClientObject
{
public:
	char pad_0000[104]; //0x0000
	std::string userName; //0x0068

};

class Vector3
{
public:
	float x;
	float y;
	float z;
};

class Transform
{
};