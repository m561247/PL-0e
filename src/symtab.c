/**
 * File: symtab.c
 * Date: Nov 12, 2013
 * Author: Jeanhwea
 */

#include "global.h"
#include "util.h"
#include "parse.h"
#include "symtab.h"
#include "nspace.h"
/* hash size */
int HASHSIZE = 211;
/* hash shift */
int SHIFT = 4;

/* point to the topest symbol table */
static SymTabSP TOP = NULL;
/* point to saved symbol table list */
/*
 *static SymTabSP savedSTAB = NULL;
 *static SymTabSP savedSTABhead = NULL;
 */
/* hold current level */
static int LEVEL = 0;

/* for generate quad */
/* hold the number of current tmp variable */
static int tmpcount = 0;
/* hold the number of current label */
static int labelcount = 0;
/* a string buffer for store tmp and label */
static char stringBuf[100];

SymTabSP newstab(void)
{
	SymTabSP st;
	int i;
	NEWSYMTAB(st);
	for (i = 0; i < HASHSIZE; i++) {
		/* initial symtab */
		*(st->sbp + i) = NULL;
	}
	st->posi_var = 0;
	st->posi_para = 0;
	st->posi_tmp = 0;
	st->level = ++LEVEL;
	return st;
}

SymTabSP pop(void)
{
	SymTabSP t;
	if (TOP != NULL) {
		t = TOP;
		TOP = t->prev;
		if (TOP != NULL)
			TOP->next = NULL;
	} else t = NULL;
	--LEVEL;
	return t;
}

void push(SymTabSP t)
{
	t->next = NULL;
	t->prev = TOP;
	if (TOP != NULL)
		TOP->next = t;
	TOP = t;
}

static char *genLabel(void)
{
	char *l;
	int n;
	sprintf(stringBuf, "%d", ++labelcount);
	n = strlen(stringBuf);
	l = (char *) malloc( (n + 5) * sizeof(char));
	if (l == NULL) {
		fprintf(errlist, "OUTOFMEM: in genLabel\n");
		return NULL;
	}
	strcpy(l,"..@l");
	strcat(l,stringBuf);
	return l;
}

static char *genTmp(void)
{
	char *l;
	int n;
	sprintf(stringBuf, "%d", ++tmpcount);
	n = strlen(stringBuf);
	l = (char *) malloc( (n + 2) * sizeof(char));
	if (l == NULL) {
		fprintf(errlist, "OUTOFMEM: in genTmp\n");
		return NULL;
	}
	strcpy(l,"&");
	strcat(l,stringBuf);
	return l;
}

static char *mkUsi(int inte)
{
	char *l;
	int n;
	sprintf(stringBuf, "%x", inte);
	n = strlen(stringBuf);
	l = (char *) malloc( (n + 3) * sizeof(char));
	if (l == NULL) {
		fprintf(errlist, "OUTOFMEM: in mkUsi\n");
		return NULL;
	}
	strcpy(l,"0x");
	strcat(l,stringBuf);
	return l;
}

static inline int hash(char *key)
{
	int h = 0;
	int i;
	if (key == NULL) {
		fprintf(errlist, "an error hash key\n");
		return h;
	}
	for (i = 0; key[i] != '\0'; i++) {
		h = ((h << SHIFT) + key[i]) % HASHSIZE;
	}
	return h;
}

void sym_insert(SymBucketSP bp, SymTabSP st)
{
	int h;
	SymBucketSP p;
	SymBucketSP *head;
	if (bp == NULL || st == NULL) {
		fprintf(errlist, "SYMTAB BUG:50\n");
		return ;
	}
	h = hash(bp->ep->name);
	head = st->sbp + h;
	for (p = *head; p != NULL; p = p->next) {
		if (!strcmp(bp->ep->name, p->ep->name))
			break;
	}
	if (p == NULL) {
		bp->next = *head;
		*head = bp;
	} else {
		bp->next = *head;
		*head = bp;
		fprintf(tiplist, "\n************ duplicated insert ************\n");
	}
}

SymTabESP sym_insert_const(IdentSP idp)
{
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	int h = hash(idp->name);
	if (TOP == NULL) 
		fprintf(errlist, "SYMTAB BUG:57\n");
	for (p = *(TOP->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = Nappend(idp->name);
		e->val = idp->val;
		e->lines = l;
		e->obj = Const_Obj_t;
		e->level = LEVEL;
		e->posi = -1;
		switch (idp->type) {
		case Int_Const_Ident_t:
			e->type = Int_Type_t;
			break;
		case Char_Const_Ident_t:
			e->type = Char_Type_t;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG: 73\n");
		}
		e->stp = TOP;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, TOP);
	} else {
		fprintf(errlist, "\nduplicated const define: %s\n: %d",
				idp->name, idp->line);
	}
	return e;
}

