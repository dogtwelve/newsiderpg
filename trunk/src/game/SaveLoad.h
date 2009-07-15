#ifndef __SAVELOAD_H_
#define __SAVELOAD_H_


#include "WIPIHeader.h"
#include "Device.h"



#define INIT_SAVELOAD()						(SaveLoad::GetInstance())

#define SAVELOAD_Slot						INIT_SAVELOAD()->Slot
#define SAVELOAD_sex						INIT_SAVELOAD()->sex
//#define SAVELOAD_MainStyle					INIT_SAVELOAD()->Style1
#define SAVELOAD_SubStyle					INIT_SAVELOAD()->Style2

#define SAVELOAD_HaveBeenVillage			INIT_SAVELOAD()->HaveBeenVillage

#define SAVELOAD_FreeInstance() 			INIT_SAVELOAD()->FreeInstance()


class SaveLoad	
{
public:
	int Slot;//���̺� ����
	int sex;//����
	int Style1;//���� ��Ÿ��
	int Style2;//���� ��Ÿ��
	
	bool HaveBeenVillage[12];	//	������ ���������� �ִ�.
	


private:
	SaveLoad();
	static SaveLoad* pSaveLoad;

public:
	~SaveLoad();
	static SaveLoad* GetInstance();
	void FreeInstance();

};


#endif