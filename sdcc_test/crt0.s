	.module crt0
	.globl	_main

	.area	_HEADER (ABS)

	.org 	0x0
init:
	ld	sp,#0x0040
	call	_main

;	;; Ordering of segments for the linker.
;	.area   _HOME
;	.area	_CODE
;	.area   _INITIALIZER
;	.area   _GSINIT
;	.area   _GSFINAL
;	.area	_DATA
;	.area   _INITIALIZED
;	.area   _BSEG
;	.area   _BSS
;	.area   _HEAP
