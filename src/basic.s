; Demonstrate assembling and loading a basic 6502 program

  .org	$8000

reset:
  lda	#$ff
  sta	$6002


loop:
  lda	#$55
  sta	$6000

  lda	#$aa
  sta	$6000

  jmp	loop

  .org	$fffc
  .word reset

; Pad this out to the end of the 32KB
  .word $0000

