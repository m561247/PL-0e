J_h1$IR_h2$IR_h3$IR:
	ASS	0x9, -, J_h1$IR_h2$IR_h3$IR_i
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
       i   J_h1$IR_h2$IR_h3$IR_i       4	Para_Ref_Obj_t	Int_Type_t      -1       4       0
-----------------------------------------------------------
var = 0; tmp = 0; para = 1; level = 4
paralist = J_h1$IR_h2$IR_h3$IR_i
***********************************************************
J_h1$IR_h2$IR:
	PUSHA	-, -, *J_h1$IR_h2$IR_i
	CALL	J_h1$IR_h2$IR_h3$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h3     J_h1$IR_h2$IR_h3$IR       4	Proc_Obj_t	Nop_Type_t      -1       3      -1
       i         J_h1$IR_h2$IR_i       3	Para_Ref_Obj_t	Int_Type_t      -1       3       0
-----------------------------------------------------------
var = 0; tmp = 0; para = 1; level = 3
paralist = J_h1$IR_h2$IR_i
***********************************************************
J_h1$IR:
	PUSHA	-, -, *J_h1$IR_i
	CALL	J_h1$IR_h2$IR, -, -
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h2           J_h1$IR_h2$IR       3	Proc_Obj_t	Nop_Type_t      -1       2      -1
       i               J_h1$IR_i       2	Para_Ref_Obj_t	Int_Type_t      -1       2       0
-----------------------------------------------------------
var = 0; tmp = 0; para = 1; level = 2
paralist = J_h1$IR_i
***********************************************************
main:
	PUSHA	-, -, *J_i
	CALL	J_h1$IR, -, -
	WRI	-, -, J_i
	FIN	-, -, -

***********************************************************
    name	  label  	    line	 object 	  type       value    level    posi
      h1                 J_h1$IR       2	Proc_Obj_t	Nop_Type_t      -1       1      -1
       i                     J_i       1	Var_Obj_t	Int_Type_t      -1       1       0
-----------------------------------------------------------
var = 1; tmp = 0; para = 0; level = 1
***********************************************************
ASM BUG:88
ASM BUG:88
