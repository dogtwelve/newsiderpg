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


TEMPLATE OBJECT_LAYER "HOUSE_1A"
{
      ID     1100
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_10.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSE_1B"
{
      ID     1101
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_10.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSE_2A"
{
      ID     1102
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_10.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSE_2B"
{
      ID     1103
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_10.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSE_2C"
{
      ID     1104
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_10.SPRITE"
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

TEMPLATE OBJECT_LAYER "WATER"
{
      ID     1200
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSES_ALL"
{
      ID     1201
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSES_1"
{
      ID     1202
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSES_2"
{
      ID     1203
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSES_3"
{
      ID     1204
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSES_4"
{
      ID     1205
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "HOUSES_5"
{
      ID     1206
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "WALL"
{
      ID     1207
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "HALL"
{
      ID     1208
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "WATER1"
{
      ID     1209
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_11.SPRITE"
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

TEMPLATE OBJECT_LAYER "TOWER"
{
      ID     1300
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "SIGN_POTION"
{
      ID     1301
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "SIGN_FORGE"
{
      ID     1302
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "SIGN_WEAPON"
{
      ID     1303
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "SIGN_FLOWER"
{
      ID     1304
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "SIGN_INN"
{
      ID     1305
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "BAG1"
{
      ID     1306
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "BAG2"
{
      ID     1307
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "BAG3"
{
      ID     1308
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "JAR1"
{
      ID     1309
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "JAR2"
{
      ID     1310
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "JAR3"
{
      ID     1311
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "SWORD"
{
      ID     1312
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "DRUM"
{
      ID     1313
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX"
{
      ID     1314
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "WOOD"
{
      ID     1315
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "ARMOR"
{
      ID     1316
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "FLOWER1"
{
      ID     1317
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "FLOWER2"
{
      ID     1318
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "FLOWER3"
{
      ID     1319
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "FLOWER4"
{
      ID     1320
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "FLOWER5"
{
      ID     1321
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "TREE1"
{
      ID     1322
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "TREE2"
{
      ID     1323
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "FOUNTAIN"
{
      ID     1324
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "LIGHT"
{
      ID     1325
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_12.SPRITE"
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

TEMPLATE OBJECT_LAYER "LAND"
{
      ID     1400
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_13.SPRITE"
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

