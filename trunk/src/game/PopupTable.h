//	장비 정의
#define E_A_SWORD		0
#define E_A_AXE			1
#define E_A_GUN			2
#define E_A_ORB			3
#define E_D_HEAD		4
#define E_D_CHEST		5
#define E_D_LEG			6
#define E_D_GLOVES		7
#define E_D_NECKLACE	8
#define E_D_RING		9

//	드랍되는 아이템의 등급
#define DG_NORMAL		0
#define DG_MAGIC		1
#define DG_RARE			2
#define DG_UNIQUE		3
#define DG_SPECIAL		4

//	드랍되는 아이템의 성별
#define DS_MAN			0
#define DS_WOMAN		1
#define DG_UNISEX		2

//	드랍되는 아이템의 감정상태
#define DJ_NORMAL		0
#define DJ_HIDDEN		1

//	드랍되는 아이템의 타입
#define DT_EQUIP			0
#define DT_SPEND			1
#define DT_MONEY			2
#define DT_SCROLL			3
#define DT_QUEST00_BOMB		4
#define DT_QUEST00_MEDAL	5


#define C_T_SW			0
#define C_T_AX			1
#define C_T_GU			2
#define C_T_OR			3
#define C_T_HE			4
#define C_T_CH			5
#define C_T_LE			6
#define C_T_GL			7

static const short costume_Table[25][8]={//코스튬 넘버 지정
	{	00,	00,	00,	00,	0,	1,	2,	3	},
	{	10,	10,	10,	10,	0,	2,	1,	3	},
	{	20,	20,	20,	20,	1,	1,	2,	2	},
	{	30,	30,	30,	30,	2,	3,	1,	3	},
	{	40,	40,	40,	40,	3,	4,	3,	1	},
	{	01,	01,	50,	50,	2,	0,	0,	0	},
	{	11,	11,	60,	60,	0,	2,	4,	2	},
	{	21,	21,	70,	70,	1,	3,	0,	1	},
	{	31,	31,	80,	80,	3,	0,	3,	2	},
	{	41,	41,	90,	90,	4,	2,	1,	4	},
	{	00,	00,	01,	01,	2,	4,	0,	0	},
	{	10,	10,	11,	11,	1,	1,	1,	1	},
	{	20,	20,	21,	21,	2,	1,	0,	0	},
	{	30,	30,	31,	31,	3,	2,	4,	2	},
	{	40,	40,	41,	41,	4,	1,	2,	4	},
	{	01,	01,	51,	51,	3,	4,	0,	0	},
	{	11,	11,	61,	61,	0,	3,	3,	3	},
	{	21,	21,	71,	71,	1,	2,	2,	1	},
	{	31,	31,	81,	81,	4,	3,	4,	2	},
	{	41,	41,	91,	91,	3,	1,	0,	4	},
	{	00,	00,	51,	51,	0,	4,	3,	3	},
	{	10,	10,	80,	80,	1,	1,	1,	1	},
	{	20,	20,	91,	91,	2,	2,	2,	2	},
	{	30,	30,	81,	81,	4,	3,	3,	0	},
	{	40,	40,	90,	90,	0,	4,	4,	4	}
};