SymTabESP sym_insert_var(IdentSP idp)
{
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	int h = hash(idp->name);
	if (TOP == NULL) 
		fprintf(errlist, "SYMTAB BUG:121\n");
	for (p = *(TOP->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = Nappend(idp->name);
		e->lines = l;
		e->level = LEVEL;
		e->posi = TOP->posi_var;
		switch (idp->type) {
		case Int_Var_Ident_t:
			e->type = Int_Type_t;
			e->obj = Var_Obj_t;
			e->val = -1;
			TOP->posi_var++;
			break;
		case Char_Var_Ident_t:
			e->type = Char_Type_t;
			e->obj = Var_Obj_t;
			e->val = -1;
			TOP->posi_var++;
			break;
		case IntArr_Var_Ident_t:
			e->type = Int_Type_t;
			e->obj = Array_Obj_t;
			e->val = idp->length;
			TOP->posi_var += e->val;
			break;
		case CharArr_Var_Ident_t:
			e->type = Char_Type_t;
			e->obj = Array_Obj_t;
			e->val = idp->length;
			TOP->posi_var += e->val;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG: 143\n");
		}
		e->stp = TOP;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, TOP);
	} else {
		fprintf(errlist, "\nduplicated var define: %s\n: %d",
				idp->name, idp->line);
	}
	return e;
}

SymTabESP sym_insert_proc(IdentSP idp, ParaListSP plp)
{
	char *proclabel;
	char *procsign;
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	int h = hash(idp->name);
	procsign = signature(idp, plp);
	proclabel = Nappend(procsign);
	if (TOP == NULL) 
		fprintf(errlist, "SYMTAB BUG:121\n");
	for (p = *(TOP->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) 
			&& (!strcmp(proclabel, p->ep->label)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = proclabel; 
		Npush(procsign);
		e->val = -1;
		e->lines = l;
		e->level = LEVEL;
		e->posi = -1;
		e->obj = Proc_Obj_t;
		e->type = Nop_Type_t;
		e->stp = TOP;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, TOP);
	} else {
		fprintf(errlist, "\nduplicated procedure define: %s\n: %d",
				idp->name, idp->line);
	}
	return e;
}

SymTabESP sym_insert_fun(IdentSP idp, ParaListSP plp)
{
	char *funlabel;
	char *funsign;
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	int h = hash(idp->name);
	funsign = signature(idp, plp);
	funlabel = Nappend(funsign);
	if (TOP == NULL) 
		fprintf(errlist, "SYMTAB BUG:121\n");
	for (p = *(TOP->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) 
			&& (!strcmp(funlabel, p->ep->label)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = funlabel; 
		Npush(funsign);
		e->val = -1;
		e->lines = l;
		e->level = LEVEL;
		e->posi = -1;
		e->obj = Fun_Obj_t;
		switch (idp->type) {
		case Int_Fun_Ident_t:
			e->type = Int_Type_t;
			break;
		case Char_Fun_Ident_t:
			e->type = Char_Type_t;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG: 201\n");
		}
		e->stp = TOP;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, TOP);
	} else {
		fprintf(errlist, "\nduplicated funtion define: %s\n: %d",
				idp->name, idp->line);
	}
	return e;
}

SymTabESP sym_insert_para(IdentSP idp)
{
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	int h = hash(idp->name);
	if (TOP == NULL) 
		fprintf(errlist, "SYMTAB BUG:263\n");
	for (p = *(TOP->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(idp->name, p->ep->name)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = idp->line;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(idp->name);
		e->label = Nappend(idp->name); 
		e->val = -1;
		e->lines = l;
		e->level = LEVEL;
		e->posi = TOP->posi_para++;
		switch (idp->type) {
		case Int_Para_Val_Ident_t:
			e->obj = Para_Val_Obj_t;
			e->type = Int_Type_t;
			break;
		case Int_Para_Ref_Ident_t:
			e->obj = Para_Ref_Obj_t;
			e->type = Int_Type_t;
			break;
		case Char_Para_Val_Ident_t:
			e->obj = Para_Val_Obj_t;
			e->type = Char_Type_t;
			break;
		case Char_Para_Ref_Ident_t:
			e->obj = Para_Ref_Obj_t;
			e->type = Char_Type_t;
			break;
		default:
			fprintf(errlist, "SYMTAB BUG: 291\n");
		}
		e->stp = TOP;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, TOP);
	} else {
		fprintf(errlist, "\nduplicated parameter define: %s\n: %d",
				idp->name, idp->line);
	}
	return e;
}

SymTabESP sym_insert_tmp(void)
{
	SymBucketSP p;
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	char *name = genTmp();
	int h = hash(name);
	if (TOP == NULL) 
		fprintf(errlist, "SYMTAB BUG:363\n");
	for (p = *(TOP->sbp + h); p != NULL; p = p->next) {
		if ((p->ep != NULL) && (!strcmp(name, p->ep->name)) ) 
				break;
	}
	if (p == NULL) {
		ENTRY(SymLineS, l);
		l->lineno = -1;
		l->next = NULL;
		ENTRY(SymTabES, e);
		e->name = copyString(name);
		e->label = Nappend(name); 
		e->val = -1;
		e->lines = l;
		e->level = LEVEL;
		e->posi = TOP->posi_tmp++;
		e->obj = Tmp_Obj_t;
		e->type = Int_Type_t;
		e->stp = TOP;
		ENTRY(SymBucketS, p);
		p->ep = e;
		p->next = NULL;
		sym_insert(p, TOP);
	} else {
		fprintf(errlist, "SYMTAB BUG:393");
	}
	return e;
}

