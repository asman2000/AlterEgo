
	incdir	'wrk:AlterEgo/assets'

	wb data.bin


assetsBeg:
	dc.l	copper-assetsBeg
	dc.l	fonts8-assetsBeg
	dc.l	sprites-assetsBeg
	dc.l	creditsColors-assetsBeg
	dc.l	creditsTxt-assetsBeg
	dc.l	sfx00-assetsBeg
	dc.l	sfx01-assetsBeg
	dc.l	sfx02-assetsBeg
	dc.l	sfx03-assetsBeg
	dc.l	sfx04-assetsBeg
	dc.l	sfx05-assetsBeg
	dc.l	sfx06-assetsBeg
	dc.l	sfx07-assetsBeg
	dc.l	sfx08-assetsBeg
	dc.l	sfx09-assetsBeg
	dc.l	sfx10-assetsBeg
	dc.l	sfx11-assetsBeg
	dc.l	sfx12-assetsBeg
	dc.l	sfx13-assetsBeg
	dc.l	sfx14-assetsBeg


assetsEnd

copper:		incbin	'raw-packed/copper.shr'
fonts8:		incbin	'raw-packed/fonts8x8x2.shr'
sprites:	incbin	'raw-packed/sprites.shr'

creditsColors:	incbin	'raw-packed/credits-colors16.shr'
creditsTxt:	incbin	'raw-packed/credits-txt.shr'

sfx00:		incbin	'raw-packed/sfx-00.shr'
sfx01:		incbin	'raw-packed/sfx-01.shr'
sfx02:		incbin	'raw-packed/sfx-02.shr'
sfx03:		incbin	'raw-packed/sfx-03.shr'
sfx04:		incbin	'raw-packed/sfx-04.shr'
sfx05:		incbin	'raw-packed/sfx-05.shr'
sfx06:		incbin	'raw-packed/sfx-06.shr'
sfx07:		incbin	'raw-packed/sfx-07.shr'
sfx08:		incbin	'raw-packed/sfx-08.shr'
sfx09:		incbin	'raw-packed/sfx-09.shr'
sfx10:		incbin	'raw-packed/sfx-10.shr'
sfx11:		incbin	'raw-packed/sfx-11.shr'
sfx12:		incbin	'raw-packed/sfx-12.shr'
sfx13:		incbin	'raw-packed/sfx-13.shr'
sfx14:		incbin	'raw-packed/sfx-14.shr'

