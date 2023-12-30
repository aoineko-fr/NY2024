// ____________________________
// ██▀▀█▀▀██▀▀▀▀▀▀▀█▀▀█        │   ▄▄▄                ▄▄      
// ██  ▀  █▄  ▀██▄ ▀ ▄█ ▄▀▀ █  │  ▀█▄  ▄▀██ ▄█▄█ ██▀▄ ██  ▄███
// █  █ █  ▀▀  ▄█  █  █ ▀▄█ █▄ │  ▄▄█▀ ▀▄██ ██ █ ██▀  ▀█▄ ▀█▄▄
// ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀────────┘                 ▀▀
//  Program template
//─────────────────────────────────────────────────────────────────────────────

//=============================================================================
// INCLUDES
//=============================================================================
#include "msxgl.h"
#include "localize.h"
#include "tile.h"
#include "vgm/lvgm_player.h"

//=============================================================================
// DEFINES
//=============================================================================

// Library's logo
#define MSX_GL				"\x01\x02\x03\x04\x05\x06"
// 
#define OOO					0
//
#define SPLIT_LINE			128
//
#define PATTERN_16OR_1ST	32
// VRAM table addresses
#define ADDR_LAYOUT			0x0000
#define ADDR_SAT1			0x7600
#define ADDR_SPT			0x7800
#define ADDR_SAT2			0xA200

// Language list entry 
struct Language
{
	u8        Code;
	const u8* Font;
};

//=============================================================================
// READ-ONLY DATA
//=============================================================================

// V9990 4-bits background data
#include "content/data_bg_4b.h"

// Localization data
#include "content/data_loc.h"

// Music
#include "content/lvgm_psg_galious_05.h"

// Fonts
#include "font/font_bios_latin.h"
#include "font/font_bios_jap2.h"
#include "font/font_bios_hangul.h"
#include "font/font_bios_cyrillic.h"
#include "font/font_bios_arabic2.h"
#include "font/font_mgl_sample6.h"

// Sprite by GrafxKid (https://opengameart.org/content/super-random-sprites)
#include "content/data_sprt_16or.h"

// Language table
const struct Language g_Language[LANG_MAX] =
{
	{ LANG_JA, g_Font_BIOS_JP2 },
	{ LANG_EN, g_Font_BIOS_EU },
	{ LANG_FR, g_Font_BIOS_EU },
	{ LANG_NL, g_Font_BIOS_EU },
	{ LANG_ES, g_Font_BIOS_EU },

	{ LANG_DE, g_Font_BIOS_EU },
	{ LANG_IT, g_Font_BIOS_EU },
	{ LANG_AR, g_Font_BIOS_ARB2 },
	{ LANG_DA, g_Font_BIOS_EU },

	{ LANG_PT, g_Font_BIOS_EU },
	{ LANG_UK, g_Font_BIOS_Cyril },
	{ LANG_FI, g_Font_BIOS_EU },
	{ LANG_SK, g_Font_BIOS_EU },
};

// Sample level tiles map
const u8 g_TileMap[] =
{
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 136, 137, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 168, 169, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, 132, 133, 134, 135, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, 164, 165, 166, 167, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 132, 133, 134, 135, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 136, 137, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 164, 165, 166, 167, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 168, 169, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 136, 137, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 168, 169, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, 136, 137, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, 168, 169, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 136, 137, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 168, 169, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, 136, 137, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, 168, 169, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,  28,  29, OOO, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,  32,  33,  34,  35, OOO, OOO, OOO, OOO, OOO, OOO,  59,  60,  61,  62, OOO, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO, OOO,  96,  97,  98,  99, OOO, OOO, OOO, OOO, OOO,  90,  91,  92,  93,  94,  95, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO,  32,  33,  34,  35, OOO, OOO, OOO, OOO, OOO, OOO,  64,  65,  66,  67, OOO, OOO, OOO, OOO, OOO, 122, 123, 124, 125, 126, 127, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO,  96,  97,  98,  99, OOO, OOO, OOO, OOO, OOO, OOO,  96,  97,  98,  99, OOO, OOO, OOO, OOO, OOO, 154, 155, 156, 157, 158, 159, OOO, 
	 OOO, OOO, OOO, OOO, OOO, OOO,  64,  65,  66,  67, OOO, OOO, OOO, OOO, OOO, OOO,  64,  65,  66,  67, OOO, OOO, OOO, OOO, OOO, OOO, OOO, 188, 189, OOO, OOO, OOO, 
	  33,  34,  33,  34,  33,  34,   8,  97,  98,  69,  33,  34,  33,  34,  33,  34,   8,  97,  98,  69,  33,  34,  33,  34,  33,  34,  33,  34,  33,  34,  33,  34, 
	  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65, 
	  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97,  98,  97, 
	  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65,  66,  65, 
};

