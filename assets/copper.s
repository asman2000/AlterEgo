
	incdir	'includes:'
	include	'hardware/custom.i'

	auto	wb\copper.bin

copperBeg
		dc.w	bplpt,0,bplpt+2,0
		dc.w	bplpt+4,0,bplpt+6,0
		dc.w	bplpt+8,0,bplpt+10,0
		dc.w	bplpt+12,0,bplpt+14,0

		dc.w	$1007,$fffe

		dc.w	sprpt,0,sprpt+2,0
		dc.w	sprpt+4,0,sprpt+6,0
		dc.w	sprpt+8,0,sprpt+10,0
		dc.w	sprpt+12,0,sprpt+14,0
		dc.w	sprpt+16,0,sprpt+18,0
		dc.w	sprpt+20,0,sprpt+22,0
		dc.w	sprpt+24,0,sprpt+26,0
		dc.w	sprpt+28,0,sprpt+30,0
		dc.w	$ffff,$fffe
copperEnd	
