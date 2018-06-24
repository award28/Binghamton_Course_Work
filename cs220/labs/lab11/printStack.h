#ifndef INCLUDE_PRINTSTACK_H
#define INCLUDE_PRINTSTACK_H

#define SAVE_BASE_POINTER main_base=ebp
#define printStack(NP) printFrameStack(esp,ebp,NP,"")
#define printFrame(NP) printStackFrame(esp,ebp,NP)

struct nframe { // moving up from baseptr...
		struct nframe * prev_nframe;
		void * return_addr;
		void * parms[];
};


typedef struct nframe* baseptr;
typedef void ** stackptr;

baseptr main_base;
register baseptr ebp asm ("ebp");
register stackptr esp asm ("esp");

void printFrameStack(stackptr sp, baseptr bp, int nparms, char *prefix);
void printStackFrame(stackptr sp,baseptr bp,int nparms);

#endif