//
const u8 g_TreeTileMap[] =
{
	 OOO, OOO,  28,  29, OOO, OOO,
	 OOO,  59,  60,  61,  62, OOO,
	  90,  91,  92,  93,  94,  95,
	 122, 123, 124, 125, 126, 127,
	 154, 155, 156, 157, 158, 159,
	 OOO, OOO, 188, 189, OOO, OOO,
};

const u8 g_SnowPattern[] =
{
// ---- Layer[0] (16x16 0,0 1,1 inc 2)
// Sprite[0] (offset:0)
	0x40, /* .#...... */ 
	0xE0, /* ###..... */ 
	0x40, /* .#...... */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[1] (offset:8)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[2] (offset:16)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[3] (offset:24)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x01, /* .......# */ 

// ---- Layer[1] (16x16 0,0 1,1 inc 2)
// Sprite[4] (offset:0)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[5] (offset:8)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x08, /* #....... */ 
// Sprite[6] (offset:16)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x04, /* .....#.. */ 
	0x0E, /* ....###. */ 
	0x04, /* .....#.. */ 
// Sprite[7] (offset:24)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 

// ---- Layer[2] (16x16 0,0 1,1 inc 2)
// Sprite[8] (offset:0)
	0x80, /* 1......0 */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[9] (offset:8)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[10] (offset:16)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
// Sprite[11] (offset:24)
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x00, /* ........ */ 
	0x01, /* .......# */ 
};

// Snow fall X coordinate offset
const i8 g_FallOffset[] = 
{
	2,	2,	1,	1,	1,	1,	1,	1,	1,	1,	0,	1,	0,	1,	0,	0,
	0,	0,	0,	-1,	0,	-1,	0,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-2,
	-2,	-2,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	-1,	0,	-1,	0,	-1,	0,	0,
	0,	0,	0,	1,	0,	1,	0,	1,	1,	1,	1,	1,	1,	1,	1,	2
};

// Sprite attribute table addresses
const u16 g_SATAddr[] = { ADDR_SAT1, ADDR_SAT2 };

// Sprites position
const VectorU8 g_SprtPos[] = {
	{  56, 143 },
	{  16, 167 },
	{  96, 167 },
	{ 176, 167 },
	{ 208, 167 },
};

//=============================================================================
// VARIABLES
//=============================================================================

// Sprite attributes
struct VDP_Sprite g_SpriteData0[32];
struct VDP_Sprite g_SpriteData1[32];

// Screen mode setting index
u8 g_VBlank = 0;
u8 g_Frame = 0;
u8 g_State = 0;

//=============================================================================
// FUNCTIONS
//=============================================================================

//-----------------------------------------------------------------------------
// H-Blank handler
void HBlankHandler()
{
	if(g_State)
		VDP_SetSpriteAttributeTable(g_SATAddr[1]);
}

//-----------------------------------------------------------------------------
// H_KEYI interrupt hook
void InterruptHook()
{
	__asm
		// Get S#1
		ld		a, #1
		out		(P_VDP_ADDR), a
		ld		a, #(0x80 + 15)
		out		(P_VDP_ADDR), a
		in		a, (P_VDP_STAT)
		//  Call H-Blank if bit #0 of S#1 is set 
		rrca
		jp		nc, _no_hblank
		call	_HBlankHandler // call to C function HBlankHandler() 
	_no_hblank:
		// Reset R#15 to S#0
		xor		a           		
		out		(P_VDP_ADDR), a
		ld		a, #(0x80 + 15)
		out		(P_VDP_ADDR),a
	__endasm;
}

//-----------------------------------------------------------------------------
// H_TIMI interrupt hook
void VBlankHook()
{
	if(g_State)
		VDP_SetSpriteAttributeTable(g_SATAddr[0]);

	// Update music
	LVGM_Decode();
	PSG_Apply();

	g_VBlank = 1;
}

