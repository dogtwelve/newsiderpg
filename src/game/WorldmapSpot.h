#define	MC_LEFT							(-1)
#define	MC_RIGHT							(1)

#define Sp_NAME			0
#define Sp_ID			1
#define Sp_X			2
#define Sp_Y			3
#define Set_PosX		4
#define Set_Dir			5


const short Town_1_Spot[4][6] = {//4개 지점
	//지명, 필드ID , X좌표 , Y좌표
	{AREANAME_TOWN_0,801,-183,53	,50,MC_RIGHT},	/*스몰 타운*/		
	{AREANAME_FIELD_2,104,-171,12	,50,MC_RIGHT},	/*미들타운 길*/		
	{AREANAME_FIELD_0,101,-218,66	,1950,MC_LEFT},	/*초원*/			
	{AREANAME_FIELD_1,200,-162,80	,50,MC_RIGHT}	/*수정 동굴*/		
};

const short Town_2_Spot[5][6] = {//5개 지점
	//지명, 필드ID , X좌표 , Y좌표
	{AREANAME_TOWN_1,803,-161,-30	,50,MC_RIGHT},		/*미들 타운*/		
	{AREANAME_FIELD_6,104,-171,12	,1450,MC_LEFT},		/*스몰타운 길*/		
	{AREANAME_FIELD_3,105,-200,-31	,450,MC_LEFT},	/*서쪽 숲*/			
	{AREANAME_FIELD_4,113,-121,-28	,50,MC_RIGHT},	/*동쪽 숲*/		
	{AREANAME_FIELD_5,205,-151,-69	,50,MC_RIGHT}		/*미로 동굴*/		
};

#define House_X			0
#define House_Y			1
const short Town_All_Spot[12][2] = {//5개 지점
	//지명, 필드ID , X좌표 , Y좌표
	{-183,53},		/*스몰 타운*/		
	{-161,-30},		/*미들 타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30},		/*타운*/		
	{-161,-30}		/*타운*/	
};


