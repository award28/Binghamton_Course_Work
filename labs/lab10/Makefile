test: target testhex.txt
	./target <testhex.txt
	
showTest : testhex.txt
	od -t x1z testhex.txt	
	
showXmp : xmphex.txt 
	od -t x1z xmphex.txt
	
testhex.txt : test.txt makeHex
	./makeHex <test.txt >testhex.txt
	
xmphex.txt : xmp.txt makeHex
	./makeHex <xmp.txt >xmphex.txt

target : target.c
	gcc -g -Wall -m32 -o target target.c
	
makeHex : makeHex.c
	gcc -g -Wall -m32 -o makeHex makeHex.c	
	
gdb: target testhex.txt
	gdb -x gdb_cmds.txt target	
	
target.asm.txt : target
	objdump -d target >target.asm.txt	
		
clean:
	-rm target target.asm.txt testhex.txt xmphex.txt makeHex
