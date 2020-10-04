/* autogenerated file */

#ifndef ALTEREGO_SIZES_H
#define ALTEREGO_SIZES_H

/*--------------------------------------------------------------------------*/
// CHIP SIZES
#define SCREEN_SIZE 40960
#define COPPER_SIZE 104
#define MUSIC_SIZE (61594)
#define SFX_SIZE (67735)
#define BOBS (1024)

// sprites in chip
// 8 bytes - fake sprite 
#define SPRITES_FAKE 8

// 18 * 4 * 2 - hero and ego sprite
#define SPRITES_HERO 18*4
#define SPRITES_EGO 18*4

// 18 * 4 * 8 - enemies sprites
#define SPRITES_ENEMIES 18*4*8

//#define SPRITES_SIZE 728

#define MEMORY_CHIP_SIZE (200*1024)

//ANY MEMORY SIZES

#define CREDITS_COLORS_SIZE 32
#define CREDITS_TEXTS_SIZE 124


#define PALETTE_SIZE (64)
#define FONTS8_SIZE (656)
#define FONTS16 (864)
#define TILES_SIZE (8192)
#define FREE4KB (4096)
#define LEVEL_SIZE (2562)
#define GFX_SPRITES_SIZE 1856

#define PACKED_MUSIC (62864)

#define PACKED_SFX (28624)
#define PACKED_LVL (20480)

#define SFX_AMOUNT 14

// ASSETS

#define DECOMPRESS_STACK_SIZE (1024*5)

#define ASSETS_SIZE 99640


#define MEMORY_OTHER_SIZE (150*1024)


/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_SIZES_H */
