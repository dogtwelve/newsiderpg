//  Implementation for sprites exported by AuroraGT editor.
//  Contains methods to handle displaying of strings.
//
//
//  Features:
//		* use ".bsprite" files (BSPRITE_v003, exported by AuroraGT v0.5.4 - SpriteEditor v0.6.4 or later)
//		* BSprite flags: BS_DEFAULT_MIDP2
//		* pixel formats supported:
//			8888	- A8 R8 G8 B8
//			4444	- A4 R4 G4 B4
//			1555	- A1 R5 G5 B5
//			0565	- R5 G6 B5
//		* data formats supported:
//			I2		- 8 pixels/byte encoding (max 2 colors)
//			I4		- 4 pixels/byte encoding (max 4 colors)
//			I16		- 2 pixels/byte encoding (max 16 colors)
//			I64RLE	- variable RLE compression (max 64 colors)
//			I127RLE	- fixed RLE compression (max 127 colors)
//			I256	- 1 pixel/byte encoding (max 256 colors)
//			I256RLE	- fixed RLE compression (max 256 colors)
//
//  Note:
//		
//
////////////////////////////////////////////////////////////////////////////////////////////////////

//
//////////////////////////////////////////////////////////////////////////////////////////////////////

//    ////////////////////////////////////////////////////////////////////////////////////////////////////

#include "ASprite.h"
#include "..\brew\SysUtil.h"




CASpriteImage::CASpriteImage(int bpp, int flag, int dataFormat, unsigned char *pWidth, unsigned char *pHeight, int colorKey, int paletteEntryNumber,
							 int nPalettes, PalettePixel **paletteData, int nModules, char *modulesData, int *modulesDataOffset)
							 //#endif
{
	//	MEMSET(this, 0, sizeof(CASpriteImage));

	switch (dataFormat)
	{
	case ENCODE_FORMAT_I64RLE:
		m_type = TYPE_RLE;
		m_palBits = CalculateBits(paletteEntryNumber);
		break;
	case ENCODE_FORMAT_I127RLE:
		m_type = TYPE_RLE;
		m_palBits = 7;
		break;
	case ENCODE_FORMAT_I256RLE:
		m_type = TYPE_RLE;
		m_palBits = 8;
		break;
	case ENCODE_FORMAT_I256:
		m_type = TYPE_INDEXED;		
		break;
	case ENCODE_FORMAT_I16:
		m_type = TYPE_INDEXED;
		bpp = 4;
		//m_palBits = 4;
		break;
	//case ENCODE_FORMAT_I4:
	//	m_type = TYPE_INDEXED;
	//	m_palBits = 2;
	//	break;
	//case ENCODE_FORMAT_I2:
	//	m_type = TYPE_INDEXED;
	//	m_palBits = 1;
	//	break;
	default:
		m_type = TYPE_INDEXED;
		//m_palBits = 8;
		break;
	}

	m_bpp = bpp;
	ASSERT(m_bpp == 8 || m_bpp == 4);
	m_flag = flag;
	if(m_flag & BBM_COLOR_KEY)
	{
		m_colorKey = colorKey;
	}
	m_paletteEntryNumber = paletteEntryNumber;
	m_nPalettes = nPalettes;
	m_paletteDataAll = paletteData;

	m_nModules = nModules;
	m_modulesPixel = (unsigned char*)modulesData;
	m_modulesPixelOffset = modulesDataOffset;

	//initialize, can be commented if you are sure SetCurrentData will be called before drawing
	int width = pWidth[0];
	int height = pHeight[0];
	m_modulesWidth = pWidth;
	m_modulesHeight = pHeight;
	SetSize(width, height, width);
	//	m_paletteData = m_paletteDataAll[0];
	m_paletteData = m_paletteDataAll[0];
	m_pixel = m_modulesPixel;
}

CASpriteImage::~CASpriteImage()
{
	//SAFE_DEL_ARRAY(m_modulesWidth);  ///seongjin---081031 no memory_del because MEMID
	//SAFE_DEL_ARRAY(m_modulesHeight);  ///seongjin---081031 no memory_del because MEMID
	//
	//SAFE_DEL_ARRAY_ARRAY(m_paletteDataAll,MAX_SPRITE_PALETTES);  ///seongjin---081031 no memory_del because MEMID
	//
	//SAFE_DEL_ARRAY(m_modulesPixel);  ///seongjin---081031 no memory_del because MEMID

	//SAFE_DEL_ARRAY(m_modulesPixelOffset);  ///seongjin---081031 no memory_del because MEMID
	//SAFE_DEL_ARRAY(m_paletteData);  ///seongjin---081031 no memory_del because MEMID

	//
	//SAFE_DEL_ARRAY(m_pixel);  ///seongjin---081031 no memory_del because MEMID
	
}

//void CASpriteImage::SetCurrentData(int paletteID, int moduleID, PalettePixel* p)
void CASpriteImage::SetCurrentData(int paletteID_2, bool bI64RLE, int paletteEntryNumber, int moduleID, PalettePixel* p)
{
	//SYZ, 2008/01/17, waiting for check
	//	ASSERT(moduleID < m_nModules);
	//	ASSERT(paletteID < m_nPalettes);
	
	//if (bI64RLE)
	//{
	//	ASSERT(m_type == TYPE_RLE);
	//	m_palBits = CalculateBits(paletteEntryNumber);
	//}

	int width = m_modulesWidth[moduleID];
	int height = m_modulesHeight[moduleID];
	SetSize(width, height, width * ((m_bpp + 7) / 8));
	m_pixel = m_modulesPixel + m_modulesPixelOffset[moduleID];
	//	m_paletteData = ((p == NULL)?m_paletteDataAll[paletteID]:p);
	m_paletteData = ((p == NULL)?m_paletteDataAll[paletteID_2]:p);
	//	m_paletteData = m_paletteDataAll + (paletteID << m_nPaletteOffset);
}
void CASpriteImage::SetScaleData(unsigned char* pixeldata, int width, int height)
{
	m_pixel = pixeldata;
	SetSize(width, height, width * ((m_bpp + 7) / 8));
}

////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef WIN32
int ASprite::spriteCounter; 
#endif

ASprite::ASprite()
{

#ifdef WIN32
		spriteCounter++;
#endif
		//ASprite();
	m_bWiseModule = true;
	_m_blendFrame = -1;//SangHo - Blend - 블랜딩 프레임 초기화

	SCROLL_DELAY_TIME = 3;
	
	_modules_w		= NULL;
	_modules_h		= NULL;

	_rectM_w		= NULL;
	_rectM_h		= NULL;
	_rectMColors	= NULL;
	
	_frames_nfm		= NULL;
	_frames_fm_start		= NULL;
	_frames_rc		= NULL;
	_frames_coll		= NULL;
	_fmodules		= NULL;
	_fmodules_palette = NULL;
	_anims_naf		= NULL;	
	_anims_af_start		= NULL;
	_aframes		= NULL;
	_map		= NULL;//point's point
	_pal		= NULL;//point's point
	//_pal_alpha		= NULL;
	_modules_data		= NULL;
	_modules_image		= NULL;
#ifndef USE_DIRECT_DRAW	
	_precalc_stack		= NULL;//point's point
#endif
	

	
	SCROLL_DELAY_TIME = 3;

	_pal_Copy = NULL;//SangHo - 복제한 팔렛트
	_pal_Back = NULL;//SangHo - 원본 팔렛트 포인터 임시저장소
}

ASprite::ASprite(byte* file, int offset)
{
	ASprite();

	Load(file, offset);
	SAFE_DEL_ARRAY(file);

}

    ////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef USE_DIRECT_DRAW
CImage* ASprite::GetModuleImage(int pal, int module)
    {
        if(_modules_image == NULL)
        {
            return NULL;
        }

        return _modules_image[pal * _nModules + module];
    }
#endif
    ////////////////////////////////////////////////////////////////////////////////////////////////////

