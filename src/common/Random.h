#ifndef RANDOM_H
#define RANDOM_H
class cGame;
class Random
{
	cGame *m_pGame;
	long m_Seed;
public:
	Random(cGame* pGame);
	Random(cGame* pGame,long lSeed);
	int		next(int bits);
	int		nextInt();
	int		nextInt(int n);
	void 	setSeed(long lSeed);
	long 	nextLong();
};
#endif