#define E_T_LV			0
#define E_T_SW_MIN		1
#define E_T_SW_MAX		2
#define E_T_AX_MIN		3
#define E_T_AX_MAX		4
#define E_T_GU_MIN		5
#define E_T_GU_MAX		6
#define E_T_OR_MIN		7
#define E_T_OR_MAX		8
#define E_T_HE			9
#define E_T_CH			10
#define E_T_LE			11
#define E_T_GL			12
static const short equip_Table[25][13]={
	{	1	,	2, 7	,	2,13	,	7,18	,	2,13	,	15	,	17	,	9	,	7	},
	{	5	,	10,13	,	6,19	,	11,24	,	6,19	,	20	,	22	,	11	,	9	},
	{	12	,	20,25	,	17,30	,	22,35	,	8,21	,	25	,	27	,	14	,	12	},
	{	15	,	23,27	,	19,35	,	24,40	,	10,23	,	30	,	32	,	16	,	14	},
	{	20	,	30,35	,	23,40	,	28,45	,	12,25	,	35	,	37	,	19	,	17	},
	{	25	,	33,38	,	26,45	,	31,50	,	14,27	,	40	,	42	,	21	,	19	},
	{	32	,	41,46	,	30,50	,	35,55	,	16,29	,	45	,	47	,	24	,	22	},
	{	35	,	45,50	,	33,57	,	38,62	,	18,31	,	50	,	52	,	26	,	24	},
	{	40	,	51,57	,	39,65	,	44,70	,	20,33	,	55	,	57	,	29	,	27	},
	{	46	,	62,68	,	43,72	,	48,77	,	22,35	,	60	,	62	,	31	,	29	},
	{	53	,	70,76	,	48,83	,	53,88	,	24,37	,	65	,	67	,	34	,	32	},
	{	57	,	75,81	,	55,95	,	60,100	,	26,39	,	70	,	72	,	36	,	34	},
	{	60	,	80,86	,	60,103	,	65,120	,	28,41	,	75	,	77	,	47	,	45	},
	{	65	,	84,92	,	64,115	,	69,130	,	30,43	,	80	,	82	,	51	,	49	},
	{	67	,	88,96	,	67,120	,	72,138	,	32,45	,	85	,	87	,	57	,	55	},
	{	72	,	92,100	,	70,125	,	78,145	,	34,47	,	90	,	92	,	60	,	58	},
	{	75	,	96,105	,	74,130	,	82,152	,	36,49	,	95	,	97	,	64	,	62	},
	{	78	,	100,110	,	77,135	,	88,160	,	38,51	,	100	,	102	,	71	,	69	},
	{	82	,	105,120	,	80,140	,	95,169	,	40,53	,	105	,	107	,	76	,	74	},
	{	85	,	110,125	,	83,145	,	100,178	,	42,55	,	110	,	112	,	81	,	79	},
	{	88	,	115,130	,	87,150	,	105,186	,	45,57	,	115	,	117	,	86	,	84	},
	{	91	,	120,135	,	90,155	,	110,198	,	47,59	,	120	,	122	,	91	,	89	},
	{	94	,	130,137	,	96,175	,	120,210	,	49,61	,	125	,	127	,	97	,	95	},
	{	97	,	150,160	,	103,207	,	125,220	,	51,62	,	130	,	132	,	102	,	100	},
	{	100	,	170,180	,	110,220	,	135,240	,	55,70	,	135	,	137	,	107	,	105	}
};

#define D_T_LV			0
#define D_T_NE_DE		1
#define D_T_RI_AT		2
#define D_T_RI_DE		3
static const short deco_Table[25][4]={
	{	1	,	5	,	1	,	3	},
	{	5	,	7	,	0	,	5	},
	{	12	,	9	,	0	,	7	},
	{	15	,	11	,	1	,	9	},
	{	20	,	13	,	2	,	11	},
	{	25	,	15	,	0	,	13	},
	{	32	,	17	,	0	,	20	},
	{	35	,	19	,	2	,	15	},
	{	40	,	21	,	7	,	0	},
	{	46	,	23	,	0	,	30	},
	{	48	,	25	,	5	,	10	},
	{	52	,	27	,	0	,	35	},
	{	53	,	29	,	10	,	20	},
	{	55	,	31	,	12	,	5	},
	{	59	,	33	,	20	,	-20	},
	{	60	,	35	,	0	,	40	},
	{	62	,	37	,	15	,	0	},
	{	65	,	39	,	0	,	37	},
	{	67	,	41	,	17	,	5	},
	{	70	,	43	,	15	,	30	},
	{	75	,	45	,	0	,	30	},
	{	80	,	47	,	10	,	0	},
	{	83	,	49	,	7	,	15	},
	{	87	,	51	,	15	,	35	},
	{	90	,	53	,	30	,	0	}
};

#define H_T_W_ATT			0
#define H_T_W_CRI			1
#define H_T_W_AGI			2
#define H_T_W_HP			3
#define H_T_W_MP			4
#define H_T_A_DEF			5
#define H_T_A_CRI			6
#define H_T_A_AGI			7
#define H_T_A_HP			8
#define H_T_A_MP			9
#define H_T_COSUME				10
static const short head_Table[8][11]={
	{	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0,	0},//null 접두사
	{	10	,	0	,	1	,	0	,	0	,	10	,	0	,	1	,	0	,	0,	2},
	{	30	,	2	,	0	,	0	,	0	,	-60	,	2	,	2	,	0	,	0,	4},
	{	20	,	0	,	0	,	10	,	0	,	20	,	0	,	0	,	3	,	0,	4},
	{	30	,	0	,	0	,	0	,	2	,	30	,	0	,	0	,	0	,	2,	3},
	{	-40	,	0	,	0	,	20	,	0	,	-40	,	1	,	1	,	2	,	0,	0},
	{	60	,	0	,	0	,	-20	,	-10	,	70	,	-1	,	-1	,	0	,	0,	2},
	{	-10	,	0	,	0	,	0	,	5	,	-20	,	0	,	0	,	0	,	2,	1}
};


