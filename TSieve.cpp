#include "TSieve.h"

BitField sieve(const BitField& inpBF)
{
	BitField outBF(inpBF);
	outBF.unload_bit(0);
	unsigned int startBit = 2;
	while ( startBit < (outBF.size() / 2 + 1 ) )
	{
		if (outBF.getBit(startBit) )
		{
			int pos = startBit;
			while ( pos < outBF.size() )
			{
				pos += startBit;
				if ( pos < outBF.size() )
				{
					outBF.unload_bit(pos);
				}
			}
		}
		++startBit;
	}
	return outBF;
}