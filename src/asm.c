/**
 * File: asm.c
 * Date: Nov 20, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "parse.h"
#include "symtab.h"
#include "quad.h"
#include "asm.h"

/* current level */
int lvl;
/* current length of var region */
int varc;
/* current length of tmp region */
int tmpc;
/* current length of parameter region */
int parac;

void enter(SymTabESP e)
{
	SymTabSP st;
	if (e == NULL) {
		fprintf(errlist, "ASM BUG:25\n");
		exit(1);
	}
	if (e->obj == Fun_Obj_t || e->obj == Proc_Obj_t) {
		st = e->stp;
		if (st == NULL) {
			fprintf(asmlist, "ASM BUG:32\n");
			abort();
		}
		lvl = st->level;
		varc = st->posi_var;
		tmpc = st->posi_tmp;
		parac = st->posi_para;
		fprintf(asmlist, "\tsub\tesp, %d\n", RESERVED);
	} else {
		fprintf(asmlist, "ASM BUG:34\n");
	}
}

void movRM_asm(char *reg, SymTabESP e)
{
	switch (e->obj) {
	case Var_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t%s, [ebp - %d]\t; %s\n", 
				reg, VAROFFSET, e->label);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\n",
				DISPLAY);
			fprintf(asmlist, "\tmov\t%s, [esi - %d]\t; %s\n",
				reg, VAROFFSET, e->label);
		} else {
			fprintf(errlist, "ASM BUG:68\n");
		}
		break;
	case Tmp_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t%s, [ebp - %d]\t; %s\n",
				reg, TMPOFFSET, e->label);
		} else {
			fprintf(errlist, "ASM BUG:76");
		}
		break;
	case Para_Val_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t%s, [ebp + %d]\t; %s\n",
				reg, PARAOFFSET, e->label);
		} else {
			fprintf(errlist, "ASM BUG:107\n");
		}
		break;
	case Para_Ref_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\n", 
				PARAOFFSET);
			fprintf(asmlist, "\tmov\t%s, [esi]\t; *%s\n", 
				reg, e->label);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tedi, [ebp + %d]\t; display\n", 
				DISPLAY);
			fprintf(asmlist, "\tmov\tesi, [edi + %d]\n",
				PARAOFFSET);
			fprintf(asmlist, "\tmov\t%s, [esi]\t; *%s\n",
				reg, e->label);
		} else {
			fprintf(errlist, "ASM BUG:85\n");
		}
		break;
	case Num_Obj_t:
		fprintf(asmlist, "\tmov\t%s, %s\n", reg, e->label);
		break;
	default:
		fprintf(errlist, "ASM BUG:88\n");
	}
}

void leaRM_asm(char *reg, SymTabESP e)
{
	switch (e->obj) {
	case Var_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tlea\t%s, [ebp - %d]\t; %s\n", 
				reg, VAROFFSET, e->label);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\t; %s\n",
				DISPLAY, e->label);
			fprintf(asmlist, "\tlea\t%s, [esi - %d]\n",
				reg, VAROFFSET);
		} else {
			fprintf(errlist, "ASM BUG:109\n");
		}
		break;
	default:
		fprintf(errlist, "ASM BUG:88\n");
	}
}

void movMR_asm(SymTabESP e, char *reg)
{
	switch (e->obj) {
	case Var_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t[ebp - %d], %s\t; %s\n",
				VAROFFSET, reg, e->label);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\t; display var\n",
				DISPLAY);
			fprintf(asmlist, "\tmov\t[esi - %d], %s\t; %s\n",
				VAROFFSET, reg, e->label);
		} else {
			fprintf(errlist, "ASM BUG:106\n");
		}
		break;
	case Tmp_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t[ebp - %d], %s\t; %s\n",
				TMPOFFSET, reg, e->label);
		} else {
			fprintf(errlist, "ASM BUG:113");
		}
		break;
	case Para_Val_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\t[ebp + %d], %s\t; %s\n",
				PARAOFFSET, reg, e->label);
		} else {
			fprintf(errlist, "ASM BUG:117\n");
		}
		break;
	case Para_Ref_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\n",
				PARAOFFSET);
			fprintf(asmlist, "\tmov\t[esi], %s\t\t; *%s\n",
				reg, e->label);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tedi, [ebp + %d]\t; display para ref\n", 
				DISPLAY);
			fprintf(asmlist, "\tmov\tesi, [edi + %d]\n",
				PARAOFFSET);
			fprintf(asmlist, "\tmov\t[esi], %s\t\t; *%s\n",
				reg, e->label);
		} else {
			fprintf(errlist, "ASM BUG:143\n");
		}
		break;
	default:
		fprintf(errlist, "ASM BUG:126\n");
	}
}