void ASprite::Load(byte* file, int offset)
    {

        //try
        {
            //if (DEF.bDbgS) System.out.println("ASprite.Load("+file.length+" bytes, "+offset+")...");

            short  bs_version =(short)(file[offset++]&0xFF);
			bs_version += ((file[offset++]&0xFF)<<8);

            int bs_flags = ((file[offset++]&0xFF));
				bs_flags += ((file[offset++]&0xFF)<< 8);
                bs_flags += ((file[offset++]&0xFF)<<16);
                bs_flags += ((file[offset++]&0xFF)<<24);//4바이트 영역의 Sprite 속성을 받아온다


            //////////////////////////////
            //	if ((bs_flags & BS_MODULES) != 0)

            // Modules...
            _nModules = (file[offset++]&0xFF);
			_nModules +=  ((file[offset++]&0xFF)<<8);

            //if (DEF.bDbgS) System.out.println("nModules = " + _nModules);
            if (_nModules > 0)//SangHo - 스프라이트 파일내에 모듈의 갯수(2byte)
            {
                _modules_w  = GL_NEW byte[_nModules];
                _modules_h  = GL_NEW byte[_nModules];			
				
				int count_rect = 0 ; int temp_offset = offset ;
				
				for (int i = 0; i < _nModules; i++)
				{
				
					if ( (file[temp_offset]&0xFF) == 0xFF || (file[temp_offset]&0xFF) == 0xFE )
					{
						count_rect  += 1;
						temp_offset += 7;
					}
					else
					{
						temp_offset += 2;
					}
				}

				if(count_rect > 0)
				{//사각형 이미지(모듈 데이터)
					_rectM_w = GL_NEW byte[ count_rect ];
					_rectM_h = GL_NEW byte[ count_rect ];
					_rectMColors = GL_NEW int[ count_rect ];
				}
				count_rect = 0 ;

                for (int i = 0; i < _nModules; i++)
                {		
					if ( (file[offset]&0xFF) == 0xFF || (file[offset]&0xFF) == 0xFE ) // -> MD_RECT -> MD_FILL_RECT
					{
						_modules_w[i] = file[offset++];
						_modules_h[i] = (byte)count_rect;	
						
						_rectMColors[count_rect] = (file[offset]&0xFF) +
                            ((file[offset+1]&0xFF)<<8) + 
                            ((file[offset+2]&0xFF)<<16) + 
                            ((file[offset+3]&0xFF)<<24);
						offset += 4;
						//_rectMColors[count_rect] =  (aa<<24)|(rr<<16)|(gg<<8)|bb;//PaletteTransform(aa, rr, gg, bb, _paletteTransform);
						_rectM_w[count_rect] = file[offset++];
						_rectM_h[count_rect] = file[offset++];							
						count_rect++;
					}
					else
					{
						_modules_w[i] = file[offset++];
						_modules_h[i] = file[offset++];		
					}
                }
            }

            //////////////////////////////
            //	if ((bs_flags & BS_FRAMES) != 0)

            // FModules...
            _nFrames = (file[offset++]&0xFF);
			_nFrames +=  + ((file[offset++]&0xFF)<<8);
            //if (DEF.bDbgS) System.out.println("_nFrames = " + _nFrames);
            if (_nFrames > 0)
            {
				//nams
				if((bs_flags & BS_FM_PALETTE) != 0)
				{
					_fmodules_palette = GL_NEW byte [_nFrames];		// 4 : palette
				}

				int _fmodules_length = _nFrames<<2;
				_fmodules = GL_NEW char[_fmodules_length];


				if((bs_flags & BS_FM_PALETTE) != 0)
				{
					int count = 0;
					int	palette_count = 0;
					for (int i = 0; i < _nFrames; ++i) 
					{
						_fmodules[count++] = file[offset++];
						_fmodules[count++] = file[offset++];
						_fmodules[count++] = file[offset++];
						_fmodules_palette[palette_count++] = file[offset++]; 
						_fmodules[count++] = file[offset++];
					}
				}
				else
				{
					int _fmodules_length = _nFrames<<2;
					_fmodules = GL_NEW char[_fmodules_length];
					//System.arraycopy(file, offset, _fmodules, 0, _fmodules_length);
					arraycopy((char*)file, offset, _fmodules, 0, _fmodules_length);
					offset += _fmodules_length;
				}
            }

			// Rect - Add by 2008.12.30 Lee SangHo ////////////////////////////////////////////////////////////////■1/4
			if ((bs_flags & BS_FRAME_RECTS) != 0) 
			{// Rect  (충돌체크-Conflict Check) - 데이터 저장 영역 생성,저장
				int count = (file[offset++]&0xFF);
				count += (file[offset++]&0xFF)<<8;//충돌영역 사각형의 Total 갯수

				_frames_rects = GL_NEW  char[count * 4];//Total 갯수 * 4(X,Y,W,H)
				arraycopy((char*)file, offset, _frames_rects, 0, count * 4);//Rect값 (저장)복사
				offset += count * 4;
			}


            // Frames...
            unsigned short nFrames = (file[offset++]&0xFF);
			nFrames += ((file[offset++]&0xFF)<<8);
            //if (DEF.bDbgS) System.out.println("nFrames = " + nFrames);
            if (nFrames > 0)
            {
                _frames_nfm      = GL_NEW  byte[nFrames];
                //	_frames_nfm      = GL_NEW short[nFrames];
                _frames_fm_start = GL_NEW short[nFrames];

				


				// Rect - Add by 2008.12.30 Lee SangHo ////////////////////////////////////////////////////////////////■2/4
				if ((bs_flags & BS_FRAME_RECTS) != 0) 
				{// Rect  (충돌체크-Conflict Check) - 초기화
					_frames_rects_start_length = nFrames + 1;//MAX 인덱스 기록 , 즉 프레임 갯수(+1은 값 구하는방식이 (N+1)-(N) 이기 때문에 종료값 존재해야함)
					_frames_rects_start = GL_NEW short[_frames_rects_start_length];//각 프레임의 Rect 시작점 저장공간 할당 
				}
				short frames_rects_offset = 0;//Rect 시작점




				for (int i = 0; i < nFrames; i++)
                {
					// Frames
                    _frames_nfm[i]      = file[offset++]; 
					if (!ALWAYS_BS_NFM_1_BYTE) offset++;
                    //	_frames_nfm[i]      = (short)((file[offset++]&0xFF) + ((file[offset++]&0xFF)<<8));
                    //_frames_fm_start[i] = (short)((file[offset++]&0xFF) + ((file[offset++]&0xFF)<<8));
					_frames_fm_start[i] = (file[offset++]&0xFF);
					_frames_fm_start[i] += (file[offset++]&0xFF)<<8;


					// Rect - Add by 2008.12.30 Lee SangHo ////////////////////////////////////////////////////////////////■3/4
					if ((bs_flags & BS_FRAME_RECTS) != 0)
					{// Rect  (충돌체크-Conflict Check) - Rect 시작점 저장
						_frames_rects_start[i] = frames_rects_offset;
						frames_rects_offset += file[offset++];//이번 프레임에서 Rect가 몇개인가? 없다면 0 
					}




                }


				// Rect - Add by 2008.12.30 Lee SangHo ////////////////////////////////////////////////////////////////■4/4
				if ((bs_flags & BS_FRAME_RECTS) != 0) 
				{// Rect  (충돌체크-Conflict Check)  -  마지막 프레임의 Rect 을 더한 갯수값 (갯수 구하는방식이 (N+1)-(N) 이기 때문에 종료값 으로 존재)
					_frames_rects_start[_frames_rects_start_length - 1] = frames_rects_offset;
				}


				// /*Rect검출코드*/for(int xx=0 ; xx < frames_rects_offset*4 ; xx+=4)	DBGPRINTF("<충돌Rect> \tX:%d \tY:%d \tW:%d \tH:%d \n", _frames_rects[xx+0] , _frames_rects[xx+1] , _frames_rects[xx+2] , _frames_rects[xx+3]);





                if (!ALWAYS_BS_SKIP_FRAME_RC)
                {
                    if ((bs_flags & BS_SKIP_FRAME_RC) != BS_SKIP_FRAME_RC) {
                        if (USE_PRECOMPUTED_FRAME_RECT)
                        {
                            // Bound rect for each frame... include
                            int nFrames4 = nFrames<<2;
                            _frames_rc = GL_NEW char[nFrames4];
                            for (int i = 0; i < nFrames4; i++)
                                _frames_rc[i] = file[offset++];
                        }
                        else
                            offset += (nFrames<<2);
                    }
                }
                else
                {
                    if (USE_PRECOMPUTED_FRAME_RECT)
                    {
                        // TODO: precompute frame rc
                    }
                }

                if (!ALWAYS_BS_FRAME_COLL_RC)
                {
                    if ((bs_flags & BS_FRAME_COLL_RC) == BS_FRAME_COLL_RC) {
                        //if (DEF.bDbgS) System.out.println("use BS_FRAME_COLL_RC");

                        // Collision rect for each frame...
                        int nFrames4 = nFrames<<2;
                        _frames_coll = GL_NEW char[nFrames4];
                        for (int i = 0; i < nFrames4; i++)
                            _frames_coll[i] = file[offset++];
                    }
                }


            }

            //////////////////////////////
            //	if ((bs_flags & BS_ANIMS) != 0)

            // AFrames...
            unsigned short nAFrames = (file[offset++]&0xFF);
			nAFrames += ((file[offset++]&0xFF)<<8);
            //if (DEF.bDbgS) System.out.println("nAFrames = " + nAFrames);
            if (nAFrames > 0)
            {
                int _aframes_length = nAFrames*5;
				_aframes = GL_NEW char[_aframes_length];
                //System.arraycopy(file, offset, _aframes, 0, _aframes.length);
				arraycopy(file, offset, (byte*)_aframes, 0, _aframes_length);
                offset += _aframes_length;
            }

            // Anims...
            unsigned short nAnims = (file[offset++]&0xFF);
			nAnims += ((file[offset++]&0xFF)<<8);
            //if (DEF.bDbgS) System.out.println("nAnims = " + nAnims);
            if (nAnims > 0)
            {
                _anims_naf      = GL_NEW  byte[nAnims];
                //	_anims_naf      = GL_NEW short[nAnims];
                _anims_af_start = GL_NEW short[nAnims];

                for (int i = 0; i < nAnims; i++)
                {
                    _anims_naf[i]      = file[offset++]; 
					if (!ALWAYS_BS_NAF_1_BYTE) offset++;
                    //	_anims_naf[i]      = (short)((file[offset++]&0xFF) + ((file[offset++]&0xFF)<<8));
                    _anims_af_start[i] = (file[offset++]&0xFF);
					_anims_af_start[i] += ((file[offset++]&0xFF)<<8);
                }
            }

            //////////////////////////////

            if (_nModules <= 0)
            {
                //if (DEF.bErr) System.out.println("WARNING: sprite with num modules = "+_nModules);
                Gc();
                return;
            }

            //////////////////////////////


			unsigned short colorKey = 0xF81F;


            // Pixel format (must be one of supported SPRITE_FORMAT_xxxx)...
            //short _pixel_format = (short)((file[offset++]&0xFF) + ((file[offset++]&0xFF)<<8));
			unsigned short _pixel_format = file[offset++]&0xFF;
			_pixel_format += (file[offset++]&0xFF)<<8;
            //if (DEF.bDbgS) System.out.println("_pixel_format = 0x" + Integer.toHexString(_pixel_format));

            // Number of palettes...
            _palettes = file[offset++]&0xFF;//SangHo - 팔렛트의 갯수를 저장
            //if (DEF.bDbgS) System.out.println("_palettes = " + _palettes);

            // Number of colors...
            _colors = file[offset++]&0xFF;//SangHo - 팔렛트내의 컬러수를 저장
            
			if (USE_ENCODE_FORMAT_I256)
                if (_colors == 0) _colors = 256;
            //if (DEF.bDbgS) System.out.println("colors = " + colors);

            // Palettes...
            //Robust
			//_pal = GL_NEW int[MAX_SPRITE_PALETTES][];
			_pal = GL_NEW PalettePixel*[MAX_SPRITE_PALETTES];//SangHo - 16개의 팔렛트 포인터를 만든다		
            for (int p = 0; p < _palettes; p++)
            {
                _pal[p] = GL_NEW PalettePixel[_colors];//SangHo - 팔렛트 갯수 만큼의  팔렛트 저장소를 만든뒤 포인터를 넘긴다

                // HINT: Sort these pixel formats regarding how often are used by your game!
                if ((_pixel_format == PIXEL_FORMAT_8888) && USE_PIXEL_FORMAT_8888)
                {
                    for (int c = 0; c < _colors; c++)
                    {
                        //int _8888  = ((file[offset++]&0xFF)    );	// B
                        //_8888 += ((file[offset++]&0xFF)<< 8);	// G
                        //_8888 += ((file[offset++]&0xFF)<<16);	// R
                        //_8888 += ((file[offset++]&0xFF)<<24);	// A

                        //if ((_8888 & 0xFF000000) != 0xFF000000)
                        //    _alpha = true;

                        //_pal[p][c] = _8888;

					int _8888  = ((file[offset++]&0xFF)    );	// B
					_8888 += ((file[offset++]&0xFF)<< 8);	// G
					_8888 += ((file[offset++]&0xFF)<<16);	// R
					_8888 += ((file[offset++]&0xFF)<<24);	// A

					//_pal[p][c] = CNativeGraphics::ToNativeColorS(_8888);;
					_pal[p][c] = ((_8888&0xF80000)>>8) | ((_8888&0x00FC00)>>5) | ((_8888&0x0000F8)>>3);
					if ((_8888 & 0xFF000000) != 0xFF000000)
					{
						_alpha = true;
						//_pal_alpha[p] = CNativeGraphics::ToNativeColorS(_8888);;
					}

                    }
                }
                else
                    if ((_pixel_format == PIXEL_FORMAT_4444) && USE_PIXEL_FORMAT_4444)
                    {
                        for (int c = 0; c < _colors; c++)
                        {
                            int _4444  = ((file[offset++]&0xFF)   );
                            _4444 += ((file[offset++]&0xFF)<<8);

                            if ((_4444 & 0xF000) != 0xF000)
                                _alpha = true;

                            // 4444 -> 8888
                            //_pal[p][c] = ((_4444 & 0xF000) << 16) | ((_4444 & 0xF000) << 12) |	// A
                            //    ((_4444 & 0x0F00) << 12) | ((_4444 & 0x0F00) <<  8) |	// R
                            //    ((_4444 & 0x00F0) <<  8) | ((_4444 & 0x00F0) <<  4) |	// G
                            //    ((_4444 & 0x000F) <<  4) | ((_4444 & 0x000F)      );	// B
							_pal[p][c] = ((_4444 & 0x0F00) << 4) | ((_4444 & 0x00F0) << 3) | ((_4444 & 0x000F) << 1);
						//if ((_4444 & 0xF000) != 0xF000)
						//{
						//	_alpha = true;
						//	_pal_alpha[p] = 0xF000;
						//}
                        }
                    }
                    else
                        if ((_pixel_format == PIXEL_FORMAT_1555) && USE_PIXEL_FORMAT_1555)
                        {//SangHo -  팔렛트 공간에 순차적으로 값을 저장
                            for (int c = 0; c < _colors; c++)
                            {
                                int _1555  = ((file[offset++]&0xFF)   );
                                _1555 += ((file[offset++]&0xFF)<<8);

                                int a = 0xFF000000;
                                if ((_1555 & 0x8000) != 0x8000)
                                {
                                    a = 0;
                                    _alpha = true;
                                }

                                // 1555 -> 8888
                                _pal[p][c] = a |						// A
                                    ((_1555 & 0x7C00) << 1) |	// R
                                    ((_1555 & 0x03E0) << 1) |	// G
                                    ((_1555 & 0x001F) );	// B

                            }
                        }
                        else
                            if ((_pixel_format == PIXEL_FORMAT_0565) && USE_PIXEL_FORMAT_0565)
                            {
                                for (int c = 0; c < _colors; c++)
                                {
                                    int _0565  = ((file[offset++]&0xFF)   );
                                    _0565 += ((file[offset++]&0xFF)<<8);

                                    int a = 0xFF000000;
                                    if (_0565 == 0xF81F)
                                    {
                                        a = 0;
                                        _alpha = true;
                                    }

                                    // 0565 -> 8888
                                    _pal[p][c] = a |						// A
                                        ((_0565 & 0xF800) << 8) |	// R
                                        ((_0565 & 0x07E0) << 5) |	// G
                                        ((_0565 & 0x001F) << 3);	// B
                                }
                            }
            }


            //////////////////////////////

			//if (_modules_image == NULL)
			//{
			//  _modules_image = GL_NEW CImage*[_palettes*_nModules];
			//	_modules_image_length = _palettes*_nModules;
			//}

            // Data format (must be one of supported ENCODE_FORMAT_xxxx)...
            _data_format = (file[offset++]&0xFF);
			_data_format += ((file[offset++]&0xFF)<<8);
            //if (DEF.bDbgS) System.out.println("_data_format = 0x" + Integer.toHexString(_data_format));

            if ((_data_format == ENCODE_FORMAT_I64RLE) && USE_ENCODE_FORMAT_I64RLE)
            {
                int clrs = _colors - 1;
                _i64rle_color_mask = 1;
                _i64rle_color_bits = 0;
                while (clrs != 0)
                {
                    clrs >>= 1;
                    _i64rle_color_mask <<= 1;
                    _i64rle_color_bits++;
                }
                _i64rle_color_mask--;
            }

            // Graphics data...
            if (_nModules > 0)
            {
				_modules_data_pal = GL_NEW char[_nModules];//module 데이터의 팔렛트
                _modules_data_off = GL_NEW int[_nModules+1];//module 데이터의 offset SangHo -   +1을 한 이유는 마지막 값의 길이를 알기위해서

                int len = 0;
                int off = offset;

                for (int m = 0; m < _nModules; m++)
                {//초기에 모듈의 갯수만큼에 해당하는 (각각 short 형에 해당하는 크기)크기가 저장되어 있다
                    // Image data for the module...
                    int size = (file[off++]&0xFF);
					size += ((file[off++]&0xFF)<<8);

					_modules_data_pal[m] = -1;//모듈이 특정 팔렛트를 써야할 경우를 위해서 지정되는 수치
                    _modules_data_off[m] = len;
                    off += size;
                    len += size;
                }
				
				_modules_data_off[_nModules] = len;//SangHo - 마지막 값의 길이를 알기위해서 Module 갯수+1개의 배열에 마지막 위치 값을 넣는다
				_modules_data = GL_NEW byte[len];//모듈 총 크기에 해당하는 메모리를 할당한다


				///////////////////////////////////////////////////////////////////////////////////이미지 저장하는부분
                for (int m = 0; m < _nModules; m++)
                {
                    // Image data for the module...
                    int size = (file[offset++]&0xFF);
					size += ((file[offset++]&0xFF)<<8);
                    //if (DEF.bDbgS) System.out.println("frame["+m+"] size = " + size);
                    //System.arraycopy(file, offset, _modules_data, _modules_data_off[m]&0xFFFF, size);
                    arraycopy(file, offset, _modules_data, _modules_data_off[m]&0xFFFF, size);
					offset += size;
                }
            }

#ifdef USE_DIRECT_DRAW
	int flag = !_alpha ? BBM_PALETTE : (BBM_PALETTE | BBM_COLOR_KEY);
	_modules_image = GL_NEW CASpriteImage(8, flag, _data_format, (unsigned char *)_modules_w, (unsigned char *)_modules_h,
	colorKey, _colors, _palettes, _pal, _nModules, (char*)_modules_data, _modules_data_off);
	
	//DBGPRINTF("+++++++++++new %d =============== %d \n", &_modules_image , *((signed long *)_modules_image-2));

#endif

            //////////////////////////////
            // module mappings
            if (USE_MODULE_MAPPINGS)
            {
                _map = GL_NEW int*[MAX_MODULE_MAPPINGS];
                //	_mappings = 0;
                _cur_map = -1;
            }

            //////////////////////////////

            Gc();

        }

    }


	void ASprite::ClearCompressedImageData ()
    {
        //_modules_data = NULL;
        //_modules_data_off = NULL;
		SAFE_DEL_ARRAY(_modules_data);
		SAFE_DEL_ARRAY(_modules_data_off);
		SAFE_DEL_ARRAY(_modules_data_pal);
        Gc();
    }

	void ASprite::ClearTemporaryBuffer ()
    {
        //temp = NULL;
		
        Gc();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // pal = palette to be initailized
    // m1 = first module
    // m2 = last module (-1 -> to end)
    // pal_copy = mapping to another palette (-1 -> build)

	void ASprite::BuildCacheImages(int pal, int m1, int m2, int pal_copy)
    {//SangHo - 모듈이미지를 생성하는 부분
#ifndef USE_DIRECT_DRAW      
		if (_nModules == 0) return;
        if (m2 == -1)
            m2 = _nModules - 1;

        if (_modules_image == NULL)
#ifdef USE_PNG
			_modules_image = GL_NEW CImage[pal*_nModules];
		_modules_image_length = pal*_nModules;
#else
		{
			SAFE_DEL_ARRAY_OBJ(_modules_image,_modules_image_length);
			_modules_image = GL_NEW CImage*[_palettes*_nModules];
			_modules_image_length = _palettes*_nModules;
		}
#endif


        if (pal_copy >= 0)
        {
            for (int i = m1; i <= m2; i++)
                _modules_image[pal * _nModules + i] = _modules_image[pal_copy * _nModules + i];
        }
        else
        {
            int old_pal = _crt_pal;
            _crt_pal = pal;
            int total_area, total_size;
            //long mem;
            //if (DEF.bDbgO) total_area = 0;
            //if (DEF.bDbgO) total_size = 0;
			if (bDbgO) total_area = 0;
            if (bDbgO) total_size = 0;
            Gc();
            //if (DEF.bDbgO) mem = Runtime.getRuntime().freeMemory();
            for (int i = m1; i <= m2; i++)
            {
				
			//	if (m_bWiseModule && _modules_image[pal*i] != null)
			//	{
			//		continue;
			//	}				
                int sizeX = _modules_w[i]&0xFF;
                int sizeY = _modules_h[i]&0xFF;
								
				if (sizeX <= 0 || sizeY <= 0) continue;

                short* image_data = DecodeImage(i, 0);
                if (image_data == NULL) continue;

                bool bAlpha = false;
                int size = sizeX * sizeY;
                //if (DEF.bDbgO) total_area += size;
				if (bDbgO) total_area += size;
                for (int ii = 0; ii < size; ii++)
                {
                    if ((image_data[ii] & 0xFF000000) != 0xFF000000)
                    {
                        bAlpha = true;
                        break;
                    }
                }
                //if (DEF.bDbgO) total_size += ((bAlpha & DEF.bEmu) ? (size*3) : (size*2));
				if (bDbgO) total_size += ((bAlpha & bEmu) ? (size*3) : (size*2));
                //_modules_image[pal * _nModules + i] = CImage.createRGBImage(image_data, sizeX, sizeY, bAlpha);
                //_modules_image[pal * _nModules + i] = GL_NEW CMutableImage(sizeX, sizeY, 16);

				SAFE_DEL(_modules_image[pal * _nModules + i]);
				_modules_image[pal * _nModules + i] = GL_NEW CMutableImage(sizeX, sizeY, 2*sizeX, 16, image_data);
				_modules_image[pal * _nModules + i]->EnableColorKey(true);
				_modules_image[pal * _nModules + i]->SetColorKey(0xf81f);
                //SAFE_DEL_ARRAY(image_data);// = NULL;
				image_data = NULL;
            }
            Gc();
            //if (DEF.bDbgI) mem -= Runtime.getRuntime().freeMemory();
            //if (DEF.bDbgI) System.out.println(" area = " + total_area + " pixels");
            //if (DEF.bDbgI) System.out.println(" size = " + total_size + " bytes");
            //if (DEF.bDbgI) System.out.println(" mem used = " + mem + " bytes");
            //if (DEF.bDbgI) System.out.println(" images = " + (m2 - m1 + 1));
            //if (DEF.bDbgI) System.out.println(" total overhead = " + (mem - total_size) + " bytes");
            //if (DEF.bDbgI) System.out.println(" image overhead = " + ((mem - total_size) / (m2 - m1 + 1)) + " bytes");
            _crt_pal = old_pal;
        }
        Gc();

		SAFE_DEL_ARRAY(_modules_data);
#endif
		
    }

#ifdef USE_PNG

    
	
	
	
	


	

	



#endif

	//tunadw 여러 팔레트를 로딩 한다 가지고 만든다
	void ASprite::enablePrecalcImage_PalLoading( int palNumber , bool useStack)
	{
#ifndef USE_DIRECT_DRAW
		if ( !useStack )
		{
			BuildCacheImages( palNumber, 0, -1, -1 );
		}
		else
		{
			_precalc_stack_max = STACK_SIZE;
			_precalc_stack = GL_NEW int[STACK_SIZE];
			SAFE_DEL_ARRAY_OBJ(_modules_image,_modules_image_length);
			_modules_image = GL_NEW CImage*[_palettes*_nModules];
			_modules_image_length = _palettes*_nModules;
		}
#endif

	}

	void ASprite::enablePrecalcImage( int palTag, bool useStack )
    {
#ifndef USE_DIRECT_DRAW
        int mask = 1;

        if ( !useStack )
        {
            for(int n=0; n<MAX_SPRITE_PALETTES; n++)
            {
                if((palTag & mask) != 0)
                {
                    BuildCacheImages( n, 0, -1, -1 );
                }

                mask <<= 1;
            }

            ClearCompressedImageData();
        }
        else
        {
            _precalc_stack_max = STACK_SIZE;
            _precalc_stack = GL_NEW int[STACK_SIZE];
			SAFE_DEL_ARRAY_OBJ(_modules_image,_modules_image_length);
            _modules_image = GL_NEW CImage*[_palettes*_nModules];
			_modules_image_length = _palettes*_nModules;
        }     
#endif
    }

	void ASprite::clearPrecalcImage()
    {
#ifndef USE_DIRECT_DRAW
        for (int i = _modules_image_length-1; i >= 0; i--)
        {
		SAFE_DEL(_modules_image[i]);
            if ( i < STACK_SIZE )
                _precalc_stack[i] = 0;
        }
        Gc();
#endif
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /*
    public String toString()
    {
    String str = GL_NEW String();

    if (DEF.bDbgM)
    {
    // Memory usage...
    int nModulesMem = 0;
    for (int i = 0; i < _nModules; i++)
    nModulesMem += (_modules_w[i]&0xFF) * (_modules_h[i]&0xFF);
    str = "encoded/decoded: " + _modules_data.length + "/" + ((DEF.bEmu ? 3 : 2) * nModulesMem);
    }

    return str;
    }
    */
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Module Mapping...

    //private void MODULE_MAPPING___() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::SetModuleMapping(int map, byte* mmp)
    {
		//Robust, not be used


        ////	if (DEF.bASSERT) DBG.ASSERT(map >= 0 && map < _mappings, "map >= 0 && map < _mappings");
        //if (_map[map] == NULL)
        //{
        //    _map[map] = GL_NEW int[_nModules];
        //    for (int i = 0; i < _nModules; i++)
        //        _map[map][i] = i;
        //}
        //if (mmp == NULL) return;
        //int off = 0;
        //while (off < mmp.length)
        //{
        //    int i1 = ((mmp[off++] & 0xFF) + ((mmp[off++] & 0xFF) << 8));
        //    int i2 = ((mmp[off++] & 0xFF) + ((mmp[off++] & 0xFF) << 8));
        //    _map[map][i1] = i2;
        //}
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::ApplyModuleMapping(int dst_pal, int src_pal, byte* mmp)
    {
		//Robust, not be used


        //int off = 0;
        //while (off < mmp.length)
        //{
        //    int i1 = ((mmp[off++] & 0xFF) + ((mmp[off++] & 0xFF) << 8));
        //    int i2 = ((mmp[off++] & 0xFF) + ((mmp[off++] & 0xFF) << 8));
        //    _modules_image[dst_pal * _nModules + i1] = _modules_image[src_pal * _nModules + i2];
        //}
        //Gc();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::SetCurrentMMapping(int map)	{ _cur_map = map; }
	int ASprite::GetCurrentMMapping()			{ return _cur_map; }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::___MODULE_MAPPING() {}

    // ... Module Mapping
    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetAFrameTime(int anim, int aframe)
    {
        //	int af = (_anims_af_start[anim] + aframe);
        //	return _aframes[((af<<2) + af + 1)] & 0xFF;
        return _aframes[(_anims_af_start[anim] + aframe) * 5 + 1] & 0xFF;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetAFrames(int anim)
    {
        return _anims_naf[anim]&0xFF;
        //	return _anims_naf[anim]&0xFFFF;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetFModules(int frame)
    {
        return _frames_nfm[frame]&0xFF;
        //	return _frames_nfm[frame]&0xFFFF;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetModuleWidth(int module)
    {
        return _modules_w[module]&0xFF;
    }

	int ASprite::GetModuleHeight(int module)
    {
        return _modules_h[module]&0xFF;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////


	int ASprite::GetFrameX(int frame)
	{
		return _frames_rc[frame*4 ];
	}

	int ASprite::GetFrameY(int frame)
	{
		return _frames_rc[frame*4 + 1];
	}



	int ASprite::GetFrameWidth(int frame)
    {
        return _frames_rc[frame*4 + 2]&0xFF;
    }

	int ASprite::GetFrameHeight(int frame)
    {
        return _frames_rc[frame*4 + 3]&0xFF;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetFrameCollisionLeft(int frame)
    {
        return _frames_coll[frame*4 + 0];
    }

	int ASprite::GetFrameCollisionTop(int frame)
    {
        return _frames_coll[frame*4 + 1];
    }

	int ASprite::GetFrameCollisionRight(int frame)
    {
        return _frames_coll[frame*4 + 2];
    }

	int ASprite::GetFrameCollisionBottom(int frame)
    {
        return _frames_coll[frame*4 + 3];
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetFrameModuleX(int frame, int fmodule)
    {
        int off = (_frames_fm_start[frame] + fmodule) << 2;
        return _fmodules[off+1];
    }

	int ASprite::GetFrameModuleY(int frame, int fmodule)
    {
        int off = (_frames_fm_start[frame] + fmodule) << 2;
        return _fmodules[off+2];
    }

	int ASprite::GetFrameModuleWidth(int frame, int fmodule)
    {
        int off = (_frames_fm_start[frame] + fmodule) << 2;

        int index = _fmodules[off]&0xFF;
		if (USE_INDEX_EX_FMODULES)
		{//SangHo - 프레임에서 모듈 인덱스 참조할때 - 로테이션 함수의 상위 2비트를 프레임의 부족한 부분을 메꿔주는 용도로 사용한다
			index |= ((_fmodules[off+3]&0xFF&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
		}

        return _modules_w[index]&0xFF;
    }

	int ASprite::GetFrameModuleHeight(int frame, int fmodule)
    {
        int off = (_frames_fm_start[frame] + fmodule) << 2;

        int index = _fmodules[off]&0xFF;
		if (USE_INDEX_EX_FMODULES)
		{//SangHo - 프레임에서 모듈 인덱스 참조할때 - 로테이션 함수의 상위 2비트를 프레임의 부족한 부분을 메꿔주는 용도로 사용한다
			index |= ((_fmodules[off+3]&0xFF&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
		}

        return _modules_h[index]&0xFF;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetAnimFrame(int anim, int aframe)
    {
        int off = (_anims_af_start[anim] + aframe) * 5;
		int frame = _aframes[off] & 0xFF;
		if(USE_INDEX_EX_AFRAMES)
		{//SangHo - flags의 상위 2비트를 "프레임"Index의 상위2비트로 메꿔주는 용도로 사용(2+8bit = MAX:1024)
			frame |= ((_aframes[off + 4] & FLAG_INDEX_EX_MASK) << INDEX_EX_SHIFT);
		}

        return frame;
    }

	//int GetAnimFrame()

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::GetAFrameRect(int* rc, int anim, int aframe, int posX, int posY, int flags, int hx, int hy)
	{//SangHo ?  frame 번째 프레임을 posX,posY 기준으로 좌상좌표와 우하좌표를 rc 로 리턴한다

     //   	System.out.println("GetAFrameRect(rc, "+anim+", "+aframe+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");
        int off = (_anims_af_start[anim] + aframe) * 5;
        int frame = _aframes[off]&0xFF;
        if (USE_INDEX_EX_AFRAMES)//SangHo - flags의 상위 2비트를 "프레임"Index의 상위2비트로 메꿔주는 용도로 사용(2+8bit = MAX:1024)
            frame |= ((_aframes[off+4]&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
        if ((flags & FLAG_OFFSET_AF) != 0)
        {
            if ((flags & FLAG_FLIP_X) != 0)	hx += _aframes[off+2];
            else							hx -= _aframes[off+2];
            if ((flags & FLAG_FLIP_Y) != 0)	hy += _aframes[off+3];
            else							hy -= _aframes[off+3];
        }
        //	if ((flags & FLAG_FLIP_X) != 0)	hx += _frames_w[frame]&0xFF;
        //	if ((flags & FLAG_FLIP_Y) != 0)	hy += _frames_h[frame]&0xFF;
        GetFrameRect(rc, frame, posX, posY, flags ^ (_aframes[off+4]&0x0F), hx, hy);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::GetFrameRect(int* rc, int frame, int posX, int posY, int flags, int hx, int hy)
	{//SangHo ?  posX,posY 기준인 anim 번째 애니메이션의 aframe 인덱스의 프레임의 좌상좌표와 우하좌표를 리턴한다

        //	System.out.println("GetFrameRect(rc, "+frame+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");

        if (USE_PRECOMPUTED_FRAME_RECT)
        {//SangHo - 미리 계산된 Rect 값을 쓴다 (프레임의 시작,너비,높이값이 BSprite 안에 들어있음) 
            int frame4 = frame<<2;
            int fx = _frames_rc[frame4++];
            int fy = _frames_rc[frame4++];
            int fw = _frames_rc[frame4++]&0xFF;
            int fh = _frames_rc[frame4++]&0xFF;

            if ((flags & FLAG_FLIP_X) != 0)	hx += fx + fw;
            else							hx -= fx;
            if ((flags & FLAG_FLIP_Y) != 0)	hy += fy + fh;
            else							hy -= fy;

            rc[0] = posX - (hx << FIXED_PRECISION);
            rc[1] = posY - (hy << FIXED_PRECISION);
            rc[2] = rc[0] + (fw << FIXED_PRECISION);
            rc[3] = rc[1] + (fh << FIXED_PRECISION);
        }
        else
        {
            // old
            //			int fx = (255 << DEF.FIXED_PRECISION);
            //			int fy = (255 << DEF.FIXED_PRECISION);
            // GL_NEW
            int fx = 0;
            int fy = 0;
            int fw = 0;
            int fh = 0;

            int nFModules = _frames_nfm[frame]&0xFF;
            //	int nFModules = _frames_nfm[frame]&0xFFFF;
            for (int fmodule = 0; fmodule < nFModules; fmodule++)
            {
                GetFModuleRect(rc, frame, fmodule, posX, posY, flags, hx, hy);
                // old
                //				if (rc[0] < fx)			fx = rc[0];
                //				if (rc[1] < fy)			fy = rc[1];
                //				if (rc[2] > fx + fw)	fw = rc[2] - fx;
                //				if (rc[3] > fy + fh)	fh = rc[3] - fy;
                // GL_NEW
                if (rc[0] < fx)
                {
                    fw = (fx+fw) - rc[0];
                    fx = rc[0];
                }

                if (rc[1] < fy)
                {
                    fh = (fy+fh) - rc[1];
                    fy = rc[1];
                }

                if (rc[2] > fx + fw)
                {
                    fw = rc[2] - fx;
                }

                if (rc[3] > fy + fh)
                {
                    fh = rc[3] - fy;
                }
            }

            hx <<= FIXED_PRECISION;
            hy <<= FIXED_PRECISION;

            if ((flags & FLAG_FLIP_X) != 0)	hx += fx + fw;
            else							hx -= fx;
            if ((flags & FLAG_FLIP_Y) != 0)	hy += fy + fh;
            else							hy -= fy;

            rc[0] = posX - hx;
            rc[1] = posY - hy;
            rc[2] = rc[0] + fw;
            rc[3] = rc[1] + fh;
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::GetFModuleRect(int* rc, int frame, int fmodule, int posX, int posY, int flags, int hx, int hy)
	{//SangHo ?  원점 기준으로 frame 번째 프레임의 fmodule 인덱스의 모듈 좌상좌표와 우하좌표를 리턴한다

        rc[0] = GetFrameModuleX(frame, fmodule) << FIXED_PRECISION;
        rc[1] = GetFrameModuleY(frame, fmodule) << FIXED_PRECISION;
        rc[2] = rc[0] + (GetFrameModuleWidth(frame, fmodule) << FIXED_PRECISION);
        rc[3] = rc[1] + (GetFrameModuleHeight(frame, fmodule) << FIXED_PRECISION);

        //	System.out.println("GetFModuleRect(rc, "+frame+", "+fmodule+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::GetModuleRect(int* rc, int module, int posX, int posY)
	{//SangHo ?  module 번째 모듈을 posX,posY 기준으로 좌상좌표와 우하좌표를 rc 로 리턴한다  

        //	System.out.println("GetModuleRect(rc, "+module+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+")");
        rc[0] = posX;
        rc[1] = posY;
        rc[2] = posX + ((_modules_w[module]&0xFF) << FIXED_PRECISION);
        rc[3] = posY + ((_modules_h[module]&0xFF) << FIXED_PRECISION);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
/*SangHo - 불필요하다고 판단
    // Added for backwards-compatibility purposes -cmm
	void ASprite::SetCurrentAnimation(int anim, bool loop)
    {
        SetCurrentAnimation(0, anim, loop);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::ClearAnimation(int animIndex,bool loop)
	{
        _current_frame[animIndex] = 0;
        _current_frame_time[animIndex] = 0;
        _is_looping[animIndex] = loop;
		_is_aniDone[animIndex] = false;
		_is_anisuspend[animIndex] = false;	//20070903
	}
	void ASprite::SetCurrentAnimation(int animIndex, int anim, bool loop)
	{//SangHo ? 에니메이션 넘버(_current_animation), 프레임 넘버(_current_frame),반복 횟수(_current_frame_time)
		//SangHo ? 루프 여부(_is_looping), 정지 여부(_is_aniDone),일시정지 여부(_is_anisuspend) 주요 6개 정보 저장




        //if (animIndex >= MAX_ANIMATION_INSTANCES) {
        //    if (bDbgS) System.out.println("MAX_ANIMATION_INSTANCES is too small!");
        //}

        _current_animation[animIndex] = anim;
        _current_frame[animIndex] = 0;
        _current_frame_time[animIndex] = 0;
        _is_looping[animIndex] = loop;
		_is_aniDone[animIndex] = false;
		_is_anisuspend[animIndex] = false;	//20070903
    }

	void ASprite::SetCurrentAnimationEX(int animIndex, int anim, bool loop)
	{
		//if (animIndex >= MAX_ANIMATION_INSTANCES) {
		//    if (bDbgS) System.out.println("MAX_ANIMATION_INSTANCES is too small!");
		//}

		_current_animation[animIndex] = anim;
		//_current_frame[animIndex] = 0;
		//_current_frame_time[animIndex] = 0;
		_is_looping[animIndex] = loop;
		_is_aniDone[animIndex] = false;
		_is_anisuspend[animIndex] = false;	//20070903
	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // Added for backwards-compatibility purposes -cmm
	int ASprite::GetCurrentAnimation()
    {
        return GetCurrentAnimation(0);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetCurrentAnimation(int animIndex)
    {
        //if (animIndex >= MAX_ANIMATION_INSTANCES) {
        //    if (DEF.bDbgS) System.out.println("MAX_ANIMATION_INSTANCES is too small!");
        //}
        return _current_animation[animIndex];
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // Added for backwards-compatibility purposes -cmm
	int ASprite::GetCurrentAnimationFrame()
    {
        return GetCurrentAnimationFrame(0);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	int ASprite::GetCurrentAnimationFrame(int animIndex) {
        return _aframes[(_anims_af_start[_current_animation[animIndex]] + _current_frame[animIndex]) * 5];
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // Added for backwards-compatibility purposes -cmm
	int ASprite::PaintAndUpdateCurrentAnimation(CGraphics* g, int posX, int posY, int flags, int hx, int hy)
    {
        return PaintAndUpdateCurrentAnimation(g, 0, posX, posY, flags, hx, hy);
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
	int ASprite::PaintAndUpdateCurrentAnimation(CGraphics* g, int animIndex, int posX, int posY, int flags, int hx, int hy)
    {
        //if (animIndex >= MAX_ANIMATION_INSTANCES) {
        //    if (bDbgS) System.out.println("MAX_ANIMATION_INSTANCES is too small!");
        //}

        int off = (_anims_af_start[_current_animation[animIndex]] + _current_frame[animIndex]) * 5;
        int frame = _aframes[off] & 0xFF;

        if(USE_INDEX_EX_AFRAMES)
        {//SangHo - flags의 상위 2비트를 "프레임"Index의 상위2비트로 메꿔주는 용도로 사용(2+8bit = MAX:1024)
            frame |= ((_aframes[off + 4] & FLAG_INDEX_EX_MASK) << INDEX_EX_SHIFT);
        }

        if ((flags & FLAG_FLIP_X) != 0)	hx += _aframes[off + 2];
        else							hx -= _aframes[off + 2];
        if ((flags & FLAG_FLIP_Y) != 0)	hy += _aframes[off + 3];
        else							hy -= _aframes[off + 3];

		//System.out.println(" ============= frame =====   "+ frame);


        PaintFrame(g, frame, posX - hx, posY - hy, flags ^ (_aframes[off + 4] & 0x0F), hx, hy);

		if ( !_is_anisuspend[animIndex] )	//ANIMATION SUSPEND
		{
        if(++_current_frame_time[animIndex] >= (_aframes[off + 1] & 0xFF))
        {
            if(++_current_frame[animIndex] >= (_anims_naf[_current_animation[animIndex]] & 0xFF))
            {
                if(_is_looping[animIndex])
                {
                    _current_frame_time[animIndex] = 0;
                    _current_frame[animIndex] = 0;
                }
                else
                {
                    //Alex - nothing just stay on the last frame
                    //_current_frame_time = 0;
                    //_current_frame = _anims_naf[_current_animation] & 0xFF;
                    _current_frame[animIndex]--;
					_is_aniDone[animIndex] = true;
                }
            } else {
                _current_frame_time[animIndex] = 0;
            }
        }
		}

        return _current_frame[animIndex];
    }

	int ASprite::GetCurrentAnimationFrameNum()
    {
        return GetCurrentAnimationFrameNum(0);
    }

	int ASprite::GetCurrentAnimationFrameNum(int animIndex) {
        return _current_frame[animIndex];
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

    // Added for backwards-compatibility purposes -cmm
	bool ASprite::IsAnimationDone()
    {
        return IsAnimationDone(0);
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////

	bool ASprite::IsAnimationDone(int animIndex) {
        //if (animIndex >= MAX_ANIMATION_INSTANCES) {
        //    if (bDbgS) System.out.println("MAX_ANIMATION_INSTANCES is too small!");
        //}

        int off = (_anims_af_start[_current_animation[animIndex]] + _current_frame[animIndex]) * 5;
		DBGPRINTF("IsAnimationDone %d %d %d %d",_current_frame[animIndex] + 1 , (_anims_naf[_current_animation[animIndex]] & 0xFF) , _current_frame_time[animIndex] , _aframes[off + 1] & 0xFF);
        return !_is_looping[animIndex] && (_current_frame[animIndex] + 1 == (_anims_naf[_current_animation[animIndex]] & 0xFF)) && (_current_frame_time[animIndex] >= (_aframes[off + 1] & 0xFF));
    }


	////NEW ADDITION CODE (ANI_STOP) 20070802///////////////////////////////////////////////////////////////////////



	void ASprite::PaintAnimation(CGraphics* g, int _animIndex, int posX, int posY, int flags, int hx, int hy)
    {//SangHo - 에니메이션에서 한 프레임을 그려줄때마다 프레임의 인덱스,좌표등등을 불러온다
	//SangHo -  (비인스턴스)내부 구조는 PaintAFrame 과 동일하게 PaintFrame 을 호출한다 차이점은 중요6개 변수가 이미 저장이 되어 있다는점


        //if (_animIndex >= MAX_ANIMATION_INSTANCES) {
        //    if (bDbgS) System.out.println("MAX_ANIMATION_INSTANCES is too small!");
        //}

        int off = (_anims_af_start[_current_animation[_animIndex]] + _current_frame[_animIndex]) * 5;
        int frame = _aframes[off] & 0xFF;

        if(USE_INDEX_EX_AFRAMES)
        {//SangHo - flags의 상위 2비트를 "프레임"Index의 상위2비트로 메꿔주는 용도로 사용(2+8bit = MAX:1024)
            frame |= ((_aframes[off + 4] & FLAG_INDEX_EX_MASK) << INDEX_EX_SHIFT);
        }

        if ((flags & FLAG_FLIP_X) != 0)	hx += _aframes[off + 2];
        else							hx -= _aframes[off + 2];
        if ((flags & FLAG_FLIP_Y) != 0)	hy += _aframes[off + 3];
        else							hy -= _aframes[off + 3];
			
        PaintFrame(g, frame, posX - hx, posY - hy, flags ^ (_aframes[off + 4] & 0x0F), hx, hy);
		//_current_frame_time[_animIndex]++;//SangHo - [버그수정109] Frame Time 인덱스 증가(UpdateAnimation 버그수정사항)
    }


	int ASprite::UpdateAnimation( int _animIndex )
	{//SangHo - (비인스턴스) 에니메이션 넘버(_current_animation) 의 _animIndex  번째 배열의 프레임 넘버(_current_frame)값을 증가시킨다

        //if (_animIndex >= MAX_ANIMATION_INSTANCES) {
        //    if (bDbgS) System.out.println("MAX_ANIMATION_INSTANCES is too small!");
        //}

        int off = (_anims_af_start[_current_animation[_animIndex]] + _current_frame[_animIndex]) * 5;

		if ( !_is_anisuspend[_animIndex] )	//ANIMATION SUSPEND
		{
        if(++_current_frame_time[_animIndex] >= (_aframes[off + 1] & 0xFF))
        {//SangHo  - [버그수정109] 프레임의 Time값이 끝에달했는지 여부판단한다 ++X 시키면 첫프레임을 못그리는버그발생(++_current_frame_time[_animIndex] => _current_frame_time[_animIndex] 으로 수정하였음)
            if(++_current_frame[_animIndex] >= (_anims_naf[_current_animation[_animIndex]] & 0xFF))
            {
                if(_is_looping[_animIndex])
                {
                    _current_frame_time[_animIndex] = 0;
                    _current_frame[_animIndex] = 0;
                }
                else
                {
                    //Alex - nothing just stay on the last frame
                    //_current_frame_time = 0;
                    //_current_frame = _anims_naf[_current_animation] & 0xFF;
                    _current_frame[_animIndex]--;
					_is_aniDone[_animIndex] = true;
                }
            } else {
                _current_frame_time[_animIndex] = 0;
            }
        }
		}

        return _current_frame[_animIndex];
    }


	void ASprite::setAnimStop( int _animIndex )
	{
		_current_frame[_animIndex] = (_anims_naf[_current_animation[_animIndex]] & 0xFF)-1;//_anims_naf[_animIndex] - 1 ;
		_is_looping[_animIndex] = false;
		_is_aniDone[_animIndex] = true;
	}

	bool ASprite::Is_animDone( int _animIndex )
    {
        return _is_aniDone[_animIndex];
    }
	 
	void ASprite::Is_animSuspend( int _animIndex )
    {
         _is_anisuspend[_animIndex] = true ;
    }
	
	void ASprite::Is_animResume( int _animIndex )
    {
         _is_anisuspend[_animIndex] = false ;
    }
	

	int ASprite::getAnimFrameMax( int _animIndex )
	{

		return (_anims_naf[_current_animation[_animIndex]] & 0xFF);
	}

	int ASprite::SetCurrentAnimationFrameNum(int _animIndex , int _index )
	{
		_current_frame[_animIndex] = _index;
		return _current_frame[_animIndex];
	}
*/

    ////////////////////////////////////////////////////////////////////////////////////////////////////


	void ASprite::Get_AFrameXY(int* tmpXY, int anim, int aframe, int posX, int posY, int flags, int hx, int hy)
	{
		int off = (_anims_af_start[anim] + aframe) * 5;
		int frame = _aframes[off] & 0xFF;

		if(USE_INDEX_EX_AFRAMES)
		{//SangHo - flags의 상위 2비트를 "프레임"Index의 상위2비트로 메꿔주는 용도로 사용(2+8bit = MAX:1024)
			frame |= ((_aframes[off + 4] & FLAG_INDEX_EX_MASK) << INDEX_EX_SHIFT);
		}





		if(flags & FLAG_ROT_90)
		{//flip 의 대상 hx hy 가 기존과다르게 바뀌어야 하며, 

			if ((flags & FLAG_FLIP_X) != 0)	
				hy += _aframes[off + 2];
			else							
				hy -= _aframes[off + 2];
			if ((flags & FLAG_FLIP_Y) != 0)	
				hx -= _aframes[off + 3];
			else							
				hx += _aframes[off + 3];
		}
		else
		{
			if ((flags & FLAG_FLIP_X) != 0)	
				hx += _aframes[off + 2];
			else							
				hx -= _aframes[off + 2];
			if ((flags & FLAG_FLIP_Y) != 0)	
				hy += _aframes[off + 3];
			else							
				hy -= _aframes[off + 3];
		}

		//SangHo - frames이 ROT90 이라면 Animation의 ROT90값은 상호간에 상쇄되면 안되기 때문에 Animation의 ROT90 값을 치환해준다
		if((_aframes[off + 4] & FLAG_ROT_90))//(flags == FLAG_FLIP_X || flags == FLAG_FLIP_Y))
		{//SangHo - frames이 ROT90이 된 상태에서는 Flip X,Y 값을 반대로 적용 && (FLAG_FLIP_X|FLAG_FLIP_Y) 일 경우는 변화가 없어야한다.

			if(flags == FLAG_FLIP_X || flags == FLAG_FLIP_Y){
				flags ^= (FLAG_FLIP_X|FLAG_FLIP_Y);
			}else if(flags == FLAG_ROT_90){
				flags ^= (FLAG_FLIP_X|FLAG_FLIP_Y);//ROT90은 아래쪽에서 상쇄
			}
		}        

		tmpXY[0] = (posX - hx);
		tmpXY[1] = (posY - hy);
		//return (posX - hx)*100000 + (posY - hy);
	}



	void ASprite::InitAnimation(){AppMain::m_nAsprite_Ani=0;}
	void ASprite::PaintAnimation(CGraphics* g, int _animIndex, int posX, int posY, int flags, int hx, int hy/*, bool LOOP*/)
	{//SangHo - 간이ANI Painter  무조건 루프가 돌며 시작지점을 정해주기 힘들다
// 		if(Fast_Ani_Num == _animIndex){
// 			Fast_Frm_Num++;
// 		}else{
// 			Fast_Ani_Num = _animIndex;
// 			Fast_Frm_Num=0;
// 		}
	/*AppMain::m_nAsprite_Ani%GetAFrames(_animIndex)
		if(LOOP){
			Fast_Frm_Num %= GetAFrames(_animIndex);
		}else{
			Fast_Frm_Num = MIN((GetAFrames(_animIndex)-1),Fast_Frm_Num);
		}*/
		int sss = AppMain::m_nAsprite_Ani%GetAFrames(_animIndex);

		PaintAFrame(g, _animIndex, sss, posX, posY, flags, hx, hy);
	}
	void ASprite::PaintAFrame(CGraphics* g, int anim, int aframe, int posX, int posY, int flags, int hx, int hy)
    {
        int off = (_anims_af_start[anim] + aframe) * 5;
        int frame = _aframes[off] & 0xFF;

        if(USE_INDEX_EX_AFRAMES)
        {//SangHo - flags의 상위 2비트를 "프레임"Index의 상위2비트로 메꿔주는 용도로 사용(2+8bit = MAX:1024)
            frame |= ((_aframes[off + 4] & FLAG_INDEX_EX_MASK) << INDEX_EX_SHIFT);
        }





		if(flags & FLAG_ROT_90)
		{//flip 의 대상 hx hy 가 기존과다르게 바뀌어야 하며, 

			if ((flags & FLAG_FLIP_X) != 0)	
				hy += _aframes[off + 2];
			else							
				hy -= _aframes[off + 2];
			if ((flags & FLAG_FLIP_Y) != 0)	
				hx -= _aframes[off + 3];
			else							
				hx += _aframes[off + 3];
		}
		else
		{
			if ((flags & FLAG_FLIP_X) != 0)	
				hx += _aframes[off + 2];
			else							
				hx -= _aframes[off + 2];
			if ((flags & FLAG_FLIP_Y) != 0)	
				hy += _aframes[off + 3];
			else							
				hy -= _aframes[off + 3];
		}

		//SangHo - frames이 ROT90 이라면 Animation의 ROT90값은 상호간에 상쇄되면 안되기 때문에 Animation의 ROT90 값을 치환해준다
		if((_aframes[off + 4] & FLAG_ROT_90))//(flags == FLAG_FLIP_X || flags == FLAG_FLIP_Y))
		{//SangHo - frames이 ROT90이 된 상태에서는 Flip X,Y 값을 반대로 적용 && (FLAG_FLIP_X|FLAG_FLIP_Y) 일 경우는 변화가 없어야한다.
			
			if(flags == FLAG_FLIP_X || flags == FLAG_FLIP_Y){
				flags ^= (FLAG_FLIP_X|FLAG_FLIP_Y);
			}else if(flags == FLAG_ROT_90){
				flags ^= (FLAG_FLIP_X|FLAG_FLIP_Y);//ROT90은 아래쪽에서 상쇄
			}
		}        

		
		m_nowAniX = hx;//SangHo - Flag 값이 적용된 마지막 상대좌표를 알아야 애니메이션 중단시 즉각 반영가능
		m_nowAniZ = hy;//SangHo - Flag 값이 적용된 마지막 상대좌표를 알아야 애니메이션 중단시 즉각 반영가능
		m_nowFlag = flags ^ (_aframes[off + 4] & 0x0F);//SangHo - 마지막 적용된 Flag 값을 알아야 애니메이션 중단시 즉각 반영가능

        PaintFrame(g, frame, posX - hx, posY - hy, m_nowFlag, hx, hy);










		
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////



	// Added By Ilyoung Lee, 
	void ASprite::PaintFrame(CGraphics* g, int frame, int posX, int posY, int flags, int hx, int hy, int anchor) {
	
		if ((anchor & CGraphics::HCENTER) == CGraphics::HCENTER) {
			posX -= GetFrameWidth(frame)>>1;
		}
		else if ((anchor & CGraphics::RIGHT) == CGraphics::RIGHT) {
			posX -= GetFrameWidth(frame);
		}
		
		if ((anchor & CGraphics::VCENTER) == CGraphics::VCENTER) {
			posY -= GetFrameHeight(frame) >> 1;
		}
		else if ((anchor & CGraphics::BOTTOM) == CGraphics::BOTTOM) {
			posY -= GetFrameHeight(frame);
		}

		PaintFrame(g, frame, posX, posY, flags, hx, hy);
	
	}

	//	하이퍼 프레임일 경우 isHyper를 true로 넘겨서 팔레트의 이중 변환을 막는다.
	void ASprite::PaintFrame(CGraphics* g, int frame, int posX, int posY, int flags, int hx, int hy, bool isHyper)
    {//SangHo - frame번 프레임을 그린다
        //	System.out.println("PaintFrame(g, "+frame+", "+posX+", "+posY+", 0x"+Integer.toHexString(flags)+", "+hx+", "+hy+")");
        int nFModules = _frames_nfm[frame]&0xFF;
        //	int nFModules = _frames_nfm[frame]&0xFFFF;
        for (int fmodule = 0; fmodule < nFModules; fmodule++)
		      PaintFModule(g, frame, fmodule, posX, posY, flags, hx, hy, isHyper);

#ifdef VIEW_CONTECT_CHECK

if(_frames_rects_start == NULL)return;
int rECT_NUM = _frames_rects_start[frame+1] - _frames_rects_start[frame];//rECT갯수
int rect_Index = _frames_rects_start[frame]*4;// Attacker 프레임의 시작지점 배열인덱스

if( rECT_NUM >= 1){ //무결성체크 - 몸통이 있다
	g->SetColor( 0x44ff44 );
	
	if(30 == frame)
	{
		int a = 0;
	}
	
	if(m_nowFlag & FLAG_FLIP_X)
		g->DrawRect((posX+m_nowAniX - hx) -_frames_rects[rect_Index]-_frames_rects[rect_Index+2],(posY+m_nowAniZ - hy) + _frames_rects[rect_Index+1], (byte)_frames_rects[rect_Index+2] - 1, (byte)_frames_rects[rect_Index+3] - 1);
	else
		g->DrawRect((posX+m_nowAniX - hx) +_frames_rects[rect_Index],(posY+m_nowAniZ - hy) + _frames_rects[rect_Index+1], (byte)_frames_rects[rect_Index+2] - 1, (byte)_frames_rects[rect_Index+3] - 1);
	
	if( rECT_NUM >= 2){ //무결성체크 - 공격이 있다
		g->SetColor( 0xff4444 );	
		rect_Index+=8;

		short X_a, Y_a;//충돌영역 XYWH
		byte W_a, H_a;//충돌영역 XYWH

		for(int xx = 0; xx <= rECT_NUM-3; xx++, rect_Index+=4){

			X_a=_frames_rects[rect_Index];
			Y_a=_frames_rects[rect_Index+1];
			W_a=(byte)_frames_rects[rect_Index+2];
			H_a=(byte)_frames_rects[rect_Index+3];
			
			if(m_nowFlag & FLAG_FLIP_X)
				g->DrawRect(
					(posX+m_nowAniX - hx) - X_a - W_a,
					(posY+m_nowAniZ - hy) + Y_a, 
					W_a - 1, 
					H_a - 1);
			else
				g->DrawRect(
					(posX+m_nowAniX - hx) + X_a,
					(posY+m_nowAniZ - hy) + Y_a, 
					W_a - 1, 
					H_a - 1);
		}
	}
}
#endif
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::PaintFModule(CGraphics* g, int frame , int fmodule, int posX, int posY, int flags, int hx, int hy, bool isHyper)
	{//SangHo - frame번째 프레임의 fmodule번째 모듈을 그려준다
		
		//nams
		//_crt_pal = 0;
		//if((bs_flags & BS_FM_PALETTE) != 0)
		if(!isHyper)
		{
			if((_fmodules_palette) != NULL)
			{
				_crt_pal = _fmodules_palette[(_frames_fm_start[frame] + fmodule)];
			}
		}
		
		int off = (_frames_fm_start[frame] + fmodule) << 2;//SangHo - 이 프레임의 0번째 위치+ 이프레임의 몇번째 모듈인가를 더해서구한뒤 4를 곱한다(각모듈은 4개의 정보로 이뤄지므로) 
		int fm_flags = _fmodules[off+3]&0xFF;//SangHo - 애니메이션의 flags와는 다른 모듈의 flags값 
		int index = _fmodules[off]&0xFF;// 최대 4 * 256값을 가지는 인덱스 정보값
		if (USE_INDEX_EX_FMODULES)
		{//SangHo - 프레임에서 모듈 인덱스 참조할때 - 로테이션 함수의 상위 2비트를 프레임의 부족한 부분을 메꿔주는 용도로 사용한다
			index |= ((fm_flags&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
		}
		int  moduleWidth,moduleHeight;//SangHo - 좌표연산의 잦은 GetFrameWidth(index),GetFrameHeight(index)를 줄여주기 위한 변수
		boolean HYPER_FM_ROT = false;
		int HYPER_FM_flags = 0;

		{//SangHo - 이부분은 2가지의 목적을 가진다.1-최적화  2-하이퍼프레임일 경우 모듈 대신 프레임의 값 전달
			if (USE_HYPER_FM && ((fm_flags & FLAG_HYPER_FM) != 0))
			{//SangHo - 프레임이 하이퍼 프레임일 경우
				moduleWidth = GetFrameWidth(index);//SangHo - 하이퍼 프레임은 모듈대신 프레임의Width값을 얻어와야 한다
				moduleHeight = GetFrameHeight(index);//SangHo - 하이퍼 프레임은 모듈대신 프레임의Height값을 얻어와야 한다
				if ((fm_flags & FLAG_ROT_90) != 0)
				{//SangHo - 하이퍼 프레임은 프레임에서 회전을 시킬 경우 모듈과 다른방식으로 회전한다. 이부분에 대한 수정
					HYPER_FM_ROT = true;
					HYPER_FM_flags = flags;//SangHo - flags값 저장을 위한 임시 저장소
				}

			}
			else
			{//SangHo - 프레임이 하이퍼 프레임이 아닐경우
				moduleWidth = GetModuleWidth(index);
				moduleHeight = GetModuleHeight(index);
			}

		}




		int posX_temp;
		int posY_temp;


		//	if ((flags & FLAG_OFFSET_FM) != 0)
		{//SangHo - 변경된 좌표 반영.   단, 하이퍼프레임의 경우에는 로테이션 적용시에 좌표를 변경시키면 하이퍼 프레임간에 결합이 깨진다.
			if ((flags & FLAG_FLIP_X) != 0)	posX_temp  = -_fmodules[off+1]-(USE_HYPER_FM && ((fm_flags & FLAG_HYPER_FM) != 0) ? 0 : _modules_w[index]&0xFF);
			else							posX_temp  =  _fmodules[off+1];
			if ((flags & FLAG_FLIP_Y) != 0)	posY_temp  = -_fmodules[off+2]-(USE_HYPER_FM && ((fm_flags & FLAG_HYPER_FM) != 0) ? 0 : _modules_h[index]&0xFF);
			else							posY_temp  =  _fmodules[off+2];
		}
		//if ((flags & FLAG_FLIP_X) != 0)	posX -= _modules_w[index]&0xFF;
		//if ((flags & FLAG_FLIP_Y) != 0)	posY -= _modules_h[index]&0xFF;


		/////////////////////////////////////////// flags Rotation ////////////////////////////////////////
		if ((flags & FLAG_ROT_90) != 0)
		{//SangHo - 회전상태에서는 애니메이션 좌표의 XY수치가 바뀐다. 자세한 내용은 아래 참조
			int posTemp = posX_temp;
			posX_temp = -posY_temp;//SangHo - Y좌표는 음수화 후 X 위치로
			posY_temp = posTemp;//SangHo - X좌표는 부호보존후  위치로
		}
		posX += posX_temp;
		posY += posY_temp;

		/////////////////////////////////////////// fm_flags Rotation ////////////////////////////////////////
		if ((fm_flags & FLAG_ROT_90) != 0)
		{//SangHo - 프레임의 flags값에 ROT_90이 포함되면 좌표와 Flip 축계가 틀어지므로 수정해 주어야 한다
			if ((flags & FLAG_ROT_90) == 0)
			{//SangHo - 에니메이션의 flags값에 ROT90이 없을때는 길이와 

				if ((flags & FLAG_FLIP_Y) != 0  || (flags & FLAG_FLIP_X) != 0 )//체크 필요
				{//SangHo - 프레임에서 ROT_90 이 실행되면 X길이와 Y 길이가 서로바뀐다. 그 가로 세로 길이 차이 만큼 보정한다
					if((flags & FLAG_FLIP_X) != 0)//SangHo - 에니메이션의 flags값에FLIP_X이 있을때
						posX -= moduleHeight-moduleWidth;
					if((flags & FLAG_FLIP_Y) != 0)//SangHo - 에니메이션의 flags값에FLIP_Y이 있을때
						posY -= moduleWidth-moduleHeight;

					if (flags != (FLAG_FLIP_X|FLAG_FLIP_Y))
					{//SangHo - ROT90이 된 상태에서는 Flip X,Y 값이 반대로 작용된다.이 문제해결 코드구현 
						flags ^= (FLAG_FLIP_X|FLAG_FLIP_Y);
					}
				}
			}
			else if ((flags & FLAG_ROT_90) != 0)
			{//SangHo - 에니메이션의 flags값에 ROT90이 포함되면 좌표와 FlipX,Y 축계가 바뀌므로 수정해 주어야 한다

				//SangHo - FlipX,FlipY는 XOR 연산 대상이지만 ROT90은 XOR 연산시 ROT 180 대신에 ROT 0이라는 원하지않는 결과값을 낸다.이 문제해결 코드구현
				flags ^= FLAG_ROT_90;
				fm_flags ^= FLAG_ROT_90|FLAG_FLIP_X|FLAG_FLIP_Y;
				//SangHo - 설명 : 2개의 플래그값에서 ROT90을 제거하고 ROT90 기능을 하는 FLAG_FLIP_X|FLAG_FLIP_Y값을 새롭게 부여한다

				if (flags == FLAG_FLIP_Y || flags == FLAG_FLIP_X)//FLAG_FLIP_X 또는 FLAG_FLIP_Y 한개의 값만 가질때
				{

					if(flags == FLAG_FLIP_X){
						posX -= moduleWidth;
						posY -= moduleHeight-moduleWidth;
					}
					if(flags == FLAG_FLIP_Y)
						posX -= moduleHeight;


					flags ^= FLAG_FLIP_X|FLAG_FLIP_Y;


				}
				else if((flags & (FLAG_FLIP_X|FLAG_FLIP_Y)) != 0)//두개의 값을 동시에 가질때
				{
					posX -= moduleHeight;
					posY -= moduleHeight-moduleWidth;

				}
				else
				{
					posX -= moduleWidth;//SangHo - 회전상태에서는 좌상기준에서 우상기준으로 바꿔준다
				}

			}

		}





		if (HYPER_FM_ROT){//SangHo - 프레임 회전이 있다면 하이퍼 프레임의 경우 일반 모듈과 달리 회전시 좌표가 변화한다. 이부분을 수정하는코드
			if ((HYPER_FM_flags & FLAG_ROT_90) != 0)//SangHo - 애니메이션 오리지널 flags값에 ROT90이 있을때
			{
				posX += moduleWidth;
				if ((HYPER_FM_flags & FLAG_FLIP_X) != 0)
					posY -= moduleWidth-moduleHeight;
				if ((HYPER_FM_flags & FLAG_FLIP_Y) != 0)
					posX -= moduleWidth-moduleHeight;
			}
			else
			{
				if ((HYPER_FM_flags & FLAG_FLIP_X) != 0)
					posX -= moduleWidth-moduleHeight;
				if ((HYPER_FM_flags & FLAG_FLIP_Y) != 0)
					posY -= moduleHeight-moduleWidth;

			}

		}






		if (USE_HYPER_FM && ((fm_flags & FLAG_HYPER_FM) != 0))
		{//SangHo - 만약 모듈이 하이퍼 프레임이라면(프레임형 모듈)모듈대신에 다시 프레임을 호출한다
			PaintFrame(g, index, posX, posY, flags ^ (fm_flags&0x0F), hx, hy, true);
		}
		else
		{//SangHo - 일반 모듈이면 PaintModule을 호출한다

			if ((flags & FLAG_ROT_90) != 0)
			{//SangHo - 회전상태에서는 좌상기준에서 우상기준으로 바꿔준다(하지만 위와는다르게 회전이 1회일어났으므로 세로길이만큼 X좌표수정)
				//PaintModule(g, index, posX, posY, flags ^ (fm_flags&0x0F),CGraphics::RIGHT); //오리지널
				posX -= moduleHeight;//최적화
			}
			PaintModule(g, index, posX, posY, flags ^ (fm_flags&0xFF));	

		}
	}

	

	// Added by Chun, 12, 02-5
	//Chun
	void ASprite::PaintModule(CGraphics* g, int module, int posX, int posY, int flags, int anchor)
	{
		if ((anchor & CGraphics::RIGHT) == CGraphics::RIGHT)
		{
			posX -= GetModuleWidth(module);
		}
		else if ((anchor & CGraphics::HCENTER) == CGraphics::HCENTER)
		{
			posX -= GetModuleWidth(module) / 2;
		}

		if ((anchor & CGraphics::BOTTOM) == CGraphics::BOTTOM)
		{
			posY -= GetModuleHeight(module);
		}	
		else if ((anchor & CGraphics::VCENTER) == CGraphics::VCENTER)
		{
			posY -= GetModuleHeight(module) / 2;
		}

		PaintModule(g, module, posX, posY, flags);
	}
	// Added by LeeSangHo, 09, 02, 16
	void ASprite::SetBlendCustom(bool blendCustom, bool overWrite, int Blend_Kind,int Blend_Percent)  ////////SangHo - Blend////////
	{// SangHo - Blend - 임의로 블랜딩을 지정해줄 필요가 있을때

		if(blendCustom){//커스텀 블랜딩을 쓰면
			if(overWrite){//기존의 블랜딩값을 무시한다면
				_m_blendCustom = BLEND_CUSTOM_OVER;
			}else{//기존의 블랜딩값을 보존하길 원한다면(블랜딩이 0 인 모듈만 블랜딩을 변경한다)
				_m_blendCustom = BLEND_CUSTOM_ZERO;
			}
		}else{//커스텀 블랜딩을 해제한다면
			_m_blendCustom = BLEND_CUSTOM_NOT;
			m_Blend_Kind=0;//블랜딩 없음
			m_Blend_Percent=0;//블랜딩 null
			return;
		}
		m_Blend_C_Kind = Blend_Kind;
		m_Blend_C_Percent = Blend_Percent;
	}
	// Added by LeeSangHo, 08, 12, 05
	void ASprite::SetBlendFrame(int blendFrame)  ////////SangHo - Blend////////
	{// SangHo - Blend - PaintModule과 밀접한 관계를 가지고 있는 모듈
		//주 기능은 블랜딩 정보를 담은 프레임의 넘버를 알려주는값을 저장
		//blendFrame 값이 0이상이라면 작동한다, 작동을 원치않는다면 -1이하의 값을 잡아주면된다.
		_m_blendFrame = blendFrame;
	}
	// Added by LeeSangHo, 08, 12, 05
	void ASprite::CheckBlendModule(int module,bool lighten)  ////////SangHo - Blend////////
	{//SangHo - Blend - 동적 블랜딩 처리를 위한 부분
		m_Blend_Kind=0;//블랜딩 없음
		m_Blend_Percent=0;//블랜딩 null
		int nFModules = _frames_nfm[_m_blendFrame]&0xFF;//프레임내 모듈갯수
		for (int fmodule = 0; fmodule < nFModules; fmodule++){
			int off = (_frames_fm_start[_m_blendFrame] + fmodule) << 2;//SangHo - 이 프레임의 0번째 위치+ 이프레임의 몇번째 모듈인가를 더해서구한뒤 4를 곱한다(각모듈은 4개의 정보로 이뤄지므로) 
			
			int index = _fmodules[off]&0xFF;// 최대 256값을 가지는 인덱스 정보값  //만약 모듈 갯수가 256개가 넘을수 있다면 알파모듈을 앞쪽에 배치하거나, 1024인덱스로 수정해야함
			if (USE_INDEX_EX_FMODULES)
			{//SangHo - 프레임에서 모듈 인덱스 참조할때 - 로테이션 함수의 상위 2비트를 프레임의 부족한 부분을 메꿔주는 용도로 사용한다
				index |= ((_fmodules[off+3]&0xFF&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);
			}

			if(index == module){
				if(lighten){
					m_Blend_Kind=5;//라이튼
					return;
				}
				m_Blend_Kind=_fmodules[off+1];//모듈의 블랜딩ID (모듈의 X값)
				m_Blend_Percent=_fmodules[off+2];//해당 ID 의 블랜딩 (0~32값 가능)정도 (모듈의 y값)
				if(m_Blend_Percent>32) m_Blend_Percent = 32;//이값은 32를 초과할 수 없다
				return;
			}
		}
	}

	void ASprite::PaintModule(CGraphics* g, int module, int posX, int posY, int flags)
    {//SangHo - 모듈을 그려주는부분

		

		if(_modules_data_pal[module]>=0)changePal(_modules_data_pal[module]);//SangHo - 모듈 고유 팔렛트로 변경한다



		if(_m_blendCustom == BLEND_CUSTOM_NOT){
			if (_m_blendFrame >= 0){
				CheckBlendModule(module,flags&0x20);//blendFrame 이 존재하면(-1이 아니라면)
			}
		}else {
			if(_m_blendCustom == BLEND_CUSTOM_ZERO){
				if (_m_blendFrame >= 0)CheckBlendModule(module,flags&0x20);//blendFrame 이 존재하면(-1이 아니라면)
				if (m_Blend_Kind == 0){	m_Blend_Kind = m_Blend_C_Kind;	m_Blend_Percent = m_Blend_C_Percent;}
			}else{
				m_Blend_Kind = m_Blend_C_Kind;
				m_Blend_Percent = m_Blend_C_Percent;
			}
		}




		bool delete_flag = false;
        if (USE_MODULE_MAPPINGS)
        {
            // Apply current module mapping...
            if (_cur_map >= 0)
            {
                module = _map[_cur_map][module];                
            }
        }

        int sizeX = _modules_w[module]&0xFF;
        int sizeY = _modules_h[module]&0xFF;
		
		if (sizeX == 0xFF || sizeX == 0xFE)
		{
			int w = _rectM_w[sizeY]&0xFF;
			int h = _rectM_h[sizeY]&0xFF;
			int oldColor = g_pGame->g->GetColor() ;
			
			if(g == NULL)return;
			
			g->SetColor( _rectMColors[sizeY] );
			if (sizeX == 0xFF)
				g->DrawRect( posX, posY, w, h);
			else
				g->FillRect( posX, posY, w, h);
			g->SetColor( oldColor );	

		}
		else
		{

			if (sizeX <= 0 || sizeY <= 0) return; 
		
			CImage* img = NULL;

			unsigned char* temp_scale_data;
			
#ifdef USE_DIRECT_DRAW

			img = _modules_image;

					
			ASSERT( _crt_pal >= 0 );
			//ASSERT( _crt_pal < _pal_length_1[imgIndex]);

			//if (_crt_pal >= _pal_length_1[imgIndex])
			//	_crt_pal = 0;

			_modules_image->SetCurrentData( _crt_pal,
				_data_format == ENCODE_FORMAT_I64RLE,
				/*_pal_length_2[_crt_pal]*/0,
				module);



			if ( _scaleImage )
			{
				int tempx = 0;
				int tempy = 0;

				tempx = (sizeX * _scaleFactor1) / _scaleFactor2;
				tempy = (sizeY * _scaleFactor1) / _scaleFactor2;				
				
				temp_scale_data = ScaleImage(sizeX , sizeY , tempx, tempy, _modules_image->GetPixelData());

				sizeX = tempx;
				sizeY = tempy;

				_modules_image->SetScaleData(temp_scale_data, tempx, tempy);


			}
#else			


			// Try to use cached images..."
			if ((_modules_image != NULL))
				img = _modules_image[_crt_pal * _nModules + module];
#endif		
			//if ( _scaleImage )
			//{
			//	short* image_data = (short*)(void*)img->GetPixelData();

			//	int tempx = 0;
			//	int tempy = 0;
			//			
			//	tempx = (sizeX * _scaleFactor1) / _scaleFactor2;
			//	tempy = (sizeY * _scaleFactor1) / _scaleFactor2;				
			//			
			//	image_data = ScaleImage(sizeX , sizeY , tempx, tempy, image_data);

			//	sizeX = tempx;
			//	sizeY = tempy;

			//	img->SetSize(sizeX,sizeY,16);
			//	img->m_pixel = (unsigned char*)image_data;

			//	_scaleImage = false;
			//}

			// Build RGB image...
			//if (img == NULL)
			//{ 	
			//	if (m_bWiseModule)
			//	{		
		 //  //         int modId = _crt_pal * _nModules + module;
			//		////System.out.println("modId :"+modId+"_crt_pal:"+_crt_pal+"_nModules:"+_nModules+"module:"+module);
		 //  //         if (_precalc_stack[_precalc_stack_index] > 0)
		 //  //             _modules_image[_precalc_stack[_precalc_stack_index]-1] = NULL;
			//		////System.out.println("_precalc_stack[_precalc_stack_index]-1"+(_precalc_stack[_precalc_stack_index]-1));
		 //  //         _precalc_stack[_precalc_stack_index] = modId + 1;
		 //  //         _precalc_stack_index = (_precalc_stack_index+1) % _precalc_stack_max;
			//		
			//		delete_flag = true;	
			//		short* image_data = DecodeImage(module, flags);
			//		if (image_data == NULL)
			//		{
			//			//if (bErr) System.out.println("DecodeImage() FAILED !");
			//			//SAFE_DEL_ARRAY(image_data);// = NULL;
			//			SAFE_DEL(img);
			//			return;
			//		}
			//		
			//		if ( _scaleImage )
			//		{
			//			int tempx = 0;
			//			int tempy = 0;
			//			
			//			tempx = (sizeX * _scaleFactor1) / _scaleFactor2;
			//			tempy = (sizeY * _scaleFactor1) / _scaleFactor2;				
			//			
			//			//image_data = ScaleImage(sizeX , sizeY , tempx, tempy, image_data);

			//			sizeX = tempx;
			//			sizeY = tempy;
			//		}
			//		
			//		//img = CImage.createRGBImage(image_data, sizeX, sizeY, _alpha);
			//		img = GL_NEW CMutableImage(sizeX, sizeY, 2*sizeX, 16, image_data);
			//		img->EnableColorKey(true);
			//		img->SetColorKey(0xf81f);
			//		
			//		// _modules_image[modId] = img;

			//		//	g.drawRGB(image_data, 0, sizeX, posX, posY, sizeX, sizeY, _alpha);
			//		
			//		//SAFE_DEL_ARRAY(image_data);// = NULL;

			//		image_data = NULL;				

			//	}
			//	else
			//	{
			//		//int offset = 0, scanLength = sizeX;
			//		//short* image_data = DecodeImage(module, flags);
			//		//if (image_data == NULL)
			//		//{
			//		//	//if (bErr) System.out.println("DecodeImage() FAILED !");
			//		//	return;
			//		//}
			//		//// draw argb without any flipx or flipy
			//		////drawRGB(g, image_data, offset, scanLength, posX, posY, sizeX, sizeY, _alpha);
			//		////g.drawRGB(image_data, 0, sizeX, posX, posY, sizeX, sizeY, _alpha);
			//		return;
			//	}
			//}

			sizeX = img->GetWidth();
			sizeY = img->GetHeight();

			const int x = 0;
			const int y = 0;
        //		if (posY < cy)			{ y = cy - posY; sizeY -= y; posY = cy; if (sizeY <= 0) return; }
        //		if (posY+sizeY > cy+ch)	{ sizeY = cy+ch - posY; if (sizeY <= 0) return; }
		


			if(drawMode == 1) {//SangHo - FLIP_X모드로 그린다
				int tempX =  0;
				int tempY = 0;
				
				if(posX < 0) {
				
					tempX = 256 + posX;

					if(tempX > 127) {
					
						posX = tempX;
					}
				}

				if(posY < 0) {
				
					tempY = 256 + posY;

					if(tempY > 127) {
					
						posY = tempY;
					}
				}
			}


			if(drawMode == 2) {
				int tempX =  0;
				
				int tempY = 0;

				
				if(posX < -70) {
				
					tempX = 256 + posX;

					if(tempX > 127) {
					
						posX = tempX;
					}
				}

				if(posY < 0) {
				
					tempY = 256 + posY;

					if(tempY > 127) {
					
						posY = tempY;
					}
				}

			}


		
			// Draw...
            if ((flags & FLAG_FLIP_X) != 0)
            {
                if ((flags & FLAG_FLIP_Y) != 0)
                {
                    // TODO: clip...
                    if((flags & FLAG_ROT_90) != 0) {
						g->DrawRegion(img, x, y, sizeX, sizeY, TRANS_ROT270, posX, posY, 0,/*Blend*/ m_Blend_Kind, m_Blend_Percent);
                    } else {
                        g->DrawRegion(img, x, y, sizeX, sizeY, TRANS_ROT180, posX, posY, 0,/*Blend*/ m_Blend_Kind, m_Blend_Percent);
                    }
                }
                else
                {                 
                    if((flags & FLAG_ROT_90) != 0) {
                        g->DrawRegion(img, x, y, sizeX, sizeY, TRANS_MIRROR_ROT90, posX, posY, 0,/*Blend*/ m_Blend_Kind, m_Blend_Percent);
                    } else {
                        g->DrawRegion(img, x, y, sizeX, sizeY, TRANS_MIRROR, posX, posY, 0,/*Blend*/ m_Blend_Kind, m_Blend_Percent);
                    }
                }
            }
            else if ((flags & FLAG_FLIP_Y) != 0)
            {               
                if((flags & FLAG_ROT_90) != 0) {
					g->DrawRegion(img, x, y, sizeX, sizeY, TRANS_MIRROR_ROT270, posX, posY, 0,/*Blend*/ m_Blend_Kind, m_Blend_Percent);//SangHo - 버그수정(TRANS_MIRROR_ROT90)
                } else {
					g->DrawRegion(img, x, y, sizeX, sizeY, TRANS_MIRROR_ROT180, posX, posY, 0,/*Blend*/ m_Blend_Kind, m_Blend_Percent);
                }
            }
            else
            {     
                if((flags & FLAG_ROT_90) != 0) {
					g->DrawRegion(img, x, y, sizeX, sizeY, TRANS_ROT90, posX, posY, 0,/*Blend*/ m_Blend_Kind, m_Blend_Percent);
                } else {
					g->DrawRegion(img, x, y, sizeX, sizeY, TRANS_NONE, posX, posY, 0,/*Blend*/ m_Blend_Kind, m_Blend_Percent);
                }
            }
			

			
			//if(delete_flag)
			//{
			//	SAFE_DEL(img);
			//	img = NULL;
			//}
			//DBGPRINTF("**********mid %d ================ %d \n", &_modules_image , &img);
			
			if ( _scaleImage )
			{
				SAFE_DEL_ARRAY(temp_scale_data);
			}
		}//End else if (sizeX == 0xFF || sizeX == 0xFE)
        
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////


	void ASprite::ScaleImage(int factor1, int factor2)
	{
		_scaleFactor1 = factor1;
		_scaleFactor2 = factor2;
		_scaleImage = true;
	}

	void ASprite::StopScaleImage()
	{
		_scaleImage = false;
	}


	CImage* ASprite::ScaleImage(CImage* src, int destWidth, int destHeight, MemoryType memType)
	{
		if ((destWidth | destHeight) < 0)
		{
			//		return CImage.createImage(0, 0);
			return NULL;
		}
		if(src == NULL)return NULL;
		int width = src->GetWidth();
		int height = src->GetHeight();
		//	int* buff = new int[width * height];
		//	int* buff2 = new int[destWidth * destHeight];
		//	src->getRGB(buff, 0, width, 0, 0, width, height);
		//GL_NEW CMutableImage(sizeX, sizeY, 2*sizeX, 16, image_data);
		CImage* dest = GL_NEW CMutableImage(destWidth, destHeight, 16/*NATIVE_COLOR_DEPTH * 2*/, memType) ;//!?
		unsigned char* buff = (unsigned char*)(void*) src->GetPixelData();
		unsigned int* buff2 = (unsigned int*)(void*) dest->GetPixelData();
		int m=0, n=0;
		for (int i = 0; i < destWidth; i++)
		{
			for (int j = 0; j < destHeight; j++)
			{
				//will raise out of array index exception				
				m =  (j * height + (destHeight >> 1)) / destHeight;//  g_pGame->GetNum(j, height, destHeight);
				if (m >= height)
					m = height - 1;
				n = (i * width + (destWidth >> 1)) / destWidth; //g_pGame->GetNum(i, width, destWidth);
				if (n >= width)
					n = width - 1;
				buff2[j * destWidth + i] = buff[m * width + n];
			}
		}
		//	return CImage.createRGBImage(buff2, destWidth, destHeight, true);
		return dest;
	}

	//short* ASprite::ScaleImage(int width , int height , int destWidth, int destHeight, short* pixel)
	//{	
	//	if ((destWidth | destHeight) < 0)
	//	{
	//		//		return CImage.createImage(0, 0);
	//		return NULL;
	//	}
	//	
	//	short* dest = GL_NEW short[destWidth * destHeight];
	//	int m=0, n=0;

	//	for (int i = 0; i < destWidth; i++)
	//	{
	//		for (int j = 0; j < destHeight; j++)
	//		{
	//			m =  (j * height + (destHeight >> 1)) / destHeight;//g_pGame->GetNum(j, height, destHeight);
	//			if (m >= height)
	//				m = height - 1;
	//			n = (i * width + (destWidth >> 1)) / destWidth; //g_pGame->GetNum(i, width, destWidth);
	//			if (n >= width)
	//				n = width - 1;
	//			dest[j * destWidth + i] = pixel[m * width + n];
	//		}
	//	}

	//	SAFE_DEL_ARRAY(pixel);
	//	return dest;
	//	
	//}
	
	unsigned char* ASprite::ScaleImage(int width , int height , int destWidth, int destHeight, unsigned char* pixel)
	{	
		if ((destWidth | destHeight) < 0)
		{			
			return NULL;
		}

		unsigned char* dest = GL_NEW unsigned char[destWidth * destHeight];
		int m=0, n=0;

		for (int i = 0; i < destWidth; i++)
		{
			for (int j = 0; j < destHeight; j++)
			{
				m =  (j * height + (destHeight >> 1)) / destHeight;//g_pGame->GetNum(j, height, destHeight);
				if (m >= height)
					m = height - 1;
				n = (i * width + (destWidth >> 1)) / destWidth; //g_pGame->GetNum(i, width, destWidth);
				if (n >= width)
					n = width - 1;
				dest[j * destWidth + i] = pixel[m * width + n];
			}
		}		
		return dest;
	}


    ////////////////////////////////////////////////////////////////////////////////////////////////////
	short* ASprite::DecodeImage(int module, int flags)
	{
		if (_modules_data == NULL || _modules_data_off == NULL)
		{
			return NULL;
		}

		int sizeX = _modules_w[module]&0xFF;
		int sizeY = _modules_h[module]&0xFF;

		//if (bErr)
		//{
		//	if (sizeX * sizeY > temp_length)
		//	{
		//		//System.out.println("ERROR: sizeX x sizeY > temp.length ("+sizeX+" x "+sizeY+" = "+sizeX * sizeY+" > "+temp.length+") !!!");
		//		return NULL;
		//	}
		//}

		short* img_data = GL_NEW short[sizeX*sizeY];

		// Choose palette...
		PalettePixel* pal = _pal[_crt_pal];

		if (pal == NULL)
		{
			return NULL;
		}

		// Build displayable...
		byte* image = _modules_data;
		int si = _modules_data_off[module] & 0xFFFF;
		int di = 0;
		int ds = sizeX * sizeY;

		// HINT: Sort these encoders regarding how often are used by your game!
		if ((_data_format == ENCODE_FORMAT_I64RLE) && USE_ENCODE_FORMAT_I64RLE)
		{
			// variable RLE compression, max 64 colors...
			while (di < ds)
			{
				int c = image[si++]&0xFF;
				int clr = pal[c & _i64rle_color_mask];
				c >>= _i64rle_color_bits;
				while (c-- >= 0)
					img_data[di++] = clr;
			}
		}
		else
		if ((_data_format == ENCODE_FORMAT_I127RLE) && USE_ENCODE_FORMAT_I127RLE)
		{
//			System.out.println("fixed RLE compression, max 127 colors...");
			// fixed RLE compression, max 127 colors...
			int c, c2, clr;

			if (!m_bWiseModule && (flags & FLAG_FLIP_X) == FLAG_FLIP_X)
			{
				flags &= ~FLAG_FLIP_X; // we dont want this to be reflipped!!!

				int cnt = sizeX;
				di = sizeX - 1;

				// RLE compression, max 127 colors...
				while (di < ds)
				{
					c = image[si++] & 0xFF;
	
					if (c > 127)
					{
						c2 = image[si++] & 0xFF;
						clr = pal[c2];
						c -= 128;
	
						while (c-- > 0)
						{
							img_data[di] = clr;

							if (--cnt == 0)
							{
								cnt = sizeX;
								di += (sizeX << 1);
							}
							di--;
						}
					}
					else
					{
						img_data[di] = pal[c];

						if (--cnt == 0)
						{
							cnt = sizeX;
							di += (sizeX << 1);
						}
						di--;
					}
				}
			}
			else
			{
				while (di < ds)
				{
					c = image[si++]&0xFF;
					if (c > 127)
					{
						c2 = image[si++]&0xFF;
						clr = pal[c2];
						c -= 128;

						while (c-- > 0)
						{
							img_data[di++] = clr;
						}
					}
					else
					{
						img_data[di++] = pal[c];
					}
				}
			}
		}
		else
		if ((_data_format == ENCODE_FORMAT_I256RLE) && USE_ENCODE_FORMAT_I256RLE)
		{
//			System.out.println("fixed RLE compression, max 256 colors...");
			// fixed RLE compression, max 256 colors...
			int c;
			int clr;
			//if (!m_bWiseModule && (flags & FLAG_FLIP_X) != 0)
			//{
			//	int cnt = sizeX;
			//	di = sizeX - 1;

			//	// RLE compression, max 127 colors...
			//	while (di < ds)
			//	{
			//		c = image[si++] & 0xFF;
	
			//		if (c > 127)
			//		{
			//			c -= 128;
	
			//			while (c-- > 0)
			//			{
			//				img_data[di] = pal[image[si++]&0xFF];

			//				if (--cnt == 0)
			//				{
			//					cnt = sizeX;
			//					di += (sizeX << 1);
			//				}
			//				di--;
			//			}
			//		}
			//		else
			//		{
			//			clr = pal[image[si++]&0xFF];

			//			while (c-- > 0)
			//			{
			//				img_data[di] = clr;

			//				if (--cnt == 0)
			//				{
			//					cnt = sizeX;
			//					di += (sizeX << 1);
			//				}
			//				di--;
			//			}
			//		}
			//	}
			//}
			//else
			{
				while (di < ds)
				{
					c = image[si++]&0xFF;
					if (c > 127)
					{
						c -= 128;
						while (c-- > 0)
						{
							img_data[di++] = pal[image[si++]&0xFF];
						}
					}
					else
					{
						clr = pal[image[si++]&0xFF];
						while (c-- > 0)
						{
							img_data[di++] = clr;
						}
					}
				}
			}
		}
		else
		if ((_data_format == ENCODE_FORMAT_I16) && USE_ENCODE_FORMAT_I16)
		{
//			System.out.println("2 pixels/byte, max 16 colors...");
			// 2 pixels/byte, max 16 colors...
			if (!m_bWiseModule && (flags & FLAG_FLIP_X) != 0)
			{
				if ((flags & FLAG_FLIP_Y) != 0)
				{
					// FLIP X-Y
					di = ds - 1;

					while (di > 0)
					{
						img_data[di--] = pal[(image[si] >> 4) & 0x0F];
						img_data[di--] = pal[(image[si]     ) & 0x0F];
						si++;
					}
				}
				else
				{
					// FLIP X
					int offX = sizeX - 1;
					int offY = 0;
					while (di < ds)
					{
						img_data[offY + offX] = pal[(image[si] >> 4) & 0x0F];

						if (--offX < 0)
						{
							offX = sizeX - 1;
							offY += sizeX;
						}

						img_data[offY + offX] = pal[(image[si]     ) & 0x0F];

						if (--offX < 0)
						{
							offX = sizeX - 1;
							offY += sizeX;
						}

						di += 2;
						si++;
					}
				}
			}
			else if (!m_bWiseModule && (flags & FLAG_FLIP_Y) != 0)
			{
				// FLIP Y
				int offX = 0;
				int offY = ds - sizeX;
				while (di < ds)
				{
					img_data[offY + offX] = pal[(image[si] >> 4) & 0x0F];

					if (++offX >= sizeX)
					{
						offX = 0;
						offY -= sizeX;

						if (offY < 0)
						{
							break;
						}
					}

					img_data[offY + offX] = pal[(image[si]     ) & 0x0F];

					if (++offX >= sizeX)
					{
						offX = 0;
						offY -= sizeX;
					}

					di += 2;
					si++;
				}
			}
			else
			{
				// NO FLIP
				while (di < ds)
				{
					img_data[di++] = pal[(image[si] >> 4) & 0x0F];
					img_data[di++] = pal[(image[si]     ) & 0x0F];
					si++;
				}
			}

			// We do the flipping during the decoding... no need to reflip.
			flags = 0;
		}
		else
		if ((_data_format == ENCODE_FORMAT_I4) && USE_ENCODE_FORMAT_I4)
		{
//			System.out.println("4 pixels/byte, max 4 colors...");
			// 4 pixels/byte, max 4 colors...
			while (di < ds)
			{
				img_data[di++] = pal[(image[si] >> 6) & 0x03];
				img_data[di++] = pal[(image[si] >> 4) & 0x03];
				img_data[di++] = pal[(image[si] >> 2) & 0x03];
				img_data[di++] = pal[(image[si]     ) & 0x03];
				si++;
			}
		}
		else
		if ((_data_format == ENCODE_FORMAT_I2) && USE_ENCODE_FORMAT_I2)
		{
//			System.out.println("8 pixels/byte, max 2 colors...");
			// 8 pixels/byte, max 2 colors...
			while (di < ds)
			{
				img_data[di++] = pal[(image[si] >> 7) & 0x01];
				img_data[di++] = pal[(image[si] >> 6) & 0x01];
				img_data[di++] = pal[(image[si] >> 5) & 0x01];
				img_data[di++] = pal[(image[si] >> 4) & 0x01];
				img_data[di++] = pal[(image[si] >> 3) & 0x01];
				img_data[di++] = pal[(image[si] >> 2) & 0x01];
				img_data[di++] = pal[(image[si] >> 1) & 0x01];
				img_data[di++] = pal[(image[si]     ) & 0x01];
				si++;
			}
		}
		else
		if ((_data_format == ENCODE_FORMAT_I256) && USE_ENCODE_FORMAT_I256)
		{
//			System.out.println("1 pixel/byte, max 256 colors...");
			// 1 pixel/byte, max 256 colors...
			while (di < ds)
			{
				img_data[di++] = pal[image[si++]&0xFF];
			}
		}

		// NOTE: M-O: For performance, the code below should be handled directly in the
		// decoding sections above. If we could decode the module data with its flipped
		// infos, we wouldn't need the code below.
		// But doing so would take more code space since we would require to handle all
		// doing all flips possibilities for all encoding possibilities used in the
		// project (I2, I4, I16, I127RLE, etc.)
		if (!m_bWiseModule)
		{
			if ((flags & FLAG_FLIP_X) != 0)
			{
				int temp;
				for (int x1 = 0, x2 = sizeX - 1; x1 < x2; x1++, x2--)
				{
					for (int off = 0; off < ds; off += sizeX)
					{
						temp = img_data[off + x1];
						img_data[off + x1] = img_data[off + x2];
						img_data[off + x2] = temp;
					}
				}
			}
			if ((flags & FLAG_FLIP_Y) != 0)
			{
				int temp;
				for (int off1 = 0, off2 = (sizeY - 1) * sizeX; off1 < off2; off1 += sizeX, off2 -= sizeX)
				{
					for (int x = 0; x < sizeX; x++)
					{
						temp = img_data[off1 + x];
						img_data[off1 + x] = img_data[off2 + x];
						img_data[off2 + x] = temp;
					}
				}
			}
		}

	//	System.out.println("...DecodeImage("+module+", 0x"+Integer.toHexString(flags)+")");
		return img_data;
	}

    
	/*
	메소드 ModuleExchange
	메소드의 용도 : 프레임을 그려줄때 내부구성요소Module 의 교체를 담당
	파라메터 기능 : mA-모듈A, mB-모듈B  교체할 쌍방
	사용 유의사항 : 다시 Exchange 하지 않으면 메모리에서 해제 하기전까지 유효하다
	작성자 : 이상호
	작성일 : 2009-05-25
	*/
	void ASprite::ModuleExchange(int mA, int mB)
	{//프레임을 구성하는 요소인 모듈을 모든 프레임을 대상으로 mA와 mB를 교체한다(메모리에서 해제 전까지 계속 유효)

		int _fmodules_length = _nFrames<<2;
		int UN_MASK = 0xFF-FLAG_INDEX_EX_MASK;
		int MASK = FLAG_INDEX_EX_MASK<<INDEX_EX_SHIFT;

		//_fmodules = GL_NEW char[_fmodules_length];
		for (int i = 0, Module = 0; i < _fmodules_length; i+=4) 
		{
			if (USE_HYPER_FM && ((_fmodules[i+3] & FLAG_HYPER_FM) != 0)){continue;}//하이퍼 프레임이면 스킵한다

			Module = _fmodules[i]&0xFF+((_fmodules[i+3]&FLAG_INDEX_EX_MASK)<<INDEX_EX_SHIFT);//Max 1024의 인덱스
			if(mA == Module){
				_fmodules[i  ] = 0xFF & mB;
				_fmodules[i+3] = 0xFF & ((mB & MASK) >> INDEX_EX_SHIFT ) + (_fmodules[i+3] & UN_MASK);
			}else if(mB ==Module){
				_fmodules[i  ] = 0xFF & mA;
				_fmodules[i+3] = 0xFF & ((mA & MASK) >> INDEX_EX_SHIFT ) + (_fmodules[i+3] & UN_MASK);
			}

		}

	}
    ////////////////////////////////////////////////////////////////////////////////////////////////////

	void ASprite::SetCurrentPalette(int pal)		{ _crt_pal = pal; }
	int ASprite::GetCurrentPalette()				{ return _crt_pal; }

 

	

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // Palette generation based on other palette...

    // -1 - original colors
    //  0 - invisible (the sprite will be hidden)
    //  1 - red-yellow
    //  2 - blue-cyan
    //  3 - green
    //  4 - grey

	int* ASprite::GenPalette(int type, int* pal)
    {
        //if (type <  0) return pal;	// original
        //if (type == 0) return NULL; // invisible

        //int new_pal[pal.length];
        //switch (type)
        //{
        //    /*			case 1: // red - yellow
        //    for (int i = 0; i < pal.length; i++)
        //    new_pal[i] = (pal[i] | 0x00FF3300) & 0xFFFFFF00;
        //    break;

        //    case 2: // blue - cyan
        //    for (int i = 0; i < pal.length; i++)
        //    new_pal[i] = (pal[i] | 0x000033FF) & 0xFF00FFFF;
        //    break;

        //    case 3: // green
        //    for (int i = 0; i < pal.length; i++)
        //    new_pal[i] = (pal[i] | 0x00000000) & 0xFF00FF00;
        //    break;
        //    */
        //case 4: // grey (desaturate)
        //    for (int i = 0; i < pal.length; i++)
        //    {
        //        int a = (pal[i] & 0xFF000000);
        //        int r = (pal[i] & 0x00FF0000) >> 16;
        //        int g = (pal[i] & 0x0000FF00) >> 8;
        //        int b = (pal[i] & 0x000000FF);
        //        int l = ((r + b + g) / 3) & 0x000000FF;
        //        new_pal[i] = ((l << 16) | (l << 8) | l | a);
        //    }
        //    break;
        //    /*
        //    case 5: // blend with black 50%
        //    for (int i = 0; i < pal.length; i++)
        //    {
        //    int a = (pal[i] & 0xFF000000);
        //    int r = (pal[i] & 0x00FC0000) >> 2;
        //    int g = (pal[i] & 0x0000FC00) >> 2;
        //    int b = (pal[i] & 0x000000FC) >> 2;
        //    new_pal[i] = (a | r | g | b);
        //    }
        //    break;
        //    */		}

        //return new_pal;
		return NULL;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    // sytem
	void ASprite::Gc()
    {
//#ifndef NOT_USE_GC        
//        long memLast = Runtime.getRuntime().freeMemory();
//        System.gc();
//        for (int i = 0; i < 10; i++)
//        {
//            Thread.yield();
//            if (Runtime.getRuntime().freeMemory() < memLast)
//                break;
//        }
//#endif
    }

	void ASprite::drawRGB(CGraphics* g, int* data, int offset, int scanlength, int x, int y, int width, int height, bool processAlpha)
    {
//    	Image tmpImage = Image.createImage(width, height);
//    	Graphics g = tmpImage.getGraphics();
    	
//    	g.setRGBPixels(0, 0, width, height, data, offset, width*4);
    	
    	for(int j = 0; j < height; j++){
    		for(int i = 0; i < width; i++){
    			int color = data[i + width * j];
    			int alpha = ((int)color << 24) & 0xFF000000;

    			if(color == 0x00F800F8 || color == 0){
    			} else{
    				g_pGame->g->SetColor(color);
    				g_pGame->g->FillRect(x + i, y + j, 1, 1);
    			}
    		}
    	}  	
    }

	ASprite::~ASprite()
	{
#ifdef WIN32
		spriteCounter--;
#endif

		workPal(false,0,0);//임시팔렛트 공간 해제

		SAFE_DEL_ARRAY(_rectM_w);
		SAFE_DEL_ARRAY(_rectM_h);
		SAFE_DEL_ARRAY(_rectMColors);	
		
		SAFE_DEL_ARRAY(_modules_w);
		SAFE_DEL_ARRAY(_modules_h);
		SAFE_DEL_ARRAY(_frames_nfm);
		SAFE_DEL_ARRAY(_frames_fm_start);
		SAFE_DEL_ARRAY(_frames_rc);
		SAFE_DEL_ARRAY(_frames_coll);
		SAFE_DEL_ARRAY(_fmodules);
		SAFE_DEL_ARRAY(_fmodules_palette);
		SAFE_DEL_ARRAY(_anims_naf);	
		SAFE_DEL_ARRAY(_anims_af_start);
		SAFE_DEL_ARRAY(_aframes);

		////////////////////////////////////////////////////////
		SAFE_DEL_ARRAY(_frames_rects_start);
		SAFE_DEL_ARRAY(_frames_rects);
		
		////////////////////////////////////////////////////////
		

		SAFE_DEL_ARRAY_ARRAY(_map,MAX_MODULE_MAPPINGS);
		SAFE_DEL_ARRAY_ARRAY(_pal,MAX_SPRITE_PALETTES);
		//SAFE_DEL(_palettes);
		//SAFE_DEL_ARRAY(_pal_alpha);
		SAFE_DEL_ARRAY(_modules_data_off);
		SAFE_DEL_ARRAY(_modules_data_pal);
		SAFE_DEL_ARRAY(_modules_data);

#ifdef USE_DIRECT_DRAW
		//DBGPRINTF("-------------------del %d  \n", &_modules_image );
		SAFE_DEL(_modules_image);
		
#else
		SAFE_DEL_ARRAY_OBJ(_modules_image,_modules_image_length);
		SAFE_DEL_ARRAY(_precalc_stack);
#endif


		
		
		SAFE_DEL_ARRAY(_pal);

		
	}


	//dongwan
	

#if NATIVE_COLOR_DEPTH== 16

	//_palettes //SangHo - 팔렛트의 갯수를 저장
	//_colors	//SangHo - 팔렛트내의 컬러수를 저장
	//_pal[p]	//SangHo - 팔렛트 갯수 만큼의  팔렛트 저장소를 만든뒤 포인터를 넘긴다

	PalettePixel* ASprite::getPal()
	{
		return _pal[_crt_pal];//현재 사용중인 팔렛트의 주소를 넘긴다 
	}

	void ASprite::setPal(PalettePixel* pal)
	{
		_pal[_crt_pal] = pal;//팔렛트를 대체한다.
	}
#else	//converted to 8888
	int* ASprite::getPal()
	{
		return _pal[_crt_pal]; 
	}

	void ASprite::setPal(int* pal)
	{
		_pal[_crt_pal] = pal;
	}
#endif	
	

	boolean ASprite::changePal(int palIdx){//SangHo - 팔렛트의 번호를 바꿔줄때 사용한다.
		if(_palettes <= palIdx)
			return false;//요청한 인덱스가 팔렛트 갯수를 넘었다

		//if(_pal_Copy != NULL)
		//	return false;//팔렛트워킹 중에는 팔렛트 교체 금지

		_crt_pal = palIdx;//팔렛트 넘버 교체 
		return true;
	}

	//2009-03-17 수정 - SangHo - 팔렛트의 갯수만큼을 동시에 작업해준다.
	boolean ASprite::workPal(boolean Work, int Pal_Kind,int percent){//SangHo - 현재 팔렛트를 임시로 생성한 팔렛트로 바꿔치기한다 percent는 -31 ~ +31

		if(Work){//임시 팔렛트를 사용한다.
			if(_pal_Copy == NULL){//_pal_Copy 가 처음 만들어지는것이라면 저장공간을 할당한다.

				_pal_Copy = GL_NEW PalettePixel*[_palettes];//SangHo - 팔렛트 갯수(_palettes) 만큼 포인터를 만든다		
				_pal_Back = GL_NEW PalettePixel*[_palettes];//SangHo - 팔렛트 갯수(_palettes) 만큼 백업 공간생성		
				for (int p = 0; p < _palettes; p++)
				{
					_pal_Copy[p] = GL_NEW PalettePixel[_colors];//SangHo - 컬러 갯수 만큼의  팔렛트 저장소를 만든뒤 포인터를 넘긴다
					_pal_Back[p] = _pal[p];//기존 팔렛트의 주소를 백업한다.
					_pal[p] = _pal_Copy[p];//팔렛트 주소 바꿔치기
				}



				//_pal_Copy = 
				//	//(PalettePixel*) MALLOC(sizeof(PalettePixel)*_colors)//임시팔렛트 공간 생성
				//	GL_NEW PalettePixel[_colors];//임시팔렛트 공간 생성
				//_pal_Back = _pal[_crt_pal];//기존 팔렛트의 번호를 백업한다.
				//_pal[_crt_pal] = _pal_Copy;//팔렛트 주소 바꿔치기
			}



			int s,R,G,B;
			for (int p = 0; p < _palettes; p++)//팔렛트 갯수만큼
			{
				for( int i =0; i<_colors; i++ )//컬러 갯수만큼
				{
					if(*(_pal_Back[p]+i) == 0xF81F )//투명값은 제외하고
					{		
						*(_pal_Copy[p]+i) =  0xF81F; 
						continue; 
					}

					
					switch(Pal_Kind){
						case 0://명도 조절
							s = *(_pal_Back[p]+i);//오리지널 팔레트
							if(percent > 0){//밝을땐 더하기
								R = ((s&0xF800)>>11	) + percent;
								G = ((s&0x07E0)>>6	) + percent;
								B = ((s&0x001f)		) + percent; 
								R = (R<0 ? 0: (R>0x1f ? 0x1f: R));
								G = (G<0 ? 0: (G>0x1f ? 0x1f: G));
								B = (B<0 ? 0: (B>0x1f ? 0x1f: B));
							}else{//어두울땐 나누기
								R = (((s&0xF800)>>11) * (32+percent)) >> 5;
								G = (((s&0x07E0)>>6	) * (32+percent)) >> 5;
								B = (((s&0x001f)	) * (32+percent)) >> 5; 
								R = (R<0 ? 0: (R>0x1f ? 0x1f: R));
								G = (G<0 ? 0: (G>0x1f ? 0x1f: G));
								B = (B<0 ? 0: (B>0x1f ? 0x1f: B));
							}
							*(_pal_Copy[p]+i)=(R << 11) | (G << 6) | B;//복제 팔렛트에 값채우기
							
							break;

						
					}

				}

			}

		}else{//오리지널 팔렛트 로 돌린다.

			if(_pal_Back != NULL || _pal_Copy != NULL){
				for (int p = 0; p < _palettes; p++)//팔렛트 갯수만큼
				{
					if(_pal_Back[p] != NULL){
						_pal[p] = _pal_Back[p];//기존 팔렛트 주소를 다시 복구한다.
						_pal_Back[p] = NULL;
					}
				}

				SAFE_DEL_ARRAY_ARRAY(_pal_Copy , _palettes)//임시팔렛트 공간 해제
				SAFE_DEL_ARRAY(_pal_Back)//원본 팔렛트 포인터  백업공간 해제
			}
		}
		 
		return true;
	}




//} // class ASprite

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
