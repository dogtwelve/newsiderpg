#include "Vector.h"

void Vector::removeAllElements()
{
	length = 0;
}

int Vector::size(){
	return length;
}

void* Vector::elementAt(int pos)
{
	return pnt[pos];
}
void Vector::insertElementAt(void* pt, int pos)
{
	if( pos>=length )
	{
		pnt[length] = pt;
	}else{
		for( int pp=length; pp>pos; pp-- )
		{
			pnt[pp] = pnt[pp-1];
		}
		pnt[pos] = pt;
	}
	length++;
}

void* Vector::firstElement()
{
	if( length > 0 ) return 0;
	return pnt[0];
}