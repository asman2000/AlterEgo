
	incdir	'wrk:AlterEgo/assets/raw-packed/'

	auto	wb data.bin


assetsBeg:
	dc.l	copper-assetsBeg
	dc.l	fonts8-assetsBeg
	dc.l	sprites-assetsBeg
	dc.l	creditsColors-assetsBeg
	dc.l	creditsTxt-assetsBeg

	dc.l	sfx-assetsBeg

	dc.l	tiles-assetsBeg
	dc.l	world0Colors-assetsBeg
	dc.l	world00-assetsBeg
	dc.l	world01-assetsBeg
	dc.l	world02-assetsBeg
	dc.l	world03-assetsBeg
	dc.l	world04-assetsBeg

	dc.l	world1Colors-assetsBeg
	dc.l	world10-assetsBeg
	dc.l	world11-assetsBeg
	dc.l	world12-assetsBeg
	dc.l	world13-assetsBeg
	dc.l	world14-assetsBeg

	dc.l	world2Colors-assetsBeg
	dc.l	world20-assetsBeg
	dc.l	world21-assetsBeg
	dc.l	world22-assetsBeg
	dc.l	world23-assetsBeg
	dc.l	world24-assetsBeg

	dc.l	world3Colors-assetsBeg
	dc.l	world30-assetsBeg
	dc.l	world31-assetsBeg
	dc.l	world32-assetsBeg
	dc.l	world33-assetsBeg
	dc.l	world34-assetsBeg

	dc.l	world4Colors-assetsBeg
	dc.l	world40-assetsBeg
	dc.l	world41-assetsBeg
	dc.l	world42-assetsBeg
	dc.l	world43-assetsBeg
	dc.l	world44-assetsBeg

	; dc.l	sfx00-assetsBeg
	; dc.l	sfx01-assetsBeg
	; dc.l	sfx02-assetsBeg
	; dc.l	sfx03-assetsBeg
	; dc.l	sfx04-assetsBeg
	; dc.l	sfx05-assetsBeg
	; dc.l	sfx06-assetsBeg
	; dc.l	sfx07-assetsBeg
	; dc.l	sfx08-assetsBeg
	; dc.l	sfx09-assetsBeg
	; dc.l	sfx10-assetsBeg
	; dc.l	sfx11-assetsBeg
	; dc.l	sfx12-assetsBeg
	; dc.l	sfx13-assetsBeg
	; dc.l	sfx14-assetsBeg

copper:		incbin	'copper.shr'
fonts8:		incbin	'fonts8x8x2.shr'
sprites:	incbin	'sprites.shr'

creditsColors:	incbin	'credits-colors16.shr'
creditsTxt:	incbin	'credits-txt.shr'

sfx:		incbin	'sfx.shr'

tiles:		incbin	'tiles.shr'
world0Colors:	incbin	'world0-colors32.shr'
world00:	incbin	'world0-0.shr'
world01:	incbin	'world0-1.shr'
world02:	incbin	'world0-2.shr'
world03:	incbin	'world0-3.shr'
world04:	incbin	'world0-4.shr'

world1Colors:	incbin	'world1-colors32.shr'
world10:	incbin	'world1-0.shr'
world11:	incbin	'world1-1.shr'
world12:	incbin	'world1-2.shr'
world13:	incbin	'world1-3.shr'
world14:	incbin	'world1-4.shr'

world2Colors:	incbin	'world2-colors32.shr'
world20:	incbin	'world2-0.shr'
world21:	incbin	'world2-1.shr'
world22:	incbin	'world2-2.shr'
world23:	incbin	'world2-3.shr'
world24:	incbin	'world2-4.shr'

world3Colors:	incbin	'world3-colors32.shr'
world30:	incbin	'world3-0.shr'
world31:	incbin	'world3-1.shr'
world32:	incbin	'world3-2.shr'
world33:	incbin	'world3-3.shr'
world34:	incbin	'world3-4.shr'

world4Colors:	incbin	'world4-colors32.shr'
world40:	incbin	'world4-0.shr'
world41:	incbin	'world4-1.shr'
world42:	incbin	'world4-2.shr'
world43:	incbin	'world4-3.shr'
world44:	incbin	'world4-4.shr'

; sfx00:		incbin	'raw-packed/sfx-00.shr'
; sfx01:		incbin	'raw-packed/sfx-01.shr'
; sfx02:		incbin	'raw-packed/sfx-02.shr'
; sfx03:		incbin	'raw-packed/sfx-03.shr'
; sfx04:		incbin	'raw-packed/sfx-04.shr'
; sfx05:		incbin	'raw-packed/sfx-05.shr'
; sfx06:		incbin	'raw-packed/sfx-06.shr'
; sfx07:		incbin	'raw-packed/sfx-07.shr'
; sfx08:		incbin	'raw-packed/sfx-08.shr'
; sfx09:		incbin	'raw-packed/sfx-09.shr'
; sfx10:		incbin	'raw-packed/sfx-10.shr'
; sfx11:		incbin	'raw-packed/sfx-11.shr'
; sfx12:		incbin	'raw-packed/sfx-12.shr'
; sfx13:		incbin	'raw-packed/sfx-13.shr'
; sfx14:		incbin	'raw-packed/sfx-14.shr'

assetsEnd
