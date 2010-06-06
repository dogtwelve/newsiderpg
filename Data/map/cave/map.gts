TEMPLATE OBJECT_LAYER "END_OF_LAYER"
{
    ID 1
    SPRITE ".\mapbase.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "IMG NUM" ""
    	0 "TYPE" "STATIC VALUE"
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "UNDER_LINE"
{
    ID 2
    SPRITE ".\mapbase.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "IMG NUM" ""
    	0 "TYPE" "STATIC VALUE"
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "UPPER_LINE"
{
    ID 3
    SPRITE ".\mapbase.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "IMG NUM" ""
    	0 "TYPE" "STATIC VALUE"
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "FILL_RECT"
{
    ID 11
    SET RECT_AREA 0 0 PARAM[0] PARAM[1] RGB(255, 0, 0)
    PARAMS
    {
        80 "w" "Zone width"
        80 "h" "Zone height"
		    255	"R" "RED"
		    0	"G" "GREEN"
		    0	"B" "BLUE"
    }
}


TEMPLATE OBJECT_LAYER "EVT_MAP_MOVE"
{
    ID 50
    SET RECT_AREA 0 0 PARAM[0] PARAM[1] RGB(255, 0, 0)
    PARAMS
    {
        40  "w" "Zone width"
        40  "h" "Zone height"
		    1 "TYPE" "ALL:1 AFTER BATTLE:2"
		    100 "N" "NEXT_STAGE"
		    100 "HEROX" "HEROX"
		    100 "HEROY" "HEROY"
    }
}

TEMPLATE OBJECT_LAYER "EVT_MAP_SIZE"
{
    ID 51
    SPRITE ".\mapbase.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "IMG NUM" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "EVT_NPC"
{
    ID 52
    SPRITE ".\mapbase.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME 3

    PARAMS
    {
    	0 "NPC_NUM" "NPC_NUM"
    	0 "NEXT_EVT" "NEXT_EVT CODE"
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "DONT_GO_RECT"
{
    ID 53
    SET RECT_AREA 0 0 PARAM[0] PARAM[1] RGB(0, 255, 0)
    PARAMS
    {
        100  "w" "Zone width"
        100  "h" "Zone height"
		    0 "NOT USE" ""
		    0 "NOT USE" ""
		    0 "NOT USE" ""
		    0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "EVENT_RECT"
{
    ID 54
    SET RECT_AREA 0 0 PARAM[0] PARAM[1] RGB(0, 0, 255)
    PARAMS
    {
        100  "w" "Zone width"
        100  "h" "Zone height"
		    0 "EN" "Event Number"
		    0 "D1" "Dummy1"
		    0 "D2" "Dummy2"
		    0 "D3" "Dummy3"
    }
}

TEMPLATE OBJECT_LAYER "REGEN_MON_RECT"
{
    ID 55
    SPRITE ".\mapbase.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME 4

    PARAMS
    {
    	0 "TYPE" "REGEN_TYPE"
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "ELECTRIC_SH_ANI"
{
      ID     500
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_4.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	8


      PARAMS
      {
            8	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CRYSTAL_BI_ANI"
{
      ID     501
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_4.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	0


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CRYSTAL_B2_ANI"
{
      ID     502
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_4.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	7


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            2	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CRYSTAL_P1_ANI"
{
      ID     503
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_4.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	2


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            3	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CRYSTAL_P2_ANI"
{
      ID     504
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_4.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	4


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            4	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CRYSTAL_P3_ANI"
{
      ID     505
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_4.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	5


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            5	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CRYSTAL_G_ANI"
{
      ID     506
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_4.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	6


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            6	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE1_L"
{
      ID     600
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	0


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE1_R"
{
      ID     601
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	1


      PARAMS
      {
            1	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE2_L"
{
      ID     602
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	2


      PARAMS
      {
            2	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            2	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE2_R"
{
      ID     603
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	3


      PARAMS
      {
            3	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            3	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE3_L"
{
      ID     604
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	4


      PARAMS
      {
            4	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            4	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE3_R"
{
      ID     605
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	5


      PARAMS
      {
            5	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            5	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE_TOP1_L"
{
      ID     606
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	6


      PARAMS
      {
            6	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            6	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE_TOP1_R"
{
      ID     607
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	7


      PARAMS
      {
            7	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            7	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE_TOP2_L"
{
      ID     608
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	8


      PARAMS
      {
            8	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            8	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE_TOP2_R"
{
      ID     609
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	9


      PARAMS
      {
            9	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            9	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE_LIGHTTOP1"
{
      ID     610
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	10


      PARAMS
      {
            10	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            10	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STONE_LIGHTTOP2"
{
      ID     611
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	11


      PARAMS
      {
            11	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            11	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OB_STONE"
{
      ID     612
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	12


      PARAMS
      {
            12	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            12	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OB_FLOWER1"
{
      ID     613
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	13


      PARAMS
      {
            13	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            13	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OB_FLOWER2"
{
      ID     614
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	14


      PARAMS
      {
            14	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            14	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OB_FLOWER3"
{
      ID     615
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	15


      PARAMS
      {
            15	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            15	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CRATER1"
{
      ID     616
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	16


      PARAMS
      {
            16	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            16	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CRATER2"
{
      ID     617
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	17


      PARAMS
      {
            17	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            17	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GRAVEL"
{
      ID     618
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	18


      PARAMS
      {
            18	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            18	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BINE1"
{
      ID     619
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	19


      PARAMS
      {
            19	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            19	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BINE2"
{
      ID     620
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	20


      PARAMS
      {
            20	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            20	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BINE3"
{
      ID     621
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	21


      PARAMS
      {
            21	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            21	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PATTERN_BACK"
{
      ID     622
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	22


      PARAMS
      {
            22	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            22	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PATTERN_ROAD1"
{
      ID     623
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	23


      PARAMS
      {
            23	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            23	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PATTERN_ROAD2"
{
      ID     624
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	24


      PARAMS
      {
            24	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            24	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PATTERN_CLIFF1_L"
{
      ID     625
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	25


      PARAMS
      {
            25	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            25	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PATTERN_CLIFF1_R"
{
      ID     626
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	26


      PARAMS
      {
            26	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            26	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PATTERN_CLIFF2_L"
{
      ID     627
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	27


      PARAMS
      {
            27	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            27	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PATTERN_CLIFF2_R"
{
      ID     628
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	28


      PARAMS
      {
            28	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            28	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OUT_STONE_L"
{
      ID     629
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	29


      PARAMS
      {
            29	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            29	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OUT_STONE_R"
{
      ID     630
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	30


      PARAMS
      {
            30	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            30	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STALACTITE1_L"
{
      ID     631
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	31


      PARAMS
      {
            31	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            31	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STALACTITE1_R"
{
      ID     632
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	32


      PARAMS
      {
            32	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            32	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STALACTITE2_UP"
{
      ID     633
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	33


      PARAMS
      {
            33	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            33	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STALACTITE2_DOWN"
{
      ID     634
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	34


      PARAMS
      {
            34	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            34	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STALACTITE3_UP"
{
      ID     635
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	35


      PARAMS
      {
            35	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            35	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "STALACTITE3_DOWN"
{
      ID     636
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	36


      PARAMS
      {
            36	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            36	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "EXIT"
{
      ID     637
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	37


      PARAMS
      {
            37	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            37	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OUT_S_L"
{
      ID     638
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	38


      PARAMS
      {
            38	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            38	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OUT_S_R"
{
      ID     639
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	39


      PARAMS
      {
            39	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            39	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OUT_FLOWER1"
{
      ID     640
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	40


      PARAMS
      {
            40	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            40	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OUT_FLOWER2"
{
      ID     641
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	41


      PARAMS
      {
            41	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            41	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OUT_CRATER1"
{
      ID     642
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	42


      PARAMS
      {
            42	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            42	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "OUT_S"
{
      ID     643
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	43


      PARAMS
      {
            43	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            43	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "DOWNEXIT"
{
      ID     644
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	44


      PARAMS
      {
            44	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            44	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "DOWNEXIT_RED"
{
      ID     645
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_5.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	45


      PARAMS
      {
            45	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            45	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BACK1"
{
      ID     700
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	0


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BACK2"
{
      ID     701
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	1


      PARAMS
      {
            1	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE1_L"
{
      ID     702
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	2


      PARAMS
      {
            2	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            2	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE1_R"
{
      ID     703
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	3


      PARAMS
      {
            3	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            3	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE2_L"
{
      ID     704
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	4


      PARAMS
      {
            4	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            4	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE2_R"
{
      ID     705
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	5


      PARAMS
      {
            5	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            5	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE3_L"
{
      ID     706
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	6


      PARAMS
      {
            6	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            6	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE3_R"
{
      ID     707
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	7


      PARAMS
      {
            7	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            7	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE4_L"
{
      ID     708
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	8


      PARAMS
      {
            8	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            8	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE4_R"
{
      ID     709
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	9


      PARAMS
      {
            9	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            9	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE5_L"
{
      ID     710
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	10


      PARAMS
      {
            10	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            10	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE5_R"
{
      ID     711
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	11


      PARAMS
      {
            11	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            11	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE6_L"
{
      ID     712
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	12


      PARAMS
      {
            12	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            12	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE6_R"
{
      ID     713
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	13


      PARAMS
      {
            13	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            13	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "FI"
{
      ID     714
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	14


      PARAMS
      {
            14	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            14	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "EXIT0"
{
      ID     715
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	15


      PARAMS
      {
            15	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            15	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE7_L"
{
      ID     716
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	16


      PARAMS
      {
            16	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            16	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "RSTONE8_R"
{
      ID     717
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_6.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	17


      PARAMS
      {
            17	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            17	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "SHOCK1_L"
{
      ID     3300
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	0


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "SHOCK1_R"
{
      ID     3301
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	1


      PARAMS
      {
            1	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "SHOCK2_L"
{
      ID     3302
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	2


      PARAMS
      {
            2	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            2	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "SHOCK2_R"
{
      ID     3303
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	3


      PARAMS
      {
            3	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            3	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "DENT1"
{
      ID     3304
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	4


      PARAMS
      {
            4	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            4	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "DENT2"
{
      ID     3305
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	5


      PARAMS
      {
            5	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            5	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "DENT3"
{
      ID     3306
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	6


      PARAMS
      {
            6	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            6	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "LA_SHOCK1_L"
{
      ID     3307
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	7


      PARAMS
      {
            7	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            7	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "LA_SHOCK1_R"
{
      ID     3308
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	8


      PARAMS
      {
            8	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            8	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "LA_SHOCK2_L"
{
      ID     3309
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	9


      PARAMS
      {
            9	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            9	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "LA_SHOCK2_R"
{
      ID     3310
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	10


      PARAMS
      {
            10	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            10	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "LA_DENT1"
{
      ID     3311
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	11


      PARAMS
      {
            11	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            11	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "LA_DENT2"
{
      ID     3312
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	12


      PARAMS
      {
            12	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            12	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "LA_DENT3"
{
      ID     3313
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	13


      PARAMS
      {
            13	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            13	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_ST1"
{
      ID     3314
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	14


      PARAMS
      {
            14	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            14	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_ST2"
{
      ID     3315
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	15


      PARAMS
      {
            15	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            15	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_ST3"
{
      ID     3316
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	16


      PARAMS
      {
            16	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            16	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_ST4"
{
      ID     3317
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	17


      PARAMS
      {
            17	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            17	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_SU1"
{
      ID     3318
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	18


      PARAMS
      {
            18	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            18	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_SU2"
{
      ID     3319
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	19


      PARAMS
      {
            19	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            19	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_SU3"
{
      ID     3320
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	20


      PARAMS
      {
            20	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            20	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_LA_ST1"
{
      ID     3321
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	21


      PARAMS
      {
            21	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            21	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_LA_ST2"
{
      ID     3322
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	22


      PARAMS
      {
            22	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            22	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_LA_ST3"
{
      ID     3323
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	23


      PARAMS
      {
            23	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            23	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_LA_ST4"
{
      ID     3324
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	24


      PARAMS
      {
            24	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            24	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_LA_SU1"
{
      ID     3325
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	25


      PARAMS
      {
            25	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            25	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_LA_SU2"
{
      ID     3326
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	26


      PARAMS
      {
            26	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            26	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_LA_SU3"
{
      ID     3327
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_32.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	27


      PARAMS
      {
            27	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            27	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

