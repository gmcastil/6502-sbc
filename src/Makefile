VASM	= vasm6502_oldstyle

basic.bin: basic.s
	$(VASM) -Fbin -dotdir -o basic.bin basic.s

.PHONY:
clean:
	rm -fv a.out
	rm -fv basic.bin

