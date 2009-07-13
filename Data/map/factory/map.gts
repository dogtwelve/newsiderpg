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
		    1 "DIR" "UP:1 DOWN:2 LEFT:3 RIGHT:4"
		    100 "N" "NEXT_STAGE"
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

TEMPLATE OBJECT_LAYER "GASS_GREEN"
{
      ID     1900
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_GREEN1"
{
      ID     1901
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_GREEN2"
{
      ID     1902
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_BLUE"
{
      ID     1903
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_BLUE1"
{
      ID     1904
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_BLUE2"
{
      ID     1905
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_GRAY"
{
      ID     1906
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_GRAY1"
{
      ID     1907
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_PURPLE"
{
      ID     1908
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "GASS_PURPLE1"
{
      ID     1909
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "PAN1"
{
      ID     1910
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "PAN2"
{
      ID     1911
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "PAN3"
{
      ID     1912
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "PAN4"
{
      ID     1913
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "PAN5_END"
{
      ID     1914
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX1_L"
{
      ID     1915
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX1_R"
{
      ID     1916
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX1_UP"
{
      ID     1917
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX1_DOWN"
{
      ID     1918
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX2_1"
{
      ID     1919
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX2_2"
{
      ID     1920
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX2_3"
{
      ID     1921
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX2_2R"
{
      ID     1922
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX2_3R"
{
      ID     1923
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX3_1"
{
      ID     1924
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BOX3_1R"
{
      ID     1925
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACKLI"
{
      ID     1926
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "OUTPAN1"
{
      ID     1927
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "OUTPAN2"
{
      ID     1928
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "P"
{
      ID     1929
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "OUTPAN3"
{
      ID     1930
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "OUTPAN4"
{
      ID     1931
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_18.SPRITE"
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

TEMPLATE OBJECT_LAYER "BROAD"
{
      ID     2000
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACK1"
{
      ID     2001
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACK2"
{
      ID     2002
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "SCAR1"
{
      ID     2003
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "SCAR2"
{
      ID     2004
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "SCAR3"
{
      ID     2005
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "SCAR4"
{
      ID     2006
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "SCAR5"
{
      ID     2007
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "LOCK"
{
      ID     2008
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "OBJL"
{
      ID     2009
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "OBJR"
{
      ID     2010
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "SHADOW1"
{
      ID     2011
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "SHADOW2"
{
      ID     2012
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT1R"
{
      ID     2013
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT2"
{
      ID     2014
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT3R"
{
      ID     2015
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT4"
{
      ID     2016
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT5R"
{
      ID     2017
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT6"
{
      ID     2018
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT7R"
{
      ID     2019
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "FRONT8"
{
      ID     2020
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_19.SPRITE"
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

TEMPLATE OBJECT_LAYER "DOWNLIGHT"
{
      ID     2100
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "S_GREEN"
{
      ID     2101
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "S_YELLOWLIGHTING"
{
      ID     2102
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACK_BLUELIGHTING"
{
      ID     2103
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACK_REDLIGHTING"
{
      ID     2104
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "P1"
{
      ID     2105
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "P2"
{
      ID     2106
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "B1"
{
      ID     2107
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "B2"
{
      ID     2108
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "G1"
{
      ID     2109
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "G2"
{
      ID     2110
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "PU1"
{
      ID     2111
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "PU2"
{
      ID     2112
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "Y1"
{
      ID     2113
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "Y2"
{
      ID     2114
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "WHOLELINE1"
{
      ID     2115
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "WHOLELINE2"
{
      ID     2116
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "WHOLELINE3"
{
      ID     2117
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "WHOLELINE4"
{
      ID     2118
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "WHOLELINE5"
{
      ID     2119
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "TOP1"
{
      ID     2120
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "TOP2"
{
      ID     2121
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
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

TEMPLATE OBJECT_LAYER "ANI_ONE"
{
      ID     2122
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	5


      PARAMS
      {
            5	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_TWO"
{
      ID     2123
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	7


      PARAMS
      {
            7	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_THREE"
{
      ID     2124
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	9


      PARAMS
      {
            9	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            2	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_PINK"
{
      ID     2125
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	11


      PARAMS
      {
            11	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            3	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_BLUE"
{
      ID     2126
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	13


      PARAMS
      {
            13	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            4	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_GREE"
{
      ID     2127
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	15


      PARAMS
      {
            15	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            5	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_PURPLE"
{
      ID     2128
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	17


      PARAMS
      {
            17	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            6	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_YELLOW"
{
      ID     2129
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	19


      PARAMS
      {
            19	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            7	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_TOP_B"
{
      ID     2130
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	31


      PARAMS
      {
            31	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            8	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_TOP_G"
{
      ID     2131
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_20.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	33


      PARAMS
      {
            33	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            9	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "FILL1"
{
      ID     2200
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "FILL2_L"
{
      ID     2201
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "FILL2_R"
{
      ID     2202
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "SH_L"
{
      ID     2203
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "SH_R"
{
      ID     2204
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "R_131"
{
      ID     2205
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "R_132"
{
      ID     2206
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "R_133"
{
      ID     2207
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "LOCK_GRAY"
{
      ID     2208
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACKLINE"
{
      ID     2209
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "LADDER"
{
      ID     2210
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "REDWIRE1"
{
      ID     2211
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "REDWIRE2"
{
      ID     2212
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "REDWIRE3"
{
      ID     2213
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACKOUT1"
{
      ID     2214
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACKOUT2_L"
{
      ID     2215
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "BACKOUT2_R"
{
      ID     2216
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE1_L"
{
      ID     2217
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE1_R"
{
      ID     2218
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE1S_R"
{
      ID     2219
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE1S_L"
{
      ID     2220
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE2_L"
{
      ID     2221
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE2_R"
{
      ID     2222
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE3_L"
{
      ID     2223
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE3_R"
{
      ID     2224
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE4_OB"
{
      ID     2225
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE5_OB"
{
      ID     2226
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE6_OB"
{
      ID     2227
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE7_L"
{
      ID     2228
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE7_R"
{
      ID     2229
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE81"
{
      ID     2230
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
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

TEMPLATE OBJECT_LAYER "PIPE82"
{
      ID     2231
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	46


      PARAMS
      {
            46	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            46	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PIPE9_OB"
{
      ID     2232
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	47


      PARAMS
      {
            47	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            47	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GAS1"
{
      ID     2233
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	48


      PARAMS
      {
            48	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            48	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GAS2"
{
      ID     2234
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	49


      PARAMS
      {
            49	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            49	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GAS3"
{
      ID     2235
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	50


      PARAMS
      {
            50	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            50	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASLINE1_L"
{
      ID     2236
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	51


      PARAMS
      {
            51	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            51	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASLINE1_R"
{
      ID     2237
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	52


      PARAMS
      {
            52	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            52	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASLINE2_L"
{
      ID     2238
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	53


      PARAMS
      {
            53	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            53	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
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

TEMPLATE OBJECT_LAYER "GASLINE2_R"
{
      ID     2239
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	54


      PARAMS
      {
            54	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            54	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASLINE3_L"
{
      ID     2240
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	55


      PARAMS
      {
            55	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            55	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASLINE3_R"
{
      ID     2241
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	56


      PARAMS
      {
            56	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            56	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASLINE4"
{
      ID     2242
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	57


      PARAMS
      {
            57	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            57	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASLINE5_L"
{
      ID     2243
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	58


      PARAMS
      {
            58	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            58	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASLINE5_R"
{
      ID     2244
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	59


      PARAMS
      {
            59	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            59	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GAS4"
{
      ID     2245
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	60


      PARAMS
      {
            60	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            60	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BBOX1"
{
      ID     2246
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	61


      PARAMS
      {
            61	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            61	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BBOX2"
{
      ID     2247
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	62


      PARAMS
      {
            62	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            62	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "BBOX3"
{
      ID     2248
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	63


      PARAMS
      {
            63	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            63	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASSCAR1"
{
      ID     2249
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	64


      PARAMS
      {
            64	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            64	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASSCAR2"
{
      ID     2250
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	65


      PARAMS
      {
            65	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            65	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASSCAR3"
{
      ID     2251
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	66


      PARAMS
      {
            66	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            66	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "GASBBOX"
{
      ID     2252
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	67


      PARAMS
      {
            67	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            67	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "PLIGHT"
{
      ID     2253
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	68


      PARAMS
      {
            68	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            0	"ANI TYPE" "0:FRAME, 1:ANI"
            68	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_PINWHEEEL"
{
      ID     2254
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	14


      PARAMS
      {
            14	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            0	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_WHEEL"
{
      ID     2255
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	18


      PARAMS
      {
            18	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            1	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_NASA1"
{
      ID     2256
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	21


      PARAMS
      {
            21	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            2	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_NASA2"
{
      ID     2257
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	23


      PARAMS
      {
            23	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            3	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_NASA3"
{
      ID     2258
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	25


      PARAMS
      {
            25	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            4	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

TEMPLATE OBJECT_LAYER "ANI_NASA4"
{
      ID     2259
      SPRITE ".\..\..\GFX\SPRITES\BACKGROUND\MAP_21.SPRITE"
      SET SPRITE 0
      SET MODULE -1
      SET FRAME	27


      PARAMS
      {
            27	"NOT FIX" "VIEW TOOL IDX"
            0	"NOT FIX" "STATIC VALUE"
            1	"ANI TYPE" "0:FRAME, 1:ANI"
            5	"DRAW IDX" "ANI OR FRAME IDX"
            0	"NOT USE" ""
      }
}

