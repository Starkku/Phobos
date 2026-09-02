#include "Body.h"

DEFINE_HOOK(0x62BE30, ParticleClass_Gas_AI_DriftSpeed, 0x0)
{
	enum { ContinueAI = 0x62BE60 };

	GET(ParticleClass*, pParticle, EBP);

	const auto pExt = ParticleTypeExt::Fetch(pParticle->Type);
	const int maxDriftSpeed = pExt->Gas_MaxDriftSpeed;
	const int minDriftSpeed = -maxDriftSpeed;

	if (pParticle->Velocity.X > maxDriftSpeed)
		pParticle->Velocity.X = maxDriftSpeed;
	else if (pParticle->Velocity.X < minDriftSpeed)
		pParticle->Velocity.X = minDriftSpeed;

	if (pParticle->Velocity.Y > maxDriftSpeed)
		pParticle->Velocity.Y = maxDriftSpeed;
	else if (pParticle->Velocity.Y < minDriftSpeed)
		pParticle->Velocity.Y = minDriftSpeed;

	return ContinueAI;
}

static SHPStruct* __fastcall ParticleClass_GetImage_Wrapper(ParticleClass* pThis)
{
	auto const pType = pThis->Type;
	auto const pTypeExt = ParticleTypeExt::Fetch(pType);
	size_t count = pTypeExt->RandomImages.size();

	if (count > 0)
	{
		// TODO: Pick in CTOR and store in extension class if ParticleExt is ever added.
		// Not worth adding extension for only this.
		uint32_t id = pThis->UniqueID; // Scramble sequential IDs.
		id ^= id >> 16;
		id *= 0x7feb352d;
		id ^= id >> 15;
		id *= 0x846ca68b;
		id ^= id >> 16;
		size_t index = id % count;

		return pTypeExt->RandomImages[index];
	}
	else
	{
		return pType->GetImage();
	}
}

DEFINE_FUNCTION_JUMP(VTABLE, 0x7EF9C0, ParticleClass_GetImage_Wrapper);
