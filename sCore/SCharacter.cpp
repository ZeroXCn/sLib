#include "SCharacter.h"

const char SCharacter::MAX_VALUE = CHAR_MAX;
const char SCharacter::MIN_VALUE = CHAR_MIN;

const int SCharacter::SIZE = sizeof(TCHAR);
///
SCharacter::SCharacter(TCHAR ch) :
SNumber(ch)
{

}

SCharacter SCharacter::ValueOf(TCHAR i)
{
	return SCharacter(i);
}
SCharacter SCharacter::ValueOf(SString s)
{
	if (s.size() > 0)return SCharacter(s.at(0));
	else return SCharacter(0);
}

SString SCharacter::ToHexString(TCHAR num, bool bIsUpper)
{
	if (bIsUpper)return SString::Format(_T("%X"), num);
	else return SString::Format(_T("%x"), num);
}

TCHAR SCharacter::ParseInt(SString s)
{
	if (s.size() > 0)return s.at(0);
	else return 0;
}