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

TEMPLATE OBJECT_LAYER "PILLARBIG"
{
      ID     1700
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PILLARMIDDLE_OUT"
{
      ID     1701
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PILLARMIDDLE_IN"
{
      ID     1702
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "H_NO"
{
      ID     1703
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PILLARBACK_IN1"
{
      ID     1704
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PILLARBACK_IN2_L"
{
      ID     1705
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PILLARBACK_IN2_R"
{
      ID     1706
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PILLARBACK_IN3"
{
      ID     1707
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PATTERN1"
{
      ID     1708
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PATTERN2"
{
      ID     1709
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PATTERN_LIGHT"
{
      ID     1710
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PATTERNBACK_OUT1"
{
      ID     1711
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PATTERNBACK_OUT2"
{
      ID     1712
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PATTERNBACK_OUT3"
{
      ID     1713
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PATTERNBACK_OUT4"
{
      ID     1714
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PATTERNBACK_IN"
{
      ID     1715
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "LINE"
{
      ID     1716
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "DEVIL"
{
      ID     1717
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "SHADOW"
{
      ID     1718
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT1"
{
      ID     1719
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT2"
{
      ID     1720
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "EXITIN"
{
      ID     1721
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "EXITOUT"
{
      ID     1722
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "PALACE_LIGHT"
{
      ID     1723
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_16.SPRITE"
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

TEMPLATE OBJECT_LAYER "FIRE_BLUE_ANI"
{
      ID     1800
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_17.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	0


      PARAMS
      {
            0	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "FIRE_GREEN_ANI"
{
      ID     1801
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_17.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	6


      PARAMS
      {
            6	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "FIRE_PURPLE_ANI"
{
      ID     1802
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_17.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	12


      PARAMS
      {
            12	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            2	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "FIRE_RED_ANI"
{
      ID     1803
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_17.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	18


      PARAMS
      {
            18	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            3	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "FIRE_YELLOW_ANI"
{
      ID     1804
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_17.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	24


      PARAMS
      {
            24	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            4	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "SMALLFIRE_GREEN_ANI"
{
      ID     1805
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_17.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	30


      PARAMS
      {
            30	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            5	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "SMALLFIRE_RED_ANI"
{
      ID     1806
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_17.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	36


      PARAMS
      {
            36	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            6	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BASCAR1"
{
      ID     3200
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "BASCAR2"
{
      ID     3201
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "BASCAR3"
{
      ID     3202
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "BAB1"
{
      ID     3203
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "BAB2"
{
      ID     3204
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "BAB3"
{
      ID     3205
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "BADENT1"
{
      ID     3206
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "BADENT2"
{
      ID     3207
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "BADENT3"
{
      ID     3208
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
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

TEMPLATE OBJECT_LAYER "ZZ_BASTONE1"
{
      ID     3209
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	9


      PARAMS
      {
            9	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            9	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ZZ_BASTONE2"
{
      ID     3210
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_31.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	10


      PARAMS
      {
            10	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            10	"DRAW IDX" "ANI OR FRAME IDX"
            1	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CARPET1"
{
      ID     3500
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_34.SPRITE"
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

TEMPLATE OBJECT_LAYER "CARPET2"
{
      ID     3501
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_34.SPRITE"
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

TEMPLATE OBJECT_LAYER "CARPET3"
{
      ID     3502
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_34.SPRITE"
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

TEMPLATE OBJECT_LAYER "CHAIR1"
{
      ID     3503
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_34.SPRITE"
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

TEMPLATE OBJECT_LAYER "CHAIR2"
{
      ID     3504
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_34.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOOUP"
{
      ID     3505
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_34.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOODOWN"
{
      ID     3506
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_34.SPRITE"
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

TEMPLATE OBJECT_LAYER "CANDLE_BIG"
{
      ID     3600
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_35.SPRITE"
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

TEMPLATE OBJECT_LAYER "CANDLE_MIDDLE"
{
      ID     3601
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_35.SPRITE"
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

TEMPLATE OBJECT_LAYER "CANDLE_SMALL"
{
      ID     3602
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_35.SPRITE"
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

TEMPLATE OBJECT_LAYER "CHANDELIER"
{
      ID     3603
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_35.SPRITE"
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

TEMPLATE OBJECT_LAYER "CANDLE_LIGHT_Y_ANI"
{
      ID     3604
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_35.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	1


      PARAMS
      {
            1	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "CANDLE_LIGHT_R_ANI"
{
      ID     3605
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_35.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	2


      PARAMS
      {
            2	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

