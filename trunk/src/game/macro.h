#define SCALE_IN_X(x)				(((x)*ZOOM_X)/ZOOM_X_DIV)
#define SCALE_IN_Y(y)				(((y)*ZOOM_Y)/ZOOM_Y_DIV)

#define SCALE_OUT_X(x)				(((x)*ZOOM_X_DIV)/ZOOM_X)
#define SCALE_OUT_Y(y)				(((y)*ZOOM_Y_DIV)/ZOOM_Y)

#define SCALE_FIXED_IN_X(x)			((((x)>>FIXED_PRECISION)*ZOOM_X)/ZOOM_X_DIV)
#define SCALE_FIXED_IN_Y(y)			((((y)>>FIXED_PRECISION)*ZOOM_Y)/ZOOM_Y_DIV)

#define SCALE_FIXED_OUT_X(x)		((((x)<<FIXED_PRECISION)*ZOOM_X_DIV)/ZOOM_X)
#define SCALE_FIXED_OUT_Y(y)		((((y)<<FIXED_PRECISION)*ZOOM_Y_DIV)/ZOOM_Y)


// --- tile
// NOTE: Change bitshift for a div by the tile dimension if its not a power of 2
#define TO_TILE(var)					(var) >>= 4
#define TO_INT(var)						(var) >>= FIXED_PRECISION
#define TO_FIXED(var)					(var) <<= FIXED_PRECISION
#define VAR_FIXED_TO_TILE(var)			var >>= (FIXED_PRECISION + 4)

#define FIXED_TO_TILE(var)				(((var) / TILE_W ) >> FIXED_PRECISION)
#define PIXEL_TO_TILE(var)				((var) / TILE_H)
#define TILE_TO_PIXEL(var)				((var) * TILE_W)
#define TILE_TO_FIXED(var)				(((var) * TILE_H) << FIXED_PRECISION)


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// ASPRITE ASPRITE ASPRITE ASPRITE ASPRITE ASPRITE ASPRITE ASPRITE ASPRITE
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

#define FLAG_FLIP_X					(FLAG_FLIP_X)
#define FLAG_FLIP_Y					(FLAG_FLIP_Y)

#define FLAG_ADD_Z					(FLAG_USER0)
#define FLAG_DISPLAY_LIST			(FLAG_USER1)
#define FLAG_UNPAUSABLE				(FLAG_USER2)
#define FLAG_PAUSED					(FLAG_USER3)
#define FLAG_DONTDRAW				(FLAG_USER4)

#define FLAG_SET(renderer, flag)	renderer.m_flags |= flag;
#define FLAG_UNSET(renderer, flag)	renderer.m_flags &= ~flag;

#define VIEW_SIDE					(0)
#define VIEW_TOP					(1)

#define STACK_DATA_IDX(i)			((i*2)+0)		// index in s_trickData array [0-80[
#define STACK_CARD_IDX(i)			((i*2)+1)		// index of the card [0-4]


// --- Zones
#define getZoneId(zone)					((zone - ZONES::k_start) << 2)
#define getZoneX(zone)					s_zones[getZoneId(zone) + 0]
#define getZoneY(zone)					s_zones[getZoneId(zone) + 1]
#define getZoneW(zone)					s_zones[getZoneId(zone) + 2]
