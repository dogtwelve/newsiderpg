DATA_TYPE LIST "ActorFlags"
{		
	0 = "Inactive"
	1 = "FlipX"
	2 = "MAPLayer"
	4 = "BOTTOMLayer"
	8 = "TOPLayer"
  16 = "HIDELayer"	
}


//////////////////////////////////////////////////////////////////////////////
// TILESET TILESET TILESET TILESET TILESET TILESET TILESET TILESET TILESET  //
//////////////////////////////////////////////////////////////////////////////

TEMPLATE OBJECT_LAYER "HERO_MC"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 1
    SPRITE ".\..\GFX\SPRITES\CHARACTER\woman_body.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "HERO_NPC"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 2
    SPRITE ".\..\GFX\SPRITES\CHARACTER\man_body.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC1_BOY"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 3
    SPRITE ".\..\GFX\SPRITES\NPC\npc_01.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC2"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 4
    SPRITE ".\..\GFX\SPRITES\NPC\npc_02.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "NPC3_DAEMURI_NOIN"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 5
    SPRITE ".\..\GFX\SPRITES\NPC\npc_03.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC4"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 6
    SPRITE ".\..\GFX\SPRITES\NPC\npc_04.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC5"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 7
    SPRITE ".\..\GFX\SPRITES\NPC\npc_05.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC6"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 8
    SPRITE ".\..\GFX\SPRITES\NPC\npc_06.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC7"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 9
    SPRITE ".\..\GFX\SPRITES\NPC\npc_07.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC8"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 10
    SPRITE ".\..\GFX\SPRITES\NPC\npc_08.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC9"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 11
    SPRITE ".\..\GFX\SPRITES\NPC\npc_09.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC10"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 12
    SPRITE ".\..\GFX\SPRITES\NPC\npc_10.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC11_SIGE"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 13
    SPRITE ".\..\GFX\SPRITES\NPC\npc_11.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC12_RONE"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 14
    SPRITE ".\..\GFX\SPRITES\NPC\npc_12.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC13"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 15
    SPRITE ".\..\GFX\SPRITES\NPC\npc_13.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC14_ANGELS"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 16
    SPRITE ".\..\GFX\SPRITES\NPC\npc_14.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC15"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 17
    SPRITE ".\..\GFX\SPRITES\NPC\npc_15.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC16"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 18
    SPRITE ".\..\GFX\SPRITES\NPC\npc_16.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC17_SIRANO"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 19
    SPRITE ".\..\GFX\SPRITES\NPC\npc_17.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_COBOLT"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 100
    SPRITE ".\..\GFX\SPRITES\MONSTER\MON05.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "EFFECT"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 200
    SPRITE ".\..\GFX\SPRITES\UI\weffect.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC18"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 20
    SPRITE ".\..\GFX\SPRITES\NPC\npc_18.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "NPC19"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 21
    SPRITE ".\..\GFX\SPRITES\NPC\npc_19.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "BLACKOUT"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 201
    SPRITE ".\..\GFX\SPRITES\cinema\blackout.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "EMOTICON_QUEST"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 202
    SPRITE ".\..\GFX\SPRITES\cinema\emoticon_quest.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "EMOTICON_ETC"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 203
    SPRITE ".\..\GFX\SPRITES\cinema\emoticon_etc.SPRITE"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "ITEM"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 204
    SPRITE ".\..\GFX\SPRITES\ui\item.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "ROCK"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 205
    SPRITE ".\..\GFX\SPRITES\monster\mon_stone_big.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_RAPTER"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 206
    SPRITE ".\..\GFX\SPRITES\monster\mon01.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_GOLEM"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 207
    SPRITE ".\..\GFX\SPRITES\monster\mon02.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_SLIME"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 208
    SPRITE ".\..\GFX\SPRITES\monster\mon03.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_WATER_ELE"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 209
    SPRITE ".\..\GFX\SPRITES\monster\mon04.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_BIGBIRD"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 210
    SPRITE ".\..\GFX\SPRITES\monster\mon06.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_TANK"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 211
    SPRITE ".\..\GFX\SPRITES\monster\mon07.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_PUMPKIN"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 212
    SPRITE ".\..\GFX\SPRITES\monster\mon08.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_SKELTON"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 213
    SPRITE ".\..\GFX\SPRITES\monster\mon09.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_GUNNER"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 214
    SPRITE ".\..\GFX\SPRITES\monster\mon10.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_FAIRLY"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 215
    SPRITE ".\..\GFX\SPRITES\monster\mon11.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_TRICARATOPS"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 216
    SPRITE ".\..\GFX\SPRITES\monster\mon12.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_REDDRAGON"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 217
    SPRITE ".\..\GFX\SPRITES\monster\mon13.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_DEVIL"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 218
    SPRITE ".\..\GFX\SPRITES\monster\mon14.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_HUMAN"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 219
    SPRITE ".\..\GFX\SPRITES\monster\mon15.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "MON_FLOWER"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 220
    SPRITE ".\..\GFX\SPRITES\monster\mon16.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_CRAB"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 221
    SPRITE ".\..\GFX\SPRITES\monster\mon17.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "MON_BUG"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 222
    SPRITE ".\..\GFX\SPRITES\monster\mon18.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "45_BOX"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 223
    SPRITE ".\..\GFX\SPRITES\monster\mon_box.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "46_KNIGHT"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 224
    SPRITE ".\..\GFX\SPRITES\monster\mon_knight.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}


TEMPLATE OBJECT_LAYER "47_TEMPLE_STONEBOX"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 225
    SPRITE ".\..\GFX\SPRITES\monster\mon_temple_stonebox.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "48_W_O_SEFF6"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 226
    SPRITE ".\..\GFX\SPRITES\character\woman_s_o6.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "49_BOSS1"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 227
    SPRITE ".\..\GFX\SPRITES\monster\boss_1.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "50_BOSS2"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 228
    SPRITE ".\..\GFX\SPRITES\monster\boss_2.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "51_BOSS3"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 229
    SPRITE ".\..\GFX\SPRITES\monster\boss_3.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "52_BOSS4"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 230
    SPRITE ".\..\GFX\SPRITES\monster\boss_4.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "53_BOSS5"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 231
    SPRITE ".\..\GFX\SPRITES\monster\boss_5.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "54_BOSS6"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 232
    SPRITE ".\..\GFX\SPRITES\monster\boss_6.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "55_BOSS7"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 233
    SPRITE ".\..\GFX\SPRITES\monster\boss_7.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}

TEMPLATE OBJECT_LAYER "TESTBACK"
{
// for ID value, see ENTITY.java, the ENTITY interface.
    ID 1000
    SPRITE "testmap.sprite"

	SET SPRITE 0
    SET MODULE -1
    SET AFRAME 0
    SET ANIM PARAM[0]
    SET FLAGS PARAM[1] 0x0001

    PARAMS
    {
        0 "AnimID" "AnimationID"
        0  "Flags" "flip flag etc."	TYPE "ActorFlags"
    }
}



