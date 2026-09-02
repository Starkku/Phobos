#include "LightFlashTypeClass.h"

void LightFlashTypeClass::LoadFromINI(CCINIClass* pINI, const char* pSection, const char* baseKey, const char* sizeKey)
{
	INI_EX exINI(pINI);

	auto makeKey = [baseKey](const char* suffix)
		{
			return std::string(baseKey) + "." + suffix;
		};

	this->Size.Read(exINI, pSection, makeKey(sizeKey).c_str());
	this->Red.Read(exINI, pSection, makeKey("Red").c_str());
	this->Green.Read(exINI, pSection, makeKey("Green").c_str());
	this->Blue.Read(exINI, pSection, makeKey("Blue").c_str());
	this->Black.Read(exINI, pSection, makeKey("Black").c_str());

	Flags = SpotlightFlags::None;

	if (this->Black)
	{
		Flags = SpotlightFlags::NoColor;
	}
	else
	{
		if (!this->Red)
			Flags = SpotlightFlags::NoRed;
		if (!this->Green)
			Flags |= SpotlightFlags::NoGreen;
		if (!this->Blue)
			Flags |= SpotlightFlags::NoBlue;
	}
}

#pragma region(save/load)

template <class T>
bool LightFlashTypeClass::Serialize(T& stm)
{
	return stm
		.Process(this->Size)
		.Process(this->Red)
		.Process(this->Green)
		.Process(this->Blue)
		.Process(this->Black)
		.Process(this->Flags)
		.Success();
}

bool LightFlashTypeClass::Load(PhobosStreamReader& stm, bool registerForChange)
{
	return this->Serialize(stm);
}

bool LightFlashTypeClass::Save(PhobosStreamWriter& stm) const
{
	return const_cast<LightFlashTypeClass*>(this)->Serialize(stm);
}

#pragma endregion(save/load)

