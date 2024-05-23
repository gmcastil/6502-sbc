;; Demonstrate assembling and loading a basic 6502 program

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

  .org	$9000
irq:
  nop

  .org	$a000
nmi:
nop

  ;; IRQ handler vector
  .org	$fffa
  .word	irq

  ;; Reset vector
  .org	$fffc
  .word reset

  ;; NMI handler vector
  .org	$fffe
  .word nmi

