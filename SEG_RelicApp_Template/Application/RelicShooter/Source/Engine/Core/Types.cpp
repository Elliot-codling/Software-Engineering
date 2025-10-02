#include "Types.h"
#include <cstring>

C_Hash32::C_Hash32()
	: value(0)
{
}

C_Hash32::C_Hash32(const unsigned int hash)
	: value(hash) 
{
}

C_Hash32::C_Hash32(const char* pData, const unsigned int dataSize)
	: value(0)
{
	GenerateHash(pData, dataSize);
}

C_Hash32::C_Hash32(const char* pData)
	: value(0)
{
	const unsigned int dataSize = strlen(pData);
	GenerateHash(pData, dataSize);
}

void C_Hash32::Zero() { value = 0; }

void C_Hash32::GenerateHash(const char* pData, const unsigned int dataSize)
{
	for (unsigned int i = 0; i < dataSize; i++)
	{
		value = 31 * value + *pData++;	// 31 or 37 are good apparently.
	}
}

unsigned int C_Hash32::GetHashValue()
{
	return value;
}
