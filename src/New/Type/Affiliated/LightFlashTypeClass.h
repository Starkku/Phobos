#pragma once

#include <Utilities/TemplateDef.h>

class LightFlashTypeClass
{
public:
	LightFlashTypeClass() = default;

	Nullable<int> Size;
	Valueable<bool> Red { true };
	Valueable<bool> Green { true };
	Valueable<bool> Blue { true };
	Valueable<bool> Black { false };

	SpotlightFlags Flags { SpotlightFlags::None }; // Set in parsing.

	void LoadFromINI(CCINIClass* pINI, const char* pSection, const char* baseKey, const char* sizeKey);
	bool Load(PhobosStreamReader& stm, bool registerForChange);
	bool Save(PhobosStreamWriter& stm) const;

	inline void CreateFlash(CoordStruct location, int defaultSize = 0) const
	{
		const int size = this->Size.Get(defaultSize);

		if (size > 0)
			MapClass::FlashbangWarheadAt(size, nullptr, location, true, this->Flags);
	}

private:
	template <typename T>
	bool Serialize(T& stm);
};
