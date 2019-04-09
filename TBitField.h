#pragma once
#include <algorithm>

typedef unsigned int TELEM;
const size_t blockSize = sizeof(TELEM);
const size_t bitsNum = blockSize * 8;

class BitField
{
private:
	const size_t LenLimit{ 1048576 };// Макс длина битового поля
	TELEM *Mem; //Указатель на массив блоков битового поля
	size_t MemLen;// к-во эл-тов Мем для представления бит.поля
	size_t numOfBlocks;//количество блоков типа BFMult в поле

	TELEM BYTE = 8;
	TELEM GetMemMask() {
		TELEM IM = 1;
		for ( int i = 1; i < bitsNum; ++i )
			IM = ( IM << 1 ) | 1;
		return IM;
	}


	
	int get_BlockIndex( int n ); // индекс для бита n 
	TELEM get_BlockMask( int bitShift );  // битовая маска для бита n


public:

	BitField( int length );			//Конструктор по умолчанию
	BitField( const BitField & ); //Конструктор копирования 
	void operator = ( const BitField &cpBF ); //
	bool& operator[]( size_t );
	size_t get_numOfBlocks() const;//Возвращает количество блоков в поле
	size_t size() const;//Количество элементов поля
	void load_AllBits();//Взведение всех битов поля
	void unload_AllBits();//Зануление всех битов поля
	unsigned short getBit(int);//Значение бита
	void load_bit(int);//взведение бита
	void unload_bit(int);//Зануление всех битов
	size_t nonzero_count() const;//Количество всех ненулевых битов поля
	~BitField();

};