#include "TBitField.h"

int BitField::get_BlockIndex(int n)
{
	return n / (blockSize * 8);
}

TELEM BitField::get_BlockMask(int bitShift)
{
	return (TELEM)(1 << bitShift);
}

BitField::BitField( int length)
{
	MemLen = length;
	numOfBlocks = MemLen / (blockSize * BYTE);
	
	if ((numOfBlocks * (blockSize * BYTE)) < MemLen) {
		++numOfBlocks;
	}
	Mem = new TELEM[numOfBlocks];

	for (int i = 0; i < numOfBlocks; ++i) {
		Mem[i] = 0;
	}
}
//cpBF = bt
BitField::BitField(const BitField &bt) : MemLen{ bt.MemLen }, numOfBlocks{ bt.numOfBlocks }
{
	Mem = new TELEM[numOfBlocks];
	std::copy(bt.Mem, bt.Mem + numOfBlocks, Mem);
}

void BitField::operator = (const BitField &bt)
{
	if (numOfBlocks != bt.numOfBlocks)
	{
		delete[]Mem;
		MemLen = bt.MemLen;
		numOfBlocks = bt.numOfBlocks;
		Mem = new TELEM[MemLen];
	}
	std::copy(bt.Mem, bt.Mem + numOfBlocks, Mem);
}


size_t BitField::get_numOfBlocks() const
{
	return numOfBlocks;
}

size_t BitField::size() const
{
	return MemLen;
}

BitField::~BitField()
{
	delete[] Mem;
}

void BitField::load_AllBits()
{
	for (int i = 0; i < numOfBlocks; ++i)
		Mem[i] |= GetMemMask();
}

void BitField::unload_AllBits()
{
	for (int i = 0; i < numOfBlocks; ++i)
		Mem[i] &= 0;
}

unsigned short BitField::getBit(int pos)
{
	//if (pos < 0 || pos >= BFLen) throw "Out of Bitfield range";
	int blockIndex = get_BlockIndex(pos);
	TELEM mask = get_BlockMask(pos % (blockSize*BYTE));
	if (Mem[blockIndex] & mask) return 1;
	return 0;
}

void BitField::load_bit(int pos)
{
	int blockIndex = get_BlockIndex(pos);
	TELEM mask = get_BlockMask(pos % (blockSize*BYTE));
	Mem[blockIndex] |= mask;
}
void BitField::unload_bit(int pos)
{
	int blockIndex = get_BlockIndex(pos);
	TELEM mask = get_BlockMask(pos % (blockSize*BYTE));
	Mem[blockIndex] &= (~mask);
}

size_t BitField::nonzero_count() const
{
	size_t counter{ 0 };					
	unsigned int blockCounter{ 0 };			
	TELEM buf = Mem[blockCounter];
	for (int i = 0; i < MemLen; ++i)
	{
		counter += (buf & 1);
		buf >>= 1;
		if (!( (i + 1 ) % bitsNum) )
		{
			buf = Mem[++blockCounter];
		}

	}
	return counter;
}


bool& BitField:: operator[](size_t idx)
{
	bool val = getBit(idx) == 1 ? true : false;
	return val;
}