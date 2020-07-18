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
// 18 * 4 * 2 - hero and ego sprite
// 18 * 4 * 8 - enemies sprites
#define SPRITES_SIZE 728

#define MEMORY_CHIP_SIZE (200*1024)

//ANY MEMORY SIZES
#define PALETTE (64)
#define FONTS8 (656)
#define FONTS16 (864)
#define TILES (8192)
#define FREE4KB (4096)
#define LEVEL (2562)
#define GFX_SPRITES_SIZE 1856

#define PACKED_MUSIC (62864)

#define PACKED_SFX (29088)
#define PACKED_LVL (20480)

#define MEMORY_OTHER_SIZE (150*1024)


// ASSETS

#define ASSETS_SIZE 29920

/*--------------------------------------------------------------------------*/

#endif /* ALTEREGO_SIZES_H */