void movRA_asm(SymTabESP e, char *offsetreg, char *reg)
{
	switch (e->obj) {
	case Array_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tlea\tedi, [ebp - %d]\t; %s\n",
				VAROFFSET, e->label);
			fprintf(asmlist, "\timul\t%s, %s, 4\n",
				offsetreg, offsetreg);
			fprintf(asmlist, "\tsub\tedi, %s\n", offsetreg);
			fprintf(asmlist, "\tmov\t%s, [edi]\n", reg);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\t; display array\n",
				DISPLAY);
			fprintf(asmlist, "\tlea\tedi, [esi - %d]\t; %s\n",
				VAROFFSET, e->label);
			fprintf(asmlist, "\timul\t%s, %s, 4\n",
				offsetreg, offsetreg);
			fprintf(asmlist, "\tsub\tedi, %s\n", offsetreg);
			fprintf(asmlist, "\tmov\t%s, [edi]\n", reg);
		}
		break;
	default:
		fprintf(asmlist, "ASM BUG:143\n");
	}
}

void movAR_asm(SymTabESP e, char *offsetreg, char *reg)
{
	switch (e->obj) {
	case Array_Obj_t:
		if (e->level == lvl) {
			fprintf(asmlist, "\tlea\tedi, [ebp - %d]\t; %s\n",
				VAROFFSET, e->label);
			fprintf(asmlist, "\timul\t%s, %s, 4\n",
				offsetreg, offsetreg);
			fprintf(asmlist, "\tsub\tedi, %s\n", offsetreg);
			fprintf(asmlist, "\tmov\t[edi], %s\n", reg);
		} else if (e->level < lvl) {
			fprintf(asmlist, "\tmov\tesi, [ebp + %d]\n",
				DISPLAY);
			fprintf(asmlist, "\tlea\tedi, [esi - %d]\t; %s\n",
				VAROFFSET, e->label);
			fprintf(asmlist, "\timul\t%s, %s, 4\n",
				offsetreg, offsetreg);
			fprintf(asmlist, "\tsub\tedi, %s\n", offsetreg);
			fprintf(asmlist, "\tmov\t[edi], %s\n", reg);
		}
		break;
	default:
		fprintf(asmlist, "ASM BUG:143\n");
	}
}

void movRR_asm(char *reg, char *reg2)
{
	fprintf(asmlist, "\tmov\t%s, %s\n", reg, reg2);
}

void movRI_asm(char *reg, int imm)
{
	fprintf(asmlist, "\tmov\t%s, %d\n", reg, imm);
}

void addRI_asm(char *reg, int imm)
{
	fprintf(asmlist, "\tadd\t%s, %d\n", reg, imm);
}

void addRR_asm(char *reg, char *reg2)
{
	fprintf(asmlist, "\tadd\t%s, %s\n", reg, reg2);
}

void subRR_asm(char *reg, char *reg2)
{
	fprintf(asmlist, "\tsub\t%s, %s\n", reg, reg2);
}

void neg_asm(char *reg)
{
	fprintf(asmlist, "\tneg\t%s\n", reg);
}

void inc_asm(char *reg)
{
	fprintf(asmlist, "\tinc\t%s\n", reg);
}