//-----------------------------------------------------------------------------
// Wait for V-Blank period
void WaitVBlank()
{
	while(g_VBlank == 0) {}
	g_VBlank = 0;
	g_Frame++;
}

//-----------------------------------------------------------------------------
//
void SetCurrentSAT(u8 idx)
{
	g_SpriteAtributeLow = g_SATAddr[idx];
	g_SpriteAtributeHigh = 0;
	g_SpriteColorLow = g_SpriteAtributeLow - 0x200;
	g_SpriteColorHigh = 0;
}

//-----------------------------------------------------------------------------
//
void UpdateSAT0()
{
	SetCurrentSAT(0);
	u8 offset = g_Frame >> 1;
	loop(j, 32)
	{
		struct VDP_Sprite* sprt = &g_SpriteData0[j];
		sprt->X += g_FallOffset[offset & 0x3F];
		offset += 2;
		sprt->Y = (sprt->Y + 1) & 0x7F;
	}
	VDP_WriteVRAM((const u8*)g_SpriteData0, g_SpriteAtributeLow, g_SpriteAtributeHigh, 32 * 4);
}

//-----------------------------------------------------------------------------
//
void UpdateSAT1()
{
	SetCurrentSAT(1);
	u8 anim = (g_Frame / 4) % 6;
	loop(j, 5)
	{
		u8 i = j * 2;
		u8 pat = PATTERN_16OR_1ST + (anim * 4);
		g_SpriteData1[i + 0].Pattern = pat;
		g_SpriteData1[i + 1].Pattern = pat + (6 * 4);
	}
	VDP_WriteVRAM((const u8*)g_SpriteData1, g_SpriteAtributeLow, g_SpriteAtributeHigh, 32 * 4);
}

