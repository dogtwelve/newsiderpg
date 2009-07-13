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

TEMPLATE OBJECT_LAYER "0_forest_forest1"
{
    ID 100
    SPRITE ".\..\..\gfx\sprites\background\map_0.sprite"

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


TEMPLATE OBJECT_LAYER "0_forest_forest2"
{
    ID 101
    SPRITE ".\..\..\gfx\sprites\background\map_0.sprite"

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


TEMPLATE OBJECT_LAYER "0_forest_forest3"
{
    ID 102
    SPRITE ".\..\..\gfx\sprites\background\map_0.sprite"

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

TEMPLATE OBJECT_LAYER "0_forest_water"
{
    ID 103
    SPRITE ".\..\..\gfx\sprites\background\map_0.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "1_forest_back"
{
    ID 200
    SPRITE ".\..\..\gfx\sprites\background\map_1.sprite"

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


TEMPLATE OBJECT_LAYER "1_forest_backtree"
{
    ID 201
    SPRITE ".\..\..\gfx\sprites\background\map_1.sprite"

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


TEMPLATE OBJECT_LAYER "1_forest_backfront_L"
{
    ID 202
    SPRITE ".\..\..\gfx\sprites\background\map_1.sprite"

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


TEMPLATE OBJECT_LAYER "1_forest_backfront_R"
{
    ID 203
    SPRITE ".\..\..\gfx\sprites\background\map_1.sprite"

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

TEMPLATE OBJECT_LAYER "1_forest_badak"
{
    ID 204
    SPRITE ".\..\..\gfx\sprites\background\map_1.sprite"

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


TEMPLATE OBJECT_LAYER "2_forest_bellflower"
{
    ID 300
    SPRITE ".\..\..\gfx\sprites\background\map_2.sprite"

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


TEMPLATE OBJECT_LAYER "2_forest_ban1stand_ani"
{
    ID 301
    SPRITE ".\..\..\gfx\sprites\background\map_2.sprite"

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


TEMPLATE OBJECT_LAYER "2_forest_ban2one_ani"
{
    ID 302
    SPRITE ".\..\..\gfx\sprites\background\map_2.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	1 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "2_forest_ban3one_ani"
{
    ID 303
    SPRITE ".\..\..\gfx\sprites\background\map_2.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "2_forest_ban4line_ani"
{
    ID 304
    SPRITE ".\..\..\gfx\sprites\background\map_2.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	1 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "2_forest_ban4down_ani"
{
    ID 305
    SPRITE ".\..\..\gfx\sprites\background\map_2.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	0 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "2_forest_flower_ani"
{
    ID 306
    SPRITE ".\..\..\gfx\sprites\background\map_2.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	3 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	5 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "3_forest_herb1_L"
{
    ID 400
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb1_R"
{
    ID 401
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb2_L"
{
    ID 402
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb2_R"
{
    ID 403
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb3_L"
{
    ID 404
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb3_R"
{
    ID 405
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb4_L"
{
    ID 406
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb4_R"
{
    ID 407
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb5_L"
{
    ID 408
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_herb5_R"
{
    ID 409
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_hilight1_L"
{
    ID 410
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_hilight1_R"
{
    ID 411
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_hilight2_L"
{
    ID 412
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_hilight2_R"
{
    ID 413
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_hilight3_L"
{
    ID 414
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_hilight3_R"
{
    ID 415
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree1_L"
{
    ID 416
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree1_R"
{
    ID 417
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree2_L"
{
    ID 418
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree2_R"
{
    ID 419
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree3_L"
{
    ID 420
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree3_R"
{
    ID 421
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree4_L"
{
    ID 422
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree4_R"
{
    ID 423
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree5_L"
{
    ID 424
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree5_R"
{
    ID 425
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree5_top_L"
{
    ID 426
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_tree5_top_R"
{
    ID 427
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_flower1"
{
    ID 428
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_flower2"
{
    ID 429
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_flower3"
{
    ID 430
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_f1_L"
{
    ID 431
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_f1_R"
{
    ID 432
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_f2_L"
{
    ID 433
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_f2_R"
{
    ID 434
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_f3_L"
{
    ID 435
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_f3_R"
{
    ID 436
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_f4_L"
{
    ID 437
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_f4_R"
{
    ID 438
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_fshadow_L"
{
    ID 439
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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

TEMPLATE OBJECT_LAYER "3_forest_fshadow_R"
{
    ID 440
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_fshadow_box"
{
    ID 441
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_uporange1_L"
{
    ID 442
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_uporange1_R"
{
    ID 443
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_uporange2_L"
{
    ID 444
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_uporange2_R"
{
    ID 445
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_uporange3_L"
{
    ID 446
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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

TEMPLATE OBJECT_LAYER "3_forest_uporange3_R"
{
    ID 447
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upblue1_L"
{
    ID 448
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upblue1_R"
{
    ID 449
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upblue2_L"
{
    ID 450
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upblue2_R"
{
    ID 451
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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

TEMPLATE OBJECT_LAYER "3_forest_upblue3_L"
{
    ID 452
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upblue3_R"
{
    ID 453
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upgreen1_L"
{
    ID 454
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upgreen1_R"
{
    ID 455
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upgreen2_L"
{
    ID 456
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upgreen2_R"
{
    ID 457
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upshadow_L"
{
    ID 458
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_upshadow_R"
{
    ID 459
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	59 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	59 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "3_forest_pattern_road"
{
    ID 460
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	60 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	60 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "3_forest_ani_ful1"
{
    ID 461
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	61 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	0 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "3_forest_ani_ful2"
{
    ID 462
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_ani_ful3"
{
    ID 463
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	63 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	2 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "3_forest_ani_ful4"
{
    ID 464
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	64 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	3 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "3_forest_ani_ful5"
{
    ID 465
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	65 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	1 "ANI TYPE" "0:FRAME, 1:ANI"
    	4 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "3_forest_flo1_L"
{
    ID 466
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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

TEMPLATE OBJECT_LAYER "3_forest_flo1_R"
{
    ID 467
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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



TEMPLATE OBJECT_LAYER "3_forest_flo2"
{
    ID 468
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_flo3"
{
    ID 469
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_flo4"
{
    ID 470
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_flo5_L"
{
    ID 471
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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

TEMPLATE OBJECT_LAYER "3_forest_flo5_R"
{
    ID 472
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

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


TEMPLATE OBJECT_LAYER "3_forest_flo6_L"
{
    ID 473
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	73 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	73 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}


TEMPLATE OBJECT_LAYER "3_forest_flo6_R"
{
    ID 474
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	74 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	74 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "3_forest_out"
{
    ID 475
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	75 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	75 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "3_forest_out"
{
    ID 475
    SPRITE ".\..\..\gfx\sprites\background\map_3.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	75 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	75 "DRAW IDX" "ANI OR FRAME IDX"
     	0 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "33_ful1"
{
    ID 3400
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_ful2"
{
    ID 3401
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_ful3"
{
    ID 3402
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_ful4"
{
    ID 3403
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_ful5_ba"
{
    ID 3404
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_ful6_ba"
{
    ID 3405
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_ful7_all"
{
    ID 3406
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_gu"
{
    ID 3407
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_badak1"
{
    ID 3408
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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


TEMPLATE OBJECT_LAYER "33_badak2"
{
    ID 3409
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_badak3"
{
    ID 3410
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_badak4"
{
    ID 3411
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_hole1"
{
    ID 3412
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_hole2"
{
    ID 3413
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_hole3"
{
    ID 3414
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_hole4"
{
    ID 3415
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

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

TEMPLATE OBJECT_LAYER "33_zz_s1"
{
    ID 3416
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	16 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	16 "DRAW IDX" "ANI OR FRAME IDX"
     	1 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "33_zz_s2"
{
    ID 3417
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	17 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	17 "DRAW IDX" "ANI OR FRAME IDX"
     	1 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "33_zz_s3"
{
    ID 3418
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	18 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	18 "DRAW IDX" "ANI OR FRAME IDX"
     	1 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "33_zz_s4"
{
    ID 3419
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	19 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	19 "DRAW IDX" "ANI OR FRAME IDX"
     	1 "NOT USE" ""
    }
}

TEMPLATE OBJECT_LAYER "33_zz_s5"
{
    ID 3420
    SPRITE ".\..\..\gfx\sprites\background\map_33.sprite"

    SET SPRITE 0
    SET MODULE -1
    SET FRAME PARAM[0]

    PARAMS
    {
    	20 "NOT FIX" "VIEW TOOL IDX"
    	0 "NOT FIX" "STATIC VALUE"
    	0 "ANI TYPE" "0:FRAME, 1:ANI"
    	20 "DRAW IDX" "ANI OR FRAME IDX"
     	1 "NOT USE" ""
    }
}
