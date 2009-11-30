#ifndef __PHYSICS_
#define __PHYSICS_



#include "Position3D.h"


#define WEIGHT_RATE			10
#define DEFAULT_WEIGHT		5

class Physics
{
public:
	int				physicsOpt;
	int				Weight;

	Position3D		Vel;
	Position3D		Accel;
	Position3D		SaveAccel;
	Position3D		GrVel;
	Position3D		GrAccel;
	Position3D		SaveGrAccel;
	Position3D		Move;

	//	저항측정
	Position3D		resistVal;
	Position3D		resistAccel;
//	Position3D		SaveMove;

//	Position3D		Movetotal;

	//--------------------------------------------------------------------------------------
	Physics()
	//--------------------------------------------------------------------------------------
	{
		Weight = DEFAULT_WEIGHT;
	}


	//--------------------------------------------------------------------------------------
	~Physics()
	//--------------------------------------------------------------------------------------
	{
	}


	//--------------------------------------------------------------------------------------
	Physics(int _Weight)
	//--------------------------------------------------------------------------------------
	{
		Weight = _Weight;
	}


	//--------------------------------------------------------------------------------------
	void initForce()
	//--------------------------------------------------------------------------------------
	{
		GrVel.Init();
		Vel.Init();
		Accel.Init();
//		Movetotal.Init();
		GrAccel.Init();

		resistVal.Init();
		resistAccel.Init();
//		SaveMove.Init();
	}


	//--------------------------------------------------------------------------------------
	Position3D process()
	//--------------------------------------------------------------------------------------
	{
		Move.Init();
	
		Vel = Vel + ((Accel*WEIGHT_RATE)/Weight);
		Accel.Init();
		Move = Move + Vel;

		GrVel = GrVel + GrAccel;
		Move = Move + GrVel;

		ResistProcess();

		return Move;
	}

	//--------------------------------------------------------------------------------------
	void setGrForce(Position3D _Force)
	//--------------------------------------------------------------------------------------
	{
		SaveGrAccel = GrAccel = _Force;
	}

	//--------------------------------------------------------------------------------------
	void setReForce(Position3D _Force)
	//--------------------------------------------------------------------------------------
	{
		resistVal.Init();
		resistAccel = _Force;
//		SaveMove = Move;
	}


	//--------------------------------------------------------------------------------------
	void setPhysicsOption(int opt)
	//--------------------------------------------------------------------------------------
	{
		physicsOpt |= opt;
	}


	//--------------------------------------------------------------------------------------
	void setForce(Position3D _Force)
	//--------------------------------------------------------------------------------------
	{
		SaveAccel = Accel = _Force;
	}

	//--------------------------------------------------------------------------------------
	void setRebound()
	//--------------------------------------------------------------------------------------
	{
		if(Move.z <= SaveGrAccel.z)	{Move.z = 0;}

		initForce();
		setGrForce(SaveGrAccel);
		Move.z *= (-1);
//		SaveMove = Move;
		setForce((Move*6)/5);

	}

	//--------------------------------------------------------------------------------------
	void resistGr()
	//--------------------------------------------------------------------------------------
	{
		GrVel = GrVel - GrAccel;
	}

	//--------------------------------------------------------------------------------------
	void ResistProcess()
	//--------------------------------------------------------------------------------------
	{
		resistVal = resistVal + resistAccel;
		
		if((0 > resistVal.x * Move.x) && (resistVal.x * resistVal.x) > (Move.x*Move.x))
		{
			Move.x = 0;
			Vel.x = 0;
			resistVal.x = 0;
			resistAccel.x = 0;
		}
		else
		{
			Move.x += resistVal.x;
		}

		if((0 > resistVal.y * Move.y) && (resistVal.y * resistVal.y) > (Move.y*Move.y))
		{
			Move.y = 0;
			Vel.y = 0;
			resistVal.y = 0;
			resistAccel.y = 0;
		}
		else
		{
			Move.y += resistVal.y;
		}

		if((0 > resistVal.z * Move.z) && (resistVal.z * resistVal.z) > (Move.z*Move.z))
		{
			Move.z = 0;
			Vel.z = 0;
			resistVal.z = 0;
			resistAccel.z = 0;
		}
		else
		{
			Move.z += resistVal.z;
		}
	}



	//--------------------------------------------------------------------------------------
	void destroy()
	//--------------------------------------------------------------------------------------
	{
	}
};


#endif