SymTabESP sym_make_usi(int usi)
{
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	ENTRY(SymLineS, l);
	l->lineno = -1;
	l->next = NULL;
	ENTRY(SymTabES, e);
	e->name = NULL;
	e->label = mkUsi(usi); 
	e->val = usi;
	e->lines = l;
	e->level = LEVEL;
	e->posi = -1;
	e->obj = Num_Obj_t;
	e->type = Int_Type_t;
	e->stp = NULL;
	return e;
}

SymTabESP sym_make_label(void)
{
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	ENTRY(SymLineS, l);
	l->lineno = -1;
	l->next = NULL;
	ENTRY(SymTabES, e);
	e->name = NULL;
	e->label = genLabel(); 
	e->val = -1;
	e->lines = l;
	e->level = LEVEL;
	e->posi = -1;
	e->obj = Label_Obj_t;
	e->type = Nop_Type_t;
	e->stp = NULL;
	return e;
}

SymTabESP sym_make_main(void)
{
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	ENTRY(SymLineS, l);
	l->lineno = -1;
	l->next = NULL;
	ENTRY(SymTabES, e);
	e->name = "main";
	e->label = "main"; 
	e->val = -1;
	e->lines = l;
	e->level = LEVEL;
	e->posi = -1;
	e->obj = Fun_Obj_t;
	e->type = Int_Type_t;
	e->stp = TOP;
	return e;
}

SymTabESP sym_make_string(char *str)
{
	SymTabESP e;
	SymLineSP l;
	e = NULL;
	ENTRY(SymLineS, l);
	l->lineno = -1;
	l->next = NULL;
	ENTRY(SymTabES, e);
	e->name = NULL;
	e->label = str; 
	e->val = -1;
	e->lines = l;
	e->level = LEVEL;
	e->posi = -1;
	e->obj = String_Obj_t;
	e->type = Nop_Type_t;
	e->stp = NULL;
	return e;
}

SymTabESP sym_lookup(char *name)
{
	SymTabSP t;
	SymBucketSP p;
	int h = hash(name);
	if (TOP == NULL) {
		fprintf(errlist, "SYMTAB BUG:108\n");
		abort();
	}
	for (t = TOP; t != NULL; t = t->prev) {
		for (p = *(t->sbp + h); p != NULL; p = p->next) {
			if ((p->ep != NULL) 
				&& (!strcmp(name, p->ep->name)) ) 
				return p->ep;
		}
	}
	return NULL;
}

void printTab(SymTabSP t)
{
	SymBucketSP p;
	int i;
	if (t != NULL) {
		fprintf(tiplist, "\n***********************************************************\n");
		fprintf(tiplist, "    name\t  label  \t    line");
		fprintf(tiplist, "\t object \t  type       value ");
		fprintf(tiplist, "   level    posi\n");
		for (i = 0; i < HASHSIZE; i++) {
			for (p = *(t->sbp + i); p != NULL; p = p->next) {
				fprintf(tiplist, "%8s%24s%8d\t",
					p->ep->name, p->ep->label, 
					p->ep->lines->lineno);
				switch (p->ep->obj) {
				case Const_Obj_t:
					fprintf(tiplist, "Const_Obj_t");
					break;
				case Var_Obj_t:
					fprintf(tiplist, "Var_Obj_t");
					break;
				case Proc_Obj_t:
					fprintf(tiplist, "Proc_Obj_t");
					break;
				case Fun_Obj_t:
					fprintf(tiplist, "Fun_Obj_t");
					break;
				case Array_Obj_t:
					fprintf(tiplist, "Array_Obj_t");
					break;
				case Para_Val_Obj_t:
					fprintf(tiplist, "Para_Val_Obj_t");
					break;
				case Para_Ref_Obj_t:
					fprintf(tiplist, "Para_Ref_Obj_t");
					break;
				case Tmp_Obj_t:
					fprintf(tiplist, "Tmp_Obj_t");
					break;
				default:
					fprintf(errlist, "SYMTAB BUG:210\n");
				}
				fprintf(tiplist, "\t");
				switch (p->ep->type) {
				case Int_Type_t:
					fprintf(tiplist, "Int_Type_t");
					break;
				case Char_Type_t:
					fprintf(tiplist, "Char_Type_t");
					break;
				case Nop_Type_t:
					fprintf(tiplist, "Nop_Type_t");
					break;
				default:
					fprintf(errlist, "SYMTAB BUG:226\n");
				}
				fprintf(tiplist, "%8d%8d%8d\n",
					p->ep->val, p->ep->level, p->ep->posi);
			}
		}
		fprintf(tiplist, "-----------------------------------------------------------\n");
		fprintf(tiplist, 
			"var = %d; tmp = %d; para = %d; level = %d\n",
			t->posi_var, t->posi_tmp, t->posi_para, t->level);
		fprintf(tiplist, "***********************************************************\n");
	}
}
