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

TEMPLATE OBJECT_LAYER "F_BG1"
{
      ID     100
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_0.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_BG2"
{
      ID     101
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_0.SPRITE"
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

TEMPLATE OBJECT_LAYER "A_BGLIGHT_00"
{
      ID     102
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_0.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	2


      PARAMS
      {
            2	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "A_BGLIGHT_01"
{
      ID     103
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_0.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	3


      PARAMS
      {
            3	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "A_BGLIGHT_02"
{
      ID     104
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_0.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	4


      PARAMS
      {
            4	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            2	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "F_FIELD1"
{
      ID     200
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_1.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_FIELD2"
{
      ID     201
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_1.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_TOP_00"
{
      ID     300
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_2.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_TOP_01"
{
      ID     301
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_2.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_TOP_02"
{
      ID     302
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_2.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_TOP_03"
{
      ID     303
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_2.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_ROAD_TOP"
{
      ID     304
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_2.SPRITE"
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

TEMPLATE OBJECT_LAYER "A_FRONTLIGHT_00"
{
      ID     305
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_2.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	6


      PARAMS
      {
            6	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "A_FRONTLIGHT_01"
{
      ID     306
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_2.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	5


      PARAMS
      {
            5	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "F_BOTTOM"
{
      ID     400
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_3.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_BOTTOM_01"
{
      ID     401
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_3.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_BOTTOM_02"
{
      ID     402
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_3.SPRITE"
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

TEMPLATE OBJECT_LAYER "F_BOTTOM_03"
{
      ID     403
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_3.SPRITE"
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

