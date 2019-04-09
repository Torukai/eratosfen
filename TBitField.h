#pragma once
#include <algorithm>

typedef unsigned int TELEM;
const size_t blockSize = sizeof(TELEM);
const size_t bitsNum = blockSize * 8;

class BitField
{
private:
	const size_t LenLimit{ 1048576 };// ���� ����� �������� ����
	TELEM *Mem; //��������� �� ������ ������ �������� ����
	size_t MemLen;// �-�� ��-��� ��� ��� ������������� ���.����
	size_t numOfBlocks;//���������� ������ ���� BFMult � ����

	TELEM BYTE = 8;
	TELEM GetMemMask() {
		TELEM IM = 1;
		for ( int i = 1; i < bitsNum; ++i )
			IM = ( IM << 1 ) | 1;
		return IM;
	}


	
	int get_BlockIndex( int n ); // ������ ��� ���� n 
	TELEM get_BlockMask( int bitShift );  // ������� ����� ��� ���� n


public:

	BitField( int length );			//����������� �� ���������
	BitField( const BitField & ); //����������� ����������� 
	void operator = ( const BitField &cpBF ); //
	bool& operator[]( size_t );
	size_t get_numOfBlocks() const;//���������� ���������� ������ � ����
	size_t size() const;//���������� ��������� ����
	void load_AllBits();//��������� ���� ����� ����
	void unload_AllBits();//��������� ���� ����� ����
	unsigned short getBit(int);//�������� ����
	void load_bit(int);//��������� ����
	void unload_bit(int);//��������� ���� �����
	size_t nonzero_count() const;//���������� ���� ��������� ����� ����
	~BitField();

};