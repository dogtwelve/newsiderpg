#include "Random.h"
#include "cgame.h"

Random::Random(cGame* pGame)
{
	m_pGame = pGame;
	m_Seed = GETTIMEMS();
}
Random::Random(cGame* pGame,long lSeed)
{
	m_pGame = pGame;
	setSeed(lSeed);
}
int Random::next(int bits)
{
	   m_Seed = (m_Seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
       return (int)(m_Seed >> (48 - bits));
}
int Random::nextInt()
{return next(32);}
int Random::nextInt(int n)
{     if (n<=0)
		return -1;

     if ((n & -n) == n)  // i.e., n is a power of 2
         return (int)((n * (long)next(31)) >> 31);

     int bits, val;
     do {
         bits = next(31);
         val = bits % n;
     } while(bits - val + (n-1) < 0);
     return val;
}
long Random::nextLong()
{
	return ((long)next(32) << 32) + next(32);
}
void Random::setSeed(long lSeed)
{
	m_Seed = (lSeed ^ 0x5DEECE66DL) & ((1L << 48) - 1);
}