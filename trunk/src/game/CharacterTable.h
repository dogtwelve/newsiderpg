
//돌격,			다운스케이팅,		드래곤헌팅,		하이크래시,		3연난무,		어기어검,		공간참격
//백다운피스톨,	스턴,			스핀샷,			힐링팩,			발칸샷,			3콤건컷터,		안드로메다
//쌍염탄,		스카이락,		아이스에로우.	토템,			뇌룡승천,		아이스드래곤,	블랙홀


const short s__ins_Skill[3*7][6] = {//스킬의 값이 할당대어 있다.
	//				Data0	스킬스프라이트		블랜딩넘버			케릭터스프라이트 ANI넘버				앞EFFECT						뒤EFFECT
	/*5연발샷*/		{ 0 ,SPRITE_WOMAN_S1 ,FRAME_WOMAN_S1_BLEND ,ANIM_WOMAN_BODY_A_S_SKILL1		,ANIM_WOMAN_S1_A_B_SKILL1_E	,-1},
	/*프로즌 샤워*/	{ 1 ,SPRITE_WOMAN_S2 ,FRAME_WOMAN_S2_BLEND ,ANIM_WOMAN_BODY_A_S_SKILL2		,ANIM_WOMAN_S2_A_B_SKILL2_E	,-1},
	/*바운딩 콤보*/	{ 2 ,SPRITE_WOMAN_S3 ,FRAME_WOMAN_S3_BLEND ,ANIM_WOMAN_BODY_A_S_SKILL3_1	,ANIM_WOMAN_S3_A_B_SKILL3_1_E,-1},
	/*공간참격*/	{ 3 ,SPRITE_WOMAN_S4 ,FRAME_WOMAN_S4_BLEND ,ANIM_WOMAN_BODY_A_S_SKILL4_1	,ANIM_WOMAN_S4_A_S_SKILL4_1_E,-1},
	/*돌격*/		{ 4 ,SPRITE_WOMAN_S5 ,FRAME_WOMAN_S5_BLEND ,ANIM_WOMAN_BODY_A_S_SKILL5		,ANIM_WOMAN_S5_A_S_SKILL5_E	,-1},
	/*드래곤헌팅*/	{ 5 ,SPRITE_WOMAN_S6 ,FRAME_WOMAN_S6_BLEND ,ANIM_WOMAN_BODY_A_S_SKILL6		,-1	,-1},
	/*3연난무*/		{ 6 ,SPRITE_WOMAN_S7 ,FRAME_WOMAN_S7_BLEND ,ANIM_WOMAN_BODY_A_S_SKILL7		,ANIM_WOMAN_S7_A_S_SKILL7_1	,-1},

	/*백다운피스톨*/{ 7 ,SPRITE_WOMAN_G1 ,FRAME_MAN_S1_BLEND ,ANIM_MAN_BODY_A_S_SKILL_1		,ANIM_MAN_S1_A_S_SKILL_1_E	,-1},
	/*스턴*/		{ 8 ,SPRITE_WOMAN_G2 ,FRAME_MAN_S2_BLEND ,ANIM_MAN_BODY_A_S_SKILL_2		,ANIM_MAN_S2_A_S_SKILL_2_E	,-1},
	/*스핀샷*/		{ 9 ,SPRITE_WOMAN_G3 ,FRAME_MAN_S3_BLEND ,ANIM_MAN_BODY_A_S_SKILL_3_1	,ANIM_MAN_S3_A_S_SKILL_3_1E	,-1},
	/*힐링팩*/		{10 ,SPRITE_WOMAN_G4 ,FRAME_MAN_S4_BLEND ,ANIM_MAN_BODY_A_S_SKILL_4_1	,ANIM_MAN_S4_A_S_SKILL_4_1_E	,-1},
	/*안드로메다*/	{11 ,SPRITE_WOMAN_G5 ,FRAME_MAN_S5_BLEND ,ANIM_MAN_BODY_A_S_SKILL_5		,ANIM_MAN_S5_A_S_SKILL_5_E	,-1},
	/*발칸샷*/		{12 ,SPRITE_WOMAN_G6 ,FRAME_MAN_S6_BLEND ,ANIM_MAN_BODY_A_S_SKILL_6_1	,ANIM_MAN_S6_A_S_SKILL_6_1_E	,-1},
	/*3콤건컷터*/	{13 ,SPRITE_WOMAN_G7 ,FRAME_MAN_S7_BLEND ,ANIM_MAN_BODY_A_S_SKILL_7		,ANIM_MAN_S7_A_S_SKILL_7_E	,-1},

	/*쌍염탄*/		{14 ,SPRITE_WOMAN_O1 ,FRAME_WOMAN_S_O1_BLEND ,ANIM_MAN_BODY_A_S_SKILL_7		,ANIM_WOMAN_S_O1_A_O_SKILL1_1_E	,-1},
	/*토템*/		{15 ,SPRITE_WOMAN_O2 ,FRAME_WOMAN_S_O2_BLEND ,ANIM_MAN_BODY_A_S_SKILL_7		,ANIM_WOMAN_S_O2_A_O_SKILL2_FUSE_E	,-1},
	/*스카이락*/	{16 ,SPRITE_WOMAN_O3 ,FRAME_WOMAN_S_O3_BLEND ,ANIM_MAN_BODY_A_S_SKILL_7		,ANIM_WOMAN_S_O3_A_O_SKILL3_1_E	,ANIM_WOMAN_S_O3_A_O_SKILL3_1_E_BACK},
	/*아이스드래곤*/{17 ,SPRITE_WOMAN_O4 ,FRAME_WOMAN_S_O4_BLEND ,ANIM_MAN_BODY_A_S_SKILL_7		,ANIM_WOMAN_S_O4_A_O_SKILL4_E	,-1},
	/*블랙홀*/		{18 ,SPRITE_WOMAN_O5 ,FRAME_WOMAN_S_O5_BLEND ,ANIM_MAN_BODY_A_S_SKILL_7		,ANIM_WOMAN_S_O5_A_O_SKILL5_E	,ANIM_WOMAN_S_O5_A_O_SKILL5_EBACK},
	/*뇌룡승천*/	{19 ,SPRITE_WOMAN_O6 ,FRAME_WOMAN_S_O6_BLEND ,ANIM_MAN_BODY_A_S_SKILL_7		,ANIM_WOMAN_S_O6_A_O_SKILL6_E	,-1},
	/*아이스에로우*/{20 ,SPRITE_WOMAN_O7 ,FRAME_WOMAN_S_O7_BLEND ,ANIM_MAN_BODY_A_S_SKILL_7		,ANIM_WOMAN_S_O7_A_O_SKILL7_1_E	,-1}
};