//-----------------------------------------------------------------------------
/// Program entry point
void main()
{
	// Initialize screen mode
	VDP_SetMode(VDP_MODE_SCREEN5);
	VDP_SetColor(1);
	VDP_EnableDisplay(FALSE);
	VDP_SetLayoutTable(ADDR_LAYOUT);
	VDP_SetSpriteAttributeTable(ADDR_SAT1);
	VDP_SetSpritePatternTable(ADDR_SPT);
	VDP_ClearVRAM();
	VDP_SetPage(0);
	VDP_SetLineCount(VDP_LINE_212);
	VDP_SetFrequency(VDP_FREQ_60HZ);

	// Load tiles data
	Tile_SetBankPage(2);
	Tile_FillBank(0, 6);
	Tile_FillBank(1, 7);
	Tile_FillBank(2, 8);
	Tile_FillBank(3, 9);
	Tile_LoadBank(0, g_DataBG4b, sizeof(g_DataBG4b) / TILE_CELL_BYTES);
	Tile_LoadBank(2, g_DataBG4b, sizeof(g_DataBG4b) / TILE_CELL_BYTES);
	for(u8 i = 0; i < 15; ++i)
		VDP_SetPaletteEntry(i + 1, *(u16*)&g_DataBG4b_palette[i*2]);

	// Draw background
	Tile_SetDrawPage(0);
	Tile_SelectBank(0);
	Tile_FillScreen(6);
	Tile_DrawMapChunk( 0, 17, g_TreeTileMap, 6, 6); // Draw tree tilemap
	Tile_DrawMapChunk( 3, 17, g_TreeTileMap, 6, 6);
	Tile_DrawMapChunk(11, 17, g_TreeTileMap, 6, 6);
	Tile_DrawScreen(g_TileMap); // Draw the whole screen tilemap
	Tile_DrawBlock(10, 8, 4, 4, 4, 2); // Draw a cloud (4x2 tiles)

	// Initialize music
	LVGM_Play(g_lVGM_psg_galious_05, TRUE);

	// Initialize interruption handler
	Bios_SetHookCallback(H_TIMI, VBlankHook);
	Bios_SetHookCallback(H_KEYI, InterruptHook);
	VDP_EnableVBlank(TRUE);
	VDP_EnableHBlank(TRUE);
	VDP_SetHBlankLine(SPLIT_LINE);
	VDP_SetColor(6);
	VDP_EnableDisplay(TRUE);

	// Draw texts
	Loc_Initialize(g_LocData, TEXT_MAX);
	loop(i, LANG_MAX)
	{
		Print_SetBitmapFont(g_Language[i].Font);
		Print_SetOutline(TRUE, 5);
		Print_SetColor(9, 0);

		u8 x = 127;
		u8 y =  8 + (i * 11);
		Loc_SetLanguage(g_Language[i].Code);

		Print_DrawTextAlignAt(x, y, Loc_GetText(TEXT_TITLE), PRINT_ALIGN_CENTER);
	}
	Print_SetBitmapFont(g_Font_MGL_Sample6);
	Print_SetMode(PRINT_MODE_BITMAP_TRANS);
	Print_SetColor(5, 0);
	Print_DrawTextAt(1, 203, MSX_GL);

	// Initialize Sprite
	VDP_EnableSprite(TRUE);
	VDP_SetSpriteFlag(VDP_SPRITE_SIZE_16);
	VDP_LoadSpritePattern(g_SnowPattern, 0, 4 * 3);
	SetCurrentSAT(0);
	loop(j, 32)
	{
		struct VDP_Sprite* sprt = &g_SpriteData0[j];
		sprt->X = Math_GetRandom8();
		sprt->Y = Math_GetRandom8() / 2;
		switch(j % 3)
		{
		case 0:
			sprt->Pattern = 0;
			sprt->Color = 9;
			break;
		case 1:
			sprt->Pattern = 4;
			sprt->Color = 9;
			break;
		default:
			sprt->Pattern = 8;
			sprt->Color = 3;
			break;
		}
		VDP_SetSpriteExUniColor(j, sprt->X, sprt->Y, sprt->Pattern, sprt->Color);
	}
	u8 chrSprt = PATTERN_16OR_1ST;
	loop(i, 6)
	{
		VDP_LoadSpritePattern(g_DataSprt16or + (i * 2 +  0) * 8, chrSprt++, 1);
		VDP_LoadSpritePattern(g_DataSprt16or + (i * 2 + 12) * 8, chrSprt++, 1);
		VDP_LoadSpritePattern(g_DataSprt16or + (i * 2 +  1) * 8, chrSprt++, 1);
		VDP_LoadSpritePattern(g_DataSprt16or + (i * 2 + 13) * 8, chrSprt++, 1);	
	}
	loop(i, 6)
	{
		VDP_LoadSpritePattern(g_DataSprt16or + (i * 2 + 24) * 8, chrSprt++, 1);
		VDP_LoadSpritePattern(g_DataSprt16or + (i * 2 + 36) * 8, chrSprt++, 1);
		VDP_LoadSpritePattern(g_DataSprt16or + (i * 2 + 25) * 8, chrSprt++, 1);
		VDP_LoadSpritePattern(g_DataSprt16or + (i * 2 + 37) * 8, chrSprt++, 1);
	}
	SetCurrentSAT(1);
	loop(j, 5)
	{
		u8 x = g_SprtPos[j].x;
		u8 y = g_SprtPos[j].y;
		u8 i = j * 2;

		struct VDP_Sprite* sprt = &g_SpriteData1[i];
		sprt->X = x;
		sprt->Y = y;
		sprt->Pattern = PATTERN_16OR_1ST + 0 * 4;
		sprt->Color = 14;
		VDP_SetSpriteExUniColor(i, sprt->X, sprt->Y, sprt->Pattern, sprt->Color);

		i++;
		sprt = &g_SpriteData1[i];
		sprt->X = x;
		sprt->Y = y;
		sprt->Pattern = PATTERN_16OR_1ST + 6 * 4;
		sprt->Color = VDP_SPRITE_CC + 1;
		VDP_SetSpriteExUniColor(i, sprt->X, sprt->Y, sprt->Pattern, sprt->Color);
	}

	// Main loop
	g_State = 1;
	while(!Keyboard_IsKeyPressed(KEY_ESC))
	{
		// Wait V-Blank
		WaitVBlank();

		// Update sprites
		if((g_Frame & 1) == 0)
			UpdateSAT0();
		else
			UpdateSAT1();
	}

	Bios_ClearHook(H_KEYI);
	Bios_ClearHook(H_TIMI);
	Bios_Exit(0);
}