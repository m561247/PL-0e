J_sa_pri_f$IV:
	LST	J_sa_pri_f$IV_n, 0x3, ..@l1
	SUB	J_sa_pri_f$IV_n, 0x1, J_sa_pri_f$IV_&2
	PUSH	-, -, J_sa_pri_f$IV_&2
	CALL	J_sa_pri_f$IV, -, J_sa_pri_f$IV_&3
	MUL	J_sa_pri_f$IV_n, J_sa_pri_f$IV_&3, J_sa_pri_f$IV_&1
	SRET	J_sa_pri_f$IV_&1, -, J_sa_pri_f$IV
	JMP	-, -, ..@l2
..@l1:
	SRET	J_sa_pri_f$IV_n, -, J_sa_pri_f$IV
..@l2:
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      &1        J_sa_pri_f$IV_&1      -1	Tmp_Obj_t	Int_Type_t      -1       4       0
      &2        J_sa_pri_f$IV_&2      -1	Tmp_Obj_t	Int_Type_t      -1       4       1
      &3        J_sa_pri_f$IV_&3      -1	Tmp_Obj_t	Int_Type_t      -1       4       2
       n         J_sa_pri_f$IV_n       7	Para_Val_Obj_t	Int_Type_t      -1       4       0
-----------------------------------------------------------
var = 0; tmp = 3; para = 1; level = 4
paralist = J_sa_pri_f$IV_n
***********************************************************
J_sa_pri_prr:
	AARR	0x2, 0x1, J_sa_pri_he
	LOAD	J_sa_pri_he, 0x1, J_sa_pri_prr_&4
	AARR	0x2, J_sa_pri_prr_&4, J_sa_pri_he
	LOAD	J_sa_pri_he, 0x1, J_sa_pri_prr_&6
	LOAD	J_sa_pri_he, J_sa_pri_prr_&6, J_sa_pri_prr_&5
	LOAD	J_sa_pri_he, 0x1, J_sa_pri_prr_&7
	AARR	J_sa_pri_prr_&5, J_sa_pri_prr_&7, J_sa_pri_pe
	LOAD	J_sa_pri_he, 0x1, J_sa_pri_prr_&9
	LOAD	J_sa_pri_pe, J_sa_pri_prr_&9, J_sa_pri_prr_&8
	WRI	-, -, J_sa_pri_prr_&8
	ADD	J_sa_pri_i, J_sa_pri_j, J_sa_pri_prr_&10
	ASS	J_sa_pri_prr_&10, -, J_sa_pri_i
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     &10        J_sa_pri_prr_&10      -1	Tmp_Obj_t	Int_Type_t      -1       4       6
      &4         J_sa_pri_prr_&4      -1	Tmp_Obj_t	Int_Type_t      -1       4       0
      &5         J_sa_pri_prr_&5      -1	Tmp_Obj_t	Int_Type_t      -1       4       1
      &6         J_sa_pri_prr_&6      -1	Tmp_Obj_t	Int_Type_t      -1       4       2
      &7         J_sa_pri_prr_&7      -1	Tmp_Obj_t	Int_Type_t      -1       4       3
      &8         J_sa_pri_prr_&8      -1	Tmp_Obj_t	Int_Type_t      -1       4       4
      &9         J_sa_pri_prr_&9      -1	Tmp_Obj_t	Int_Type_t      -1       4       5
-----------------------------------------------------------
var = 0; tmp = 7; para = 0; level = 4
***********************************************************
J_sa_pri:
	CALL	J_sa_pri_prr, -, -
	PUSH	-, -, 0x6
	CALL	J_sa_pri_f$IV, -, J_sa_pri_&11
	LOAD	J_sa_pri_he, 0x1, J_sa_pri_&14
	LOAD	J_sa_pri_pe, J_sa_pri_&14, J_sa_pri_&13
	DIV	J_sa_pri_&11, J_sa_pri_&13, J_sa_pri_&12
	WRI	-, -, J_sa_pri_&12
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     &11            J_sa_pri_&11      -1	Tmp_Obj_t	Int_Type_t      -1       3       0
     &12            J_sa_pri_&12      -1	Tmp_Obj_t	Int_Type_t      -1       3       1
     &13            J_sa_pri_&13      -1	Tmp_Obj_t	Int_Type_t      -1       3       2
     &14            J_sa_pri_&14      -1	Tmp_Obj_t	Int_Type_t      -1       3       3
     prr            J_sa_pri_prr      10	Proc_Obj_t	Nop_Type_t      -1       3      -1
      he             J_sa_pri_he       3	Array_Obj_t	Int_Type_t      10       3       0
       f           J_sa_pri_f$IV       7	Fun_Obj_t	Int_Type_t      -1       3      -1
       i              J_sa_pri_i       5	Var_Obj_t	Int_Type_t      -1       3      20
       j              J_sa_pri_j       5	Var_Obj_t	Int_Type_t      -1       3      21
      pe             J_sa_pri_pe       4	Array_Obj_t	Int_Type_t      10       3      10
-----------------------------------------------------------
var = 22; tmp = 4; para = 0; level = 3
***********************************************************
J_sa:
	CALL	J_sa_pri, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     pri                J_sa_pri       2	Proc_Obj_t	Nop_Type_t      -1       2      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 2
***********************************************************
J_prn_fe$IR:
	ASS	0x16, -, J_prn_fe$IR_i
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
       i           J_prn_fe$IR_i      18	Para_Ref_Obj_t	Int_Type_t      -1       3       0
-----------------------------------------------------------
var = 0; tmp = 0; para = 1; level = 3
paralist = J_prn_fe$IR_i
***********************************************************
J_prn:
	PUSHA	-, -, *J_prn_he
	CALL	J_prn_fe$IR, -, -
	WRI	-, -, J_prn_he
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      fe             J_prn_fe$IR      18	Proc_Obj_t	Nop_Type_t      -1       2      -1
      he                J_prn_he      17	Var_Obj_t	Int_Type_t      -1       2       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 0; level = 2
***********************************************************
main:
	CALL	J_sa, -, -
	CALL	J_prn, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
     prn                   J_prn      16	Proc_Obj_t	Nop_Type_t      -1       1      -1
      sa                    J_sa       1	Proc_Obj_t	Nop_Type_t      -1       1      -1
-----------------------------------------------------------
var = 0; tmp = 0; para = 0; level = 1
***********************************************************