static const short a_Skill_Table[3*7*10][7] = {
	//,검사 스킬 데미지 공식 : ATT+N,//////////////////////////////////////////////////////////,,,,,,,
	//,Skill Lv,"	Attack1","	Attack2","	CoolTime(frame)","	Combo","	Mana","	Need_Point","	Need_Level",
	//,이기어검,지속시간 20초,,,,
	/*,1,*/{80,0,300,100,103,6,40},
	/*,2,*/{90,0,300,100,108,6,40},
	/*,3,*/{100,0,300,100,113,6,40},
	/*,4,*/{110,0,300,100,118,6,40},
	/*,5,*/{120,0,300,100,123,6,40},
	/*,6,*/{130,0,300,100,128,7,50},
	/*,7,*/{140,0,300,100,148,7,50},
	/*,8,*/{150,0,300,100,168,7,50},
	/*,9,*/{160,0,300,100,188,7,50},
	/*,10,*/{180,0,300,100,208,8,50},
	//,다운스케이팅,,,,,
	/*,1,*/{110,140,50,100,20,2,5},
	/*,2,*/{115,150,50,100,25,2,5},
	/*,3,*/{120,160,60,100,30,2,5},
	/*,4,*/{125,170,60,100,35,2,5},
	/*,5,*/{130,180,70,100,40,2,5},
	/*,6,*/{135,190,70,100,45,3,15},
	/*,7,*/{140,200,80,100,57,3,15},
	/*,8,*/{145,210,80,100,69,3,15},
	/*,9,*/{150,220,90,100,81,3,15},
	/*,10,*/{155,240,90,100,93,4,15},
	//,하이크래시,,,,,
	/*,1,*/{150,0,100,100,70,4,25},
	/*,2,*/{170,0,100,100,75,4,25},
	/*,3,*/{190,0,110,100,80,4,25},
	/*,4,*/{210,0,110,100,85,4,25},
	/*,5,*/{230,0,120,100,90,4,25},
	/*,6,*/{250,0,120,100,95,5,35},
	/*,7,*/{270,0,130,100,100,5,35},
	/*,8,*/{290,0,140,100,115,5,35},
	/*,9,*/{310,0,150,100,130,5,35},
	/*,10,*/{350,0,160,100,145,6,35},
	//,공간참격,,,,,
	/*,1,*/{150,300,600,100,128,7,50},
	/*,2,*/{170,330,630,100,133,7,50},
	/*,3,*/{190,360,660,100,138,7,50},
	/*,4,*/{210,390,690,100,143,7,50},
	/*,5,*/{230,420,720,100,148,7,50},
	/*,6,*/{250,450,750,100,153,8,55},
	/*,7,*/{270,480,780,100,178,8,55},
	/*,8,*/{290,520,810,100,203,8,55},
	/*,9,*/{310,550,840,100,228,8,55},
	/*,10,*/{330,580,870,100,233,9,55},
	//,돌격,,,,,
	/*,1,*/{140,0,30,100,6,1,1},
	/*,2,*/{150,0,30,100,11,1,1},
	/*,3,*/{160,0,40,100,16,1,1},
	/*,4,*/{170,0,40,100,21,1,1},
	/*,5,*/{180,0,50,100,26,1,1},
	/*,6,*/{190,0,50,100,31,2,10},
	/*,7,*/{200,0,60,100,41,2,10},
	/*,8,*/{210,0,60,100,51,3,10},
	/*,9,*/{220,0,70,100,61,3,10},
	/*,10,*/{240,0,70,100,71,4,10},
	//,드래곤헌팅,,,,,
	/*,1,*/{150,0,70,100,45,3,15},
	/*,2,*/{160,0,70,100,50,3,15},
	/*,3,*/{170,0,70,100,55,3,15},
	/*,4,*/{180,0,70,100,60,3,15},
	/*,5,*/{190,0,70,100,65,3,15},
	/*,6,*/{200,0,80,100,70,4,25},
	/*,7,*/{210,0,80,100,83,4,25},
	/*,8,*/{220,0,80,100,96,4,25},
	/*,9,*/{220,0,80,100,109,4,25},
	/*,10,*/{240,0,80,100,122,5,25},
	//,3연난무,각타간 쿨타임 없음,,,,
	/*,1,*/{110,220,200,100,35,5,35},
	/*,2,*/{115,240,210,100,36,5,35},
	/*,3,*/{120,260,220,100,37,5,35},
	/*,4,*/{125,280,230,100,38,5,35},
	/*,5,*/{130,300,240,100,39,5,35},
	/*,6,*/{135,320,250,100,40,6,45},
	/*,7,*/{140,340,260,100,47,6,45},
	/*,8,*/{145,360,270,100,54,6,45},
	/*,9,*/{150,380,280,100,61,6,45},
	/*,10,*/{155,400,290,100,68,7,45},
	//,건너 스킬 데미지 공식 : ATT+N,///////////////////////////////////////////////////////////////,,,,
	//,백다운피스톨,,,,,
	/*,1,*/{80,110,30,0,4,1,0},
	/*,2,*/{85,115,30,0,7,1,0},
	/*,3,*/{90,120,30,0,9,1,0},
	/*,4,*/{95,125,30,0,12,1,0},
	/*,5,*/{100,130,40,0,14,1,0},
	/*,6,*/{110,135,40,0,16,2,10},
	/*,7,*/{115,140,50,0,22,2,10},
	/*,8,*/{120,145,50,0,27,3,10},
	/*,9,*/{125,150,60,0,32,3,10},
	/*,10,*/{130,155,60,0,37,4,10},
	//,스턴,,,,,
	/*,1,*/{90,0,30,0,11,2,5},
	/*,2,*/{95,0,30,0,18,2,5},
	/*,3,*/{100,0,40,0,16,2,5},
	/*,4,*/{105,0,40,0,18,2,5},
	/*,5,*/{110,0,50,0,21,2,5},
	/*,6,*/{115,0,50,0,23,3,15},
	/*,7,*/{120,0,60,0,25,3,15},
	/*,8,*/{125,0,60,0,35,3,15},
	/*,9,*/{130,0,70,0,42,3,15},
	/*,10,*/{140,0,70,0,48,4,15},
	//,스핀샷,,,,,
	/*,1,*/{100,0,50,0,23,3,15},
	/*,2,*/{105,0,50,0,26,3,15},
	/*,3,*/{110,0,50,0,28,3,15},
	/*,4,*/{115,0,50,0,31,3,15},
	/*,5,*/{120,0,50,0,33,3,15},
	/*,6,*/{125,0,60,0,36,4,25},
	/*,7,*/{130,0,60,0,42,4,25},
	/*,8,*/{135,0,60,0,49,4,25},
	/*,9,*/{140,0,60,0,55,4,25},
	/*,10,*/{150,0,70,0,62,5,25},
	//,힐링팩,,,,,
	/*,1,*/{10,0,100,0,56,4,25},
	/*,2,*/{15,0,100,0,58,4,25},
	/*,3,*/{20,0,110,0,61,4,25},
	/*,4,*/{25,0,110,0,63,4,25},
	/*,5,*/{30,0,120,0,66,4,25},
	/*,6,*/{35,0,120,0,68,5,35},
	/*,7,*/{40,0,130,0,71,5,35},
	/*,8,*/{45,0,140,0,78,5,35},
	/*,9,*/{50,0,150,0,86,5,35},
	/*,10,*/{55,0,160,0,93,6,35},
	//,안드로메다,,,,,
	/*,1,*/{200,0,300,0,66,7,50},
	/*,2,*/{210,0,320,0,69,7,50},
	/*,3,*/{220,0,340,0,71,7,50},
	/*,4,*/{230,0,360,0,74,7,50},
	/*,5,*/{240,0,380,0,76,7,50},
	/*,6,*/{250,0,400,0,79,8,55},
	/*,7,*/{260,0,420,0,91,8,55},
	/*,8,*/{270,0,440,0,104,8,55},
	/*,9,*/{280,0,460,0,116,8,55},
	/*,10,*/{290,0,480,0,119,9,55},
	//,발칸샷,각타간 쿨타임 없음,,,,
	/*,1,*/{110,0,150,0,35,5,35},
	/*,2,*/{115,0,160,0,36,5,35},
	/*,3,*/{120,0,170,0,37,5,35},
	/*,4,*/{125,0,180,0,38,5,35},
	/*,5,*/{130,0,190,0,39,5,35},
	/*,6,*/{135,0,200,0,40,6,45},
	/*,7,*/{140,0,210,0,47,6,45},
	/*,8,*/{145,0,220,0,54,6,45},
	/*,9,*/{150,0,230,0,61,6,45},
	/*,10,*/{155,0,240,0,68,7,45},
	//,3콤 건컷터,,,,,
	/*,1,*/{80,0,250,0,52,6,40},
	/*,2,*/{90,0,260,0,55,6,40},
	/*,3,*/{100,0,270,0,57,6,40},
	/*,4,*/{110,0,280,0,60,6,40},
	/*,5,*/{120,0,290,0,63,6,40},
	/*,6,*/{130,0,300,0,65,7,50},
	/*,7,*/{140,0,310,0,75,7,50},
	/*,8,*/{150,0,320,0,85,7,50},
	/*,9,*/{160,0,330,0,95,7,50},
	/*,10,*/{180,0,340,0,105,8,50},
	//,매직 스킬 데미지 공식 : ATT+N,///////////////////////////////////////////////////////////////,0,,,
	//,쌍염탄,,,,,
	/*,1,*/{140,0,15,100,15,1,0},
	/*,2,*/{150,0,15,100,25,1,0},
	/*,3,*/{160,0,15,100,35,1,0},
	/*,4,*/{170,0,15,100,45,1,0},
	/*,5,*/{180,0,15,100,55,1,0},
	/*,6,*/{190,0,20,100,65,2,10},
	/*,7,*/{200,0,20,100,85,2,10},
	/*,8,*/{210,0,20,100,105,3,10},
	/*,9,*/{220,0,20,100,125,3,10},
	/*,10,*/{240,0,20,100,145,4,10},
	//,화염,냉기 토템,토템지속시간 20초,,,,
	/*,1,*/{160,1,200,100,143,4,25},
	/*,2,*/{190,2,220,100,153,4,25},
	/*,3,*/{220,3,240,100,163,4,25},
	/*,4,*/{250,4,260,100,173,4,25},
	/*,5,*/{280,5,280,100,183,4,25},
	/*,6,*/{310,6,300,100,193,5,35},
	/*,7,*/{340,7,320,100,203,5,35},
	/*,8,*/{370,8,330,100,233,5,35},
	/*,9,*/{400,9,350,100,263,5,35},
	/*,10,*/{430,10,370,100,293,6,35},
	//,스카이락,,,,,
	/*,1,*/{160,0,80,100,43,2,5},
	/*,2,*/{175,0,80,100,53,2,5},
	/*,3,*/{190,0,80,100,63,2,5},
	/*,4,*/{205,0,80,100,73,2,5},
	/*,5,*/{220,0,90,100,83,2,5},
	/*,6,*/{235,0,90,100,93,3,15},
	/*,7,*/{250,0,90,100,117,3,15},
	/*,8,*/{265,0,90,100,141,3,15},
	/*,9,*/{280,0,100,100,165,3,15},
	/*,10,*/{295,0,110,100,189,4,15},
	//,아이스드래곤,,,,,
	/*,1,*/{160,320,160,320,209,6,40},
	/*,2,*/{170,340,170,340,219,6,40},
	/*,3,*/{180,360,180,360,229,6,40},
	/*,4,*/{190,380,190,380,239,6,40},
	/*,5,*/{200,400,200,400,249,6,40},
	/*,6,*/{210,420,210,420,259,7,50},
	/*,7,*/{220,440,220,440,299,7,50},
	/*,8,*/{230,460,230,460,339,7,50},
	/*,9,*/{240,480,240,480,379,7,50},
	/*,10,*/{250,500,250,500,419,8,50},
	//,블랙홀,,,,,
	/*,1,*/{400,0,600,100,259,7,50},
	/*,2,*/{450,0,630,100,269,7,50},
	/*,3,*/{500,0,660,100,279,7,50},
	/*,4,*/{550,0,690,100,289,7,50},
	/*,5,*/{600,0,720,100,299,7,50},
	/*,6,*/{650,0,750,100,309,8,55},
	/*,7,*/{700,0,780,100,359,8,55},
	/*,8,*/{750,0,810,100,409,8,55},
	/*,9,*/{800,0,840,100,459,8,55},
	/*,10,*/{850,0,870,100,469,9,55},
	//,뇌룡승천,,,,,
	/*,1,*/{400,0,250,100,178,5,35},
	/*,2,*/{430,0,270,100,183,5,35},
	/*,3,*/{460,0,290,100,188,5,35},
	/*,4,*/{490,0,310,100,193,5,35},
	/*,5,*/{520,0,330,100,198,5,35},
	/*,6,*/{550,0,350,100,203,6,45},
	/*,7,*/{580,0,370,100,238,6,45},
	/*,8,*/{610,0,390,100,273,6,45},
	/*,9,*/{640,0,410,100,308,6,45},
	/*,10,*/{670,0,430,100,343,7,45},
	//,아이스에로우,,,,,
	/*,1,*/{200,0,90,100,93,3,15},
	/*,2,*/{220,0,90,100,103,3,15},
	/*,3,*/{240,0,90,100,113,3,15},
	/*,4,*/{280,0,90,100,123,3,15},
	/*,5,*/{300,0,90,100,133,3,15},
	/*,6,*/{320,0,100,100,143,4,25},
	/*,7,*/{340,0,100,100,169,4,25},
	/*,8,*/{360,0,100,100,195,4,25},
	/*,9,*/{380,0,100,100,221,4,25},
	/*,10,*/{400,0,100,100,247,5,25}
};



