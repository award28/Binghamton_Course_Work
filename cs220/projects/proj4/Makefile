test : grades 
	./grades <test.txt

grades: grades.c
	gcc -m32 -g -o grades grades.c
	
grades.objd.txt : grades
	objdump -d grades >grades.objd.txt
	
gdb : grades 
	gdb -x dbg_cmds.txt grades
	
clean:  
	-rm grades grades.objd.txt
