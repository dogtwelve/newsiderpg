#ifndef		_POSITION_3D_
#define		_POSITION_3D_

class Position3D
{
public:
	int x;
	int y;
	int z;

	Position3D();
	Position3D(int _x, int _y, int _z);
	Position3D operator+ (const Position3D&);
	Position3D operator- (const Position3D&);
	Position3D operator/ (const int&);
	Position3D operator* (const int&);

	void Init(int x = 0, int y = 0, int z = 0);
	int Sqr_Distance(Position3D&);
	int Sqr_Distance(int _x, int _y , int _z);
	int Sqr_GetLength();
};

#endif