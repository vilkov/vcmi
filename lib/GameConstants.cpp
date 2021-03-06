/*
 * GameConstants.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#define INSTANTIATE_BASE_FOR_ID_HERE

#include "StdInc.h"

#include "VCMI_Lib.h"
#include "CDefObjInfoHandler.h"
#include "CArtHandler.h"
#include "CCreatureHandler.h"
#include "CSpellHandler.h"

#define ID_LIKE_OPERATORS_INTERNAL(A, B, AN, BN)	\
bool operator==(const A & a, const B & b)			\
{													\
	return AN == BN ;								\
}													\
bool operator!=(const A & a, const B & b)			\
{													\
	return AN != BN ;								\
}													\
bool operator<(const A & a, const B & b)			\
{													\
	return AN < BN ;								\
}													\
bool operator<=(const A & a, const B & b)			\
{													\
	return AN <= BN ;								\
}													\
bool operator>(const A & a, const B & b)			\
{													\
	return AN > BN ;								\
}													\
bool operator>=(const A & a, const B & b)			\
{													\
	return AN >= BN ;								\
}

#define ID_LIKE_OPERATORS(CLASS_NAME, ENUM_NAME)	\
	ID_LIKE_OPERATORS_INTERNAL(CLASS_NAME, CLASS_NAME, a.num, b.num)	\
	ID_LIKE_OPERATORS_INTERNAL(CLASS_NAME, ENUM_NAME, a.num, b)	\
	ID_LIKE_OPERATORS_INTERNAL(ENUM_NAME, CLASS_NAME, a, b.num)


ID_LIKE_OPERATORS(SecondarySkill, SecondarySkill::ESecondarySkill)

ID_LIKE_OPERATORS(Obj, Obj::EObj)

ID_LIKE_OPERATORS(ETerrainType, ETerrainType::EETerrainType)

ID_LIKE_OPERATORS(ArtifactID, ArtifactID::EArtifactID)

ID_LIKE_OPERATORS(ArtifactPosition, ArtifactPosition::EArtifactPosition)

ID_LIKE_OPERATORS(CreatureID, CreatureID::ECreatureID)

ID_LIKE_OPERATORS(SpellID, SpellID::ESpellID)

ID_LIKE_OPERATORS(BuildingID, BuildingID::EBuildingID)

ID_LIKE_OPERATORS(BFieldType, BFieldType::EBFieldType)


bmap<int, ConstTransitivePtr<CGDefInfo> > & Obj::toDefObjInfo() const
{
	return VLC->dobjinfo->gobjs[*this];
}

CArtifact * ArtifactID::toArtifact() const
{
	return VLC->arth->artifacts[*this];
}

CCreature * CreatureID::toCreature() const
{
	return VLC->creh->creatures[*this];
}

CSpell * SpellID::toSpell() const
{
	return VLC->spellh->spells[*this];
}

//template std::ostream & operator << <ArtifactInstanceID>(std::ostream & os, BaseForID<ArtifactInstanceID> id);
//template std::ostream & operator << <ObjectInstanceID>(std::ostream & os, BaseForID<ObjectInstanceID> id);