void dec_asm(char *reg)
{
	fprintf(asmlist, "\tdec\t%s\n", reg);
}

void pusha_asm(SymTabESP e)
{
	fprintf(asmlist, "\tpush\t%s\n", e->label);
}

void pushR_asm(char *reg)
{
	fprintf(asmlist, "\tpush\t%s\n", reg);
}

void pop_asm(char *reg)
{
	fprintf(asmlist, "\tpop\t%s\n", reg);
}

void call_asm(SymTabESP e)
{
	int i, offset;
	int enterlevel = e->level+1;
	if (enterlevel <= lvl) {
		// fprintf(asmlist, "\tpush\tebp\t\t; display new\n");
		for (i = 0; i < enterlevel-1; i++) {
			offset = 4 * ( 2 + enterlevel-1 - i);
			fprintf(asmlist, "\tmov\tedi, [ebp + %d]\n",
				offset);
			fprintf(asmlist, "\tpush\tedi\t\t; display new\n");
		}
		fprintf(asmlist, "\tcall\t%s\n", e->label);
		offset = 4 * (e->stp->posi_para + enterlevel-1);
		fprintf(asmlist, "\tadd\tesp, %d\n", offset);
	} else if (enterlevel == lvl+1) {
		fprintf(asmlist, "\tpush\tebp\t\t; display new\n");
		for (i = 0; i < lvl-1; i++) {
			offset = 4 * ( 2 + lvl-1 - i);
			fprintf(asmlist, "\tmov\tedi, [ebp + %d]\n",
				offset);
			fprintf(asmlist, "\tpush\tedi\t\t; display low level\n");
		}
		fprintf(asmlist, "\tcall\t%s\n", e->label);
		offset = 4 * (e->stp->posi_para + enterlevel-1);
		fprintf(asmlist, "\tadd\tesp, %d\n", offset);
	} else {
		fprintf(errlist, "ASM BUG:186\n");
	}
}

void ret_asm(void)
{
	fprintf(asmlist, "\tret\n");
}

void label_asm(SymTabESP e)
{
	if (e->obj == Fun_Obj_t || e->obj == Proc_Obj_t) {
		fprintf(asmlist, "\nSECTION .TEXT\n");
		fprintf(asmlist, "\tGLOBAL %s\n", e->label);
		fprintf(asmlist, "%s:\n", e->label);
	} else if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "%s:\n", e->label);
	}
}

void jmp_asm(SymTabESP e)
{
	if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "\tjmp\t%s\n", e->label);
	} else {
		fprintf(errlist, "ASM BUG:264\n");
	}
}

void cmpRR_asm(char *reg, char *reg2)
{
	fprintf(asmlist, "\tcmp\t%s, %s\t\n", reg, reg2);
}

void jz_asm(SymTabESP e)
{
	if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "\tjz\t%s\n", e->label);
	} else {
		fprintf(errlist, "ASM BUG:283\n");
	}
}

void jnz_asm(SymTabESP e)
{
	if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "\tjnz\t%s\n", e->label);
	} else {
		fprintf(errlist, "ASM BUG:292\n");
	}
}

void jg_asm(SymTabESP e)
{
	if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "\tjg\t%s\n", e->label);
	} else {
		fprintf(errlist, "ASM BUG:300\n");
	}
}

void jng_asm(SymTabESP e)
{
	if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "\tjng\t%s\n", e->label);
	} else {
		fprintf(errlist, "ASM BUG:310\n");
	}
}

void jl_asm(SymTabESP e)
{
	if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "\tjl\t%s\n", e->label);
	} else {
		fprintf(errlist, "ASM BUG:319\n");
	}
}

void jnl_asm(SymTabESP e)
{
	if (e->obj == Label_Obj_t) {
		fprintf(asmlist, "\tjnl\t%s\n", e->label);
	} else {
		fprintf(errlist, "ASM BUG:328\n");
	}
}

void retval_asm(char *reg)
{
	fprintf(asmlist, "\tmov\t[ebp - 4], %s\t; set return value\n", reg);
}