static const short a_Passive_Table[4*7*5][3] = {
	//,검사 스킬 데미지 공식 : ATT+N,//////////////////////////////////////////////////////////,,,,,,,
	//,Skill Lv,"	Attack1","	Attack2","	CoolTime(frame)","	Combo","	Mana","	Need_Point","	Need_Level",
	//,소드 마스터리 Sword Master,,,Sword ATT +
	/*,1,*/{10,2,20},
	/*,2,*/{15,2,20},
	/*,3,*/{20,3,30},
	/*,4,*/{25,3,30},
	/*,5,*/{30,4,30},
	//,생명증가 HP UP,,,,HP+
	/*,1,*/{100,1,10},
	/*,2,*/{200,1,10},
	/*,3,*/{300,2,21},
	/*,4,*/{400,2,21},
	/*,5,*/{500,3,21},
	//,극한의 저력 The power of extreme,,,(HP20% 이하일경우) ATT + 
	/*,1,*/{30,3,30},
	/*,2,*/{35,3,30},
	/*,3,*/{40,4,40},
	/*,4,*/{45,4,40},
	/*,5,*/{50,5,40},
	//,철벽 Strong wall,,,(2% 확률로 데미지 -50%)
	/*,1,*/{2,4,40},
	/*,2,*/{6,4,40},
	/*,3,*/{12,5,45},
	/*,4,*/{18,5,45},
	/*,5,*/{25,6,45},
	//,맹독 수련 Deadly poison training,,,(기본타시 2% 확률로 독에 걸린다)
	/*,1,*/{2,3,30},
	/*,2,*/{4,3,30},
	/*,3,*/{6,3,30},
	/*,4,*/{8,4,30},
	/*,5,*/{10,5,40},
	//,5연발샷 강화,,,이기어검 공격력 강화 + 10% 
	/*,1,*/{10,3,50},
	/*,2,*/{20,3,50},
	/*,3,*/{30,3,50},
	/*,4,*/{40,4,50},
	/*,5,*/{50,5,60},
	//,참격수련,,,공간참격 크리율 + 10% 상승
	/*,1,*/{10,3,50},
	/*,2,*/{20,3,50},
	/*,3,*/{30,3,50},
	/*,4,*/{40,4,50},
	/*,5,*/{50,5,60},
	//,건너 스킬 데미지 공식 : ATT+N,///////////////////////////////////////////////////////////////,,,,
	//,건 마스터리 Gun Master,,,
	/*,1,*/{5,1,10 },
	/*,2,*/{7,1,10 },
	/*,3,*/{9,2,21 },
	/*,4,*/{11,2,21},
	/*,5,*/{13,3,21},
	//,치명타 훈련 Critical training,,,
	/*,1,*/{7,2,20 },
	/*,2,*/{10,2,20},
	/*,3,*/{13,3,30},
	/*,4,*/{16,3,30},
	/*,5,*/{20,4,30},
	//,고난도 회피 숙련 Great dodge ,,,
	/*,1,*/{30,3,30},
	/*,2,*/{35,3,30},
	/*,3,*/{40,4,35},
	/*,4,*/{45,4,35},
	/*,5,*/{50,5,35},
	//,에너지 게이트 Energy gate,,,MP up + 2%
	/*,1,*/{2,4,40},
	/*,2,*/{3,4,40},
	/*,3,*/{4,5,45},
	/*,4,*/{5,5,45},
	/*,5,*/{6,6,45},
	//,감정술 appraisal,,,LV1의 아이템을 감정 할 수 있다.
	/*,1,*/{1,3,30},
	/*,2,*/{2,3,30},
	/*,3,*/{3,3,30},
	/*,4,*/{4,4,30},
	/*,5,*/{5,5,40},
	//,스턴샷 강화,,,스턴샷 스턴 0.5초 상승
	/*,1,*/{5,2,15 },
	/*,2,*/{10,2,15},
	/*,3,*/{15,3,20},
	/*,4,*/{20,3,20},
	/*,5,*/{30,3,20},
	//,힐링팩 부스터,,,힐링 + 4% 상승 마나소모 10% 상승
	/*,1,*/{4,3,30 },
	/*,2,*/{8,3,30 },
	/*,3,*/{12,4,40},
	/*,4,*/{16,4,40},
	/*,5,*/{20,5,40},
	//,매직 스킬 데미지 공식 : ATT+N,///////////////////////////////////////////////////////////////,0,,,
	//,매직 마스터리,,,법사 ATT+ 5%
	/*,1,*/{5,1,10},
	/*,2,*/{10,1,10},
	/*,3,*/{15,2,21},
	/*,4,*/{20,2,21},
	/*,5,*/{25,3,21},
	//,상성강화,,,상성공격에 의한 피해를 2% 증가 시킨다.
	/*,1,*/{2,2,20},
	/*,2,*/{4,2,20},
	/*,3,*/{6,4,40},
	/*,4,*/{8,4,40},
	/*,5,*/{10,5,40},
	//,회복증대,,,HP/MP increase up + 5%
	/*,1,*/{5,2,20},
	/*,2,*/{10,2,20},
	/*,3,*/{15,3,30},
	/*,4,*/{20,3,30},
	/*,5,*/{25,4,30},
	//,기술 수련,,,Over 10 Sec Cooltime down 1Sec
	/*,1,*/{10,3,30},
	/*,2,*/{20,3,30},
	/*,3,*/{30,4,35},
	/*,4,*/{40,4,35},
	/*,5,*/{50,5,35},
	//,눈부신성장,,,레벨업시 2% 의 확률로 추가 능력치가 상승한다
	/*,1,*/{2 ,4,40},
	/*,2,*/{4 ,4,40},
	/*,3,*/{6 ,5,45},
	/*,4,*/{8 ,5,45},
	/*,5,*/{10,6,45},
	//,고대어 습득,,,1 LV 고대어를 해석할수있다
	/*,1,*/{1,3,30},
	/*,2,*/{2,3,30},
	/*,3,*/{3,3,30},
	/*,4,*/{4,4,30},
	/*,5,*/{5,5,40},
	//,냉기 훈련,얼음화살 아이스 빙룡 소환의 동결 지속시간을 늘린다.,,
	/*,1,*/{5,2,20},
	/*,2,*/{10,2,20},
	/*,3,*/{15,4,40},
	/*,4,*/{20,4,40},
	/*,5,*/{25,5,40},
	//커맨드 패시브 스킬///////////////////////////////////////////////////////////////,0,,,
	//,잡기                                 catch	
	/*,1,*/{1,2,5},							
	/*,2,*/{1,2,5},							
	/*,3,*/{1,2,5},							
	/*,4,*/{1,2,5},							
	/*,5,*/{1,2,5},							
	//,라인이동								lineMove	
	/*,1,*/{1,5,10},							
	/*,2,*/{1,5,10},							
	/*,3,*/{1,5,10},							
	/*,4,*/{1,5,10},							
	/*,5,*/{1,5,10},	
	//,대시어택								dashAtt
	/*,1,*/{1,2,5},
	/*,2,*/{1,2,5},
	/*,3,*/{1,2,5},
	/*,4,*/{1,2,5},
	/*,5,*/{1,2,5},
	//,가드 SSSSSSSSSSSSSSSSSSSSSSSS		guard	
	/*,1,*/{1,3,10},							
	/*,2,*/{1,3,10},							
	/*,3,*/{1,3,10},							
	/*,4,*/{1,3,10},							
	/*,5,*/{1,3,10},							
	//,마나충전 OOOOOOOOOOOOOOOOOOOO		manaCharge	
	/*,1,*/{1,3,10},							
	/*,2,*/{1,3,10},							
	/*,3,*/{1,3,10},							
	/*,4,*/{1,3,10},							
	/*,5,*/{1,3,10},							
	//,차지어택 GGGGGGGGGGGGGGGGGGGG		chargeShot
	/*,1,*/{1,3,10},							
	/*,2,*/{1,3,10},							
	/*,3,*/{1,3,10},							
	/*,4,*/{1,3,10},							
	/*,5,*/{1,3,10}							
	
};
































