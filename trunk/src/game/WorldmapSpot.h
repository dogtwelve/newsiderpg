#define	MC_LEFT							(-1)
#define	MC_RIGHT							(1)

#define Sp_NAME			0
#define Sp_ID			1
#define Sp_X			2
#define Sp_Y			3
#define Set_PosX		4
#define Set_Dir			5


const short Town_1_Spot[4][6] = {//4�� ����
	//����, �ʵ�ID , X��ǥ , Y��ǥ
	{AREANAME_TOWN_0,801,-183,53	,50,MC_RIGHT},	/*���� Ÿ��*/		
	{AREANAME_FIELD_2,104,-171,12	,50,MC_RIGHT},	/*�̵�Ÿ�� ��*/		
	{AREANAME_FIELD_0,101,-218,66	,1950,MC_LEFT},	/*�ʿ�*/			
	{AREANAME_FIELD_1,200,-162,80	,50,MC_RIGHT}	/*���� ����*/		
};

const short Town_2_Spot[5][6] = {//5�� ����
	//����, �ʵ�ID , X��ǥ , Y��ǥ
	{AREANAME_TOWN_1,803,-161,-30	,50,MC_RIGHT},		/*�̵� Ÿ��*/		
	{AREANAME_FIELD_6,104,-171,12	,1450,MC_LEFT},		/*����Ÿ�� ��*/		
	{AREANAME_FIELD_3,105,-200,-31	,450,MC_LEFT},	/*���� ��*/			
	{AREANAME_FIELD_4,113,-121,-28	,50,MC_RIGHT},	/*���� ��*/		
	{AREANAME_FIELD_5,205,-151,-69	,50,MC_RIGHT}		/*�̷� ����*/		
};

#define House_X			0
#define House_Y			1
const short Town_All_Spot[12][2] = {//5�� ����
	//����, �ʵ�ID , X��ǥ , Y��ǥ
	{-183,53},		/*���� Ÿ��*/		
	{-161,-30},		/*�̵� Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30},		/*Ÿ��*/		
	{-161,-30}		/*Ÿ��*/	
};


