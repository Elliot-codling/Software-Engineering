#ifndef _TYPES_H
#define _TYPES_H

class C_Hash32
{
public:

	// Taken from http://stackoverflow.com/questions/2351087/what-is-the-best-32bit-hash-function-for-short-strings-tag-names

	C_Hash32();
	explicit C_Hash32(unsigned int hash);
	C_Hash32(const char* pData, unsigned int dataSize);
	explicit C_Hash32(const char* pData);

	void Zero();
	void GenerateHash(const char* pData, unsigned int dataSize);
	
	unsigned int GetHashValue();

private:

	unsigned int	value;
};

#endif