#define G_T_E_DDANG			0
#define G_T_E_MUL			1
#define G_T_E_BUL			2
#define G_T_E_BARAM			3
#define G_T_A_CON			4
#define G_T_A_INT			5
#define G_T_A_STR			6
#define G_T_A_DEX			7
static const short gem_Table[19][8]={
	{	1	,	0	,	0	,	0	,	3	,	0	,	0	,	0	},//null 접두사
	{	2	,	0	,	0	,	0	,	5	,	0	,	0	,	0	},
	{	3	,	-1	,	0	,	0	,	15	,	0	,	0	,	0	},
	{	0	,	1	,	0	,	0	,	0	,	3	,	0	,	0	},
	{	0	,	2	,	0	,	0	,	0	,	5	,	0	,	0	},
	{	0	,	3	,	-1	,	0	,	0	,	10	,	0	,	0	},
	{	0	,	0	,	1	,	0	,	0	,	0	,	3	,	0	},
	{	0	,	0	,	2	,	0	,	0	,	0	,	5	,	0	},
	{	0	,	0	,	3	,	-1	,	0	,	0	,	15	,	0	},
	{	0	,	0	,	0	,	1	,	0	,	0	,	0	,	3	},
	{	0	,	0	,	0	,	2	,	0	,	0	,	0	,	5	},
	{	-1	,	0	,	0	,	3	,	0	,	0	,	0	,	15	},

	{	5	,	-2	,	0	,	0	,	0	,	0	,	0	,	0	},
	{	0	,	5	,	-2	,	0	,	0	,	0	,	0	,	0	},
	{	0	,	0	,	5	,	-2	,	0	,	0	,	0	,	0	},
	{	-2	,	0	,	0	,	5	,	0	,	0	,	0	,	0	},
	{	2	,	0	,	2	,	0	,	0	,	0	,	0	,	0	},
	{	0	,	2	,	0	,	2	,	0	,	0	,	0	,	0	},
	{	3	,	3	,	3	,	3	,	0	,	0	,	0	,	0	}
};



#define USE_T_ID			0
#define USE_T_GREAD			1
#define USE_T_INFO			2
static const short H_Potion_Table[3][3]={//힐링용품
	{	200	,	1	,	15	},
	{	201	,	2	,	40	},
	{	202	,	3	,	65	}
};
static const short M_Potion_Table[3][3]={//마나용품
	{	203	,	1	,	5	},
	{	204	,	2	,	15	},
	{	205	,	3	,	20	}
};
static const short Bag_Table[4][3]={//가방
	{	100	,	3	,	8	},
	{	101	,	4	,	16	},
	{	102	,	5	,	24	},
	{	102	,	6	,	32	}
};
static const short Enchant_Table[3][3]={//강화용품
	{	400	,	3	,	1	},
	{	401	,	5	,	2	},
	{	402	,	6	,	30	}
};
static const short Book_Table[3][3]={//스킬북
	{	500	,	5	,	0	},
	{	501	,	6	,	1	},
	{	502	,	7	,	2	}
};


static const short MixBook_600[9][7]={//조합서
	{	1000	,	201	,	5	,	204	,	5	,	1424	,	1	},
	{	1001	,	201	,	5	,	204	,	5	,	1423	,	1	},
	{	1002	,	201	,	5	,	204	,	5	,	1424	,	10	},
	{	1003	,	201	,	5	,	204	,	5	,	1423	,	10	},
	{	1004	,	201	,	5	,	204	,	5	,	   0	,	0	},
	{	1002	,	201	,	65	,	204	,	5	,	   0	,	0	},
	{	1003	,	201	,	5	,	204	,	65	,	   0	,	0	},
	{	1004	,	201	,	5	,	  0	,	0	,	   0	,	0	},
	{	1005	,	201	,	1	,	204	,	1	,	1424	,	1	}
};
static const short MixBook_601[2][7]={//조합서
	{	1002	,	201	,	1	,	0	,	0	,	0	,	0	},
	{	1003	,	204	,	1	,	0	,	0	,	0	,	0	}
};
static const short MixBook_602[2][7]={//조합서
	{	1004	,	201	,	5	,	204	,	5	,	1424	,	0	},
	{	1005	,	201	,	1	,	204	,	1	,	1424	,	2	}
};
static const short MixBook_603[2][7]={//조합서
	{	1006	,	201	,	5	,	204	,	5	,	1424	,	0	},
	{	1007	,	201	,	1	,	204	,	1	,	1424	,	1	}
};
static const short MixBook_604[2][7]={//조합서
	{	1008	,	201	,	5	,	204	,	5	,	1424	,	0	},
	{	1009	,	201	,	1	,	204	,	1	,	1424	,	1	}
};