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


TEMPLATE OBJECT_LAYER "7_sky"
{
    ID 800
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "7_flat1"
{
    ID 801
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "7_flat2"
{
    ID 802
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "7_flat3"
{
    ID 803
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "7_kidong1"
{
    ID 804
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "7_kidong2"
{
    ID 805
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	5 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "7_bridge1"
{
    ID 806
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	6 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	6 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "7_bridge2_L"
{
    ID 807
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	7 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	7 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "7_bridge_flyboat"
{
    ID 808
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	8 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	8 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "7_bridge_boat"
{
    ID 809
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	9 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	9 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "7_bridge3"
{
    ID 810
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	10 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	10 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "7_bridge2_R"
{
    ID 811
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	11 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	11 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "7_bridge4"
{
    ID 812
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	12 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	12 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "7_bridge5"
{
    ID 813
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	13 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	13 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "7_bridge6_L"
{
    ID 814
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	14 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	14 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "7_bridge6_R"
{
    ID 815
    SPRITE ".\..\..\gfx\sprites\background\map_7.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	15 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	15 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "8_flyboat1"
{
    ID 900
    SPRITE ".\..\..\gfx\sprites\background\map_8.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "8_flyboat2"
{
    ID 901
    SPRITE ".\..\..\gfx\sprites\background\map_8.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "8_flyboat3"
{
    ID 902
    SPRITE ".\..\..\gfx\sprites\background\map_8.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "8_flyboat4"
{
    ID 903
    SPRITE ".\..\..\gfx\sprites\background\map_8.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "8_shadow1_l"
{
    ID 904
    SPRITE ".\..\..\gfx\sprites\background\map_8.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "8_shadow1_r"
{
    ID 905
    SPRITE ".\..\..\gfx\sprites\background\map_8.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	5 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "8_shadow2_l"
{
    ID 906
    SPRITE ".\..\..\gfx\sprites\background\map_8.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	6 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	6 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "8_shadow2_r"
{
    ID 907
    SPRITE ".\..\..\gfx\sprites\background\map_8.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	7 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	7 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "9_habor1"
{
    ID 1000
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "9_habor2"
{
    ID 1001
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "9_habor3"
{
    ID 1002
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "9_habor4"
{
    ID 1003
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	5 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "9_haborYellow1"
{
    ID 1004
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	6 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	6 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "9_haborYellow2"
{
    ID 1005
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	7 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	7 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "9_haborYellow3"
{
    ID 1006
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	8 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	8 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "9_haborYellow4"
{
    ID 1007
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	9 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	9 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "9_habor_piece1"
{
    ID 1008
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	11 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	11 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "9_habor_piece2"
{
    ID 1009
    SPRITE ".\..\..\gfx\sprites\background\map_9.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	12 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	12 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_a1"
{
    ID 1100
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	10 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	10 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_a2"
{
    ID 1101
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	11 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	11 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_a3"
{
    ID 1102
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	13 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	13 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_a4"
{
    ID 1103
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	14 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	14 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_a5"
{
    ID 1104
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	15 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	15 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_a6"
{
    ID 1105
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	16 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	16 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_b1"
{
    ID 1106
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	17 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	17 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_b2"
{
    ID 1107
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	18 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	18 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_b3"
{
    ID 1108
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	19 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	19 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_b4"
{
    ID 1109
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	20 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	20 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_b5"
{
    ID 1110
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	21 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	21 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_b6"
{
    ID 1111
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	22 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	22 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_c1"
{
    ID 1112
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	23 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	23 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_c2"
{
    ID 1113
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	24 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	24 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_c3"
{
    ID 1114
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	25 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	25 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_c4"
{
    ID 1115
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	26 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	26 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_c5"
{
    ID 1116
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	27 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	27 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_c6"
{
    ID 1116
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	28 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	28 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_d1"
{
    ID 1117
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	29 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	29 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_d2"
{
    ID 1118
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	30 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	30 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_d3"
{
    ID 1119
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	31 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	31 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_d4"
{
    ID 1120
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	32 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	32 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_d5"
{
    ID 1121
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	33 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	33 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_d6"
{
    ID 1122
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	35 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	35 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}



TEMPLATE OBJECT_LAYER "10_house_e1"
{
    ID 1123
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	36 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	36 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_e2"
{
    ID 1124
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	37 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	37 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_e3"
{
    ID 1125
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	38 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	38 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_e4"
{
    ID 1126
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	39 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	39 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_e5"
{
    ID 1127
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	40 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	40 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "10_house_e6"
{
    ID 1128
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	41 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	41 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_house_e7"
{
    ID 1129
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	42 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	42 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "10_house_e8"
{
    ID 1130
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	43 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	43 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_small1"
{
    ID 1131
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	44 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	44 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_small2"
{
    ID 1132
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	45 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	45 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_small3"
{
    ID 1133
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	46 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	46 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "10_small4"
{
    ID 1134
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	47 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	47 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "10_smalldoor_L"
{
    ID 1135
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	48 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	48 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "10_smalldoor_R"
{
    ID 1136
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	49 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	49 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_smallwindow_L"
{
    ID 1137
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	50 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	50 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_smallwindow_R"
{
    ID 1138
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	51 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	51 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_clock1"
{
    ID 1139
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	52 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	52 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_clock2"
{
    ID 1140
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	53 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	53 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "10_door"
{
    ID 1141
    SPRITE ".\..\..\gfx\sprites\background\map_10.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	54 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	54 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_house_roof_blue"
{
    ID 1200
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_roof_blue"
{
    ID 1201
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "11_small_window_blue"
{
    ID 1202
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "11_clock_blue"
{
    ID 1203
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	5 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_house_roof_green"
{
    ID 1204
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	6 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	6 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_roof_green"
{
    ID 1205
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	7 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	7 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_window_green"
{
    ID 1206
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	8 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	8 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_clock_green"
{
    ID 1207
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	9 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	9 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "11_house_roof_pink"
{
    ID 1208
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	10 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	10 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_roof_pink"
{
    ID 1209
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	11 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	11 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "11_small_window_pink"
{
    ID 1210
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	12 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	12 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_clock_pink"
{
    ID 1211
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	13 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	13 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_house_roof_purple"
{
    ID 1212
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	14 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	14 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_roof_purple"
{
    ID 1213
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	15 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	15 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_window_purple"
{
    ID 1214
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	16 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	16 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_clock_purple"
{
    ID 1215
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	17 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	17 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "11_house_roof_yellow"
{
    ID 1216
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	18 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	18 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_roof_yellow"
{
    ID 1217
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	19 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	19 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_window_yellow"
{
    ID 1218
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	20 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	20 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "11_clock_yellow"
{
    ID 1219
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	21 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	21 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_house_roof_red"
{
    ID 1220
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	22 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	22 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_roof_red"
{
    ID 1221
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	23 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	23 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_small_window_red"
{
    ID 1222
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	24 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	24 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "11_clock_red"
{
    ID 1223
    SPRITE ".\..\..\gfx\sprites\background\map_11.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	25 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	25 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_box1_L"
{
    ID 1300
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_box1_R"
{
    ID 1301
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_box2_L"
{
    ID 1302
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_box2_R"
{
    ID 1303
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_box3_L"
{
    ID 1304
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_box3_R"
{
    ID 1305
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	5 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_bookbox_L"
{
    ID 1306
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	6 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	6 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_bookbox_R"
{
    ID 1307
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	7 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	7 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shelf1_L"
{
    ID 1308
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	8 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	8 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shelf1_R"
{
    ID 1309
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	9 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	9 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shelf2_L"
{
    ID 1310
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	10 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	10 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shelf2_R"
{
    ID 1311
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	11 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	11 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_pouch_red"
{
    ID 1312
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	12 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	12 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_pouch_blue"
{
    ID 1313
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	13 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	13 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_cask_s1"
{
    ID 1314
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	14 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	14 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_cask_s2big"
{
    ID 1315
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	15 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	15 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_cask_s3small"
{
    ID 1316
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	16 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	16 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_cask_s4"
{
    ID 1317
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	17 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	17 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_cask_flower1"
{
    ID 1318
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	18 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	18 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_cask_flower2"
{
    ID 1319
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	19 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	19 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_cask_flower3"
{
    ID 1320
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	20 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	20 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_flower1_back"
{
    ID 1321
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	21 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	21 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_flower2"
{
    ID 1322
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	22 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	22 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_flower3_back"
{
    ID 1323
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	23 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	23 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_flower4"
{
    ID 1324
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	24 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	24 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_flower5"
{
    ID 1325
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	25 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	25 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_flower6_back"
{
    ID 1326
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	26 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	26 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_cord"
{
    ID 1327
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	27 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	27 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_boat_L"
{
    ID 1328
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	28 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	28 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_boat_R"
{
    ID 1329
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	29 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	29 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_boat_no_L"
{
    ID 1330
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	30 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	30 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_boat_no_R"
{
    ID 1331
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	31 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	31 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_bundle1back"
{
    ID 1332
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	32 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	32 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_bundle2"
{
    ID 1333
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	33 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	33 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_bundle3"
{
    ID 1334
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	34 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	34 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_signboard_L"
{
    ID 1335
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	35 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	35 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_signboard_R"
{
    ID 1336
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	36 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	36 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_pot1small"
{
    ID 1337
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	37 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	37 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_pot2"
{
    ID 1338
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	38 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	38 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_pot3big"
{
    ID 1339
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	39 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	39 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_tent1big_L"
{
    ID 1340
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	40 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	40 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_tent1big_R"
{
    ID 1341
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	41 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	41 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_tent2red_L"
{
    ID 1342
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	42 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	42 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_tent2red_R"
{
    ID 1343
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	43 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	43 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_tent2redpole_L"
{
    ID 1344
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	44 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	44 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_tent2redpole_R"
{
    ID 1345
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	45 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	45 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_tent3blue_L"
{
    ID 1346
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	46 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	46 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_tent3blue_R"
{
    ID 1347
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	47 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	47 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_tent4small_L"
{
    ID 1348
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	48 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	48 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_tent4small_R"
{
    ID 1349
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	49 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	49 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_wood1_L"
{
    ID 1350
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	50 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	50 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_wood1_R"
{
    ID 1351
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	51 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	51 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_wood2"
{
    ID 1352
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	52 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	52 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_wood3"
{
    ID 1353
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	53 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	53 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_wood4_L"
{
    ID 1354
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	54 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	54 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_wood4_R"
{
    ID 1355
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	55 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	55 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_wood5"
{
    ID 1356
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	56 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	56 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_doorknife_L"
{
    ID 1357
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	57 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	57 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_doorknife_R"
{
    ID 1358
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	58 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	58 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_forgeback_L"
{
    ID 1359
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	65 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	65 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_forgeback_R"
{
    ID 1360
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	66 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	66 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_forgefront"
{
    ID 1361
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	67 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	67 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_forgecask1"
{
    ID 1362
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	68 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	68 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_forgecask2"
{
    ID 1363
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	69 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	69 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_forgecask3"
{
    ID 1364
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	70 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	70 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_log1"
{
    ID 1365
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	71 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	71 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_log2"
{
    ID 1366
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	72 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	72 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadowhouse_big"
{
    ID 1367
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	79 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	79 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadowhouse_small"
{
    ID 1368
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	80 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	80 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadowbig_one"
{
    ID 1369
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	81 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	81 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadowmid_one"
{
    ID 1370
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	82 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	82 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadow_one1"
{
    ID 1371
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	83 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	83 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadow_one2"
{
    ID 1372
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	84 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	84 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadow"
{
    ID 1373
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	85 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	85 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_shadowclock"
{
    ID 1374
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	86 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	86 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadowboard"
{
    ID 1375
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	87 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	87 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_fuel_ani"
{
    ID 1376
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	59 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "12_smake_ani"
{
    ID 1377
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	62 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_lightflowershop_ani"
{
    ID 1378
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	73 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_lightwindow_ani"
{
    ID 1379
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	75 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_streetlamp_ani"
{
    ID 1380
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	77 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "12_shadowhowse_big2"
{
    ID 1381
    SPRITE ".\..\..\gfx\sprites\background\map_12.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	88 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	88 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_forge"
{
    ID 1400
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_equipment"
{
    ID 1401
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_sundries"
{
    ID 1402
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_jewelshop"
{
    ID 1403
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_trainingshop"
{
    ID 1404
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_board1"
{
    ID 1405
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	5 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_board2"
{
    ID 1406
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	6 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	6 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_line"
{
    ID 1407
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	7 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	7 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "13_armor"
{
    ID 1408
    SPRITE ".\..\..\gfx\sprites\background\map_13.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	8 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	8 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "14_tree1"
{
    ID 1500
    SPRITE ".\..\..\gfx\sprites\background\map_14.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "14_tree2"
{
    ID 1501
    SPRITE ".\..\..\gfx\sprites\background\map_14.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "14_tree3"
{
    ID 1502
    SPRITE ".\..\..\gfx\sprites\background\map_14.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "14_tree4"
{
    ID 1503
    SPRITE ".\..\..\gfx\sprites\background\map_14.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "14_tree5"
{
    ID 1504
    SPRITE ".\..\..\gfx\sprites\background\map_14.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "15_water_ani"
{
    ID 1600
    SPRITE ".\..\..\gfx\sprites\background\map_15.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "26_forest_vil_down"
{
    ID 2700
    SPRITE ".\..\..\gfx\sprites\background\map_26.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "26_forest_vil_dol1"
{
    ID 2701
    SPRITE ".\..\..\gfx\sprites\background\map_26.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "26_forest_vil_dol2"
{
    ID 2702
    SPRITE ".\..\..\gfx\sprites\background\map_26.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "26_forest_vil_dol3"
{
    ID 2703
    SPRITE ".\..\..\gfx\sprites\background\map_26.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "26_forest_vil_dol4"
{
    ID 2704
    SPRITE ".\..\..\gfx\sprites\background\map_26.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "26_forest_vil_dol5"
{
    ID 2705
    SPRITE ".\..\..\gfx\sprites\background\map_26.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	5 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "26_forest_vil_dol6"
{
    ID 2706
    SPRITE ".\..\..\gfx\sprites\background\map_26.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	6 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	6 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "27_forest_vilup"
{
    ID 2800
    SPRITE ".\..\..\gfx\sprites\background\map_27.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "27_forest_viltree1"
{
    ID 2801
    SPRITE ".\..\..\gfx\sprites\background\map_27.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "27_forest_viltree2"
{
    ID 2802
    SPRITE ".\..\..\gfx\sprites\background\map_27.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	2 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "27_forest_viltree3"
{
    ID 2803
    SPRITE ".\..\..\gfx\sprites\background\map_27.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "27_forest_viltree4"
{
    ID 2804
    SPRITE ".\..\..\gfx\sprites\background\map_27.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	4 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "27_forest_viltree5"
{
    ID 2805
    SPRITE ".\..\..\gfx\sprites\background\map_27.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	5 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "28_sa_vil_down"
{
    ID 2900
    SPRITE ".\..\..\gfx\sprites\background\map_28.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "28_sa_vil_normal"
{
    ID 2901
    SPRITE ".\..\..\gfx\sprites\background\map_28.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "29_sa_vil_mountain"
{
    ID 3000
    SPRITE ".\..\..\gfx\sprites\background\map_29.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "30_sa_vil_sky"
{
    ID 3100
    SPRITE ".\..\..\gfx\sprites\background\map_30.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "36_normal_vil_down"
{
    ID 3700
    SPRITE ".\..\..\gfx\sprites\background\map_36.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}