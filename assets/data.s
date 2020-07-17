
	incdir	'wrk:AlterEgo/assets'

	wb data.bin

assetsBeg:
	dc.l	copper-assetsBeg
	dc.l	fonts8-assetsBeg
	dc.l	sprites-assetsBeg
assetsEnd

copper:		incbin	'raw-packed/copper.shr'
fonts8:		incbin	'raw-packed/fonts8x8x2.shr'
sprites:	incbin	'raw-packed/sprites.shr'