#ifndef _OPTIM_H_
#define _OPTIM_H_
#include "limits.h"
#include "ir.h"
#include "symtab.h"

// CFG: flow graph objects: Module, Function, BasicBlock
typedef struct _module_struct mod_t;
typedef struct _function_struct fun_t;
typedef struct _basic_block_struct bb_t;

// DAG: graph, nodes
typedef struct _dag_struct dag_t;
typedef struct _dag_node_struct dnode_t;

struct _module_struct {
	fun_t *fhead;
	fun_t *ftail;
};

struct _function_struct {
	symtab_t *scope;
	bb_t *bhead;
	bb_t *btail;
	fun_t *next;
};

struct _basic_block_struct {
	// basic information
	int bid; // block ID
	int total; // total number of instructions
	inst_t *insts[MAXBBINST]; // instructions
	bb_t *next;

	// next-use information
	bool liveness[MAXSYMENT];
	inst_t *nextuse[MAXSYMENT];

	// predecessors and successors
	bb_t *pred[MAXBBLINK];
	bb_t *succ[MAXBBLINK];
};

typedef enum dnode_cate_enum {
	OPERNODE = 0,
	SYMBOLNODE = 1,
} dnode_cate_t;

struct _dag_node_struct {
	// common
	int nid; // node ID
	dnode_cate_t cate;

	// attributes for operation node
	op_t op;
	dnode_t *left;
	dnode_t *right;

	// attributes for symbol node
	syment_t *syment;
};

struct _dag_struct {
	int gid; // graph ID
	int opcnt; // operation nodes counter
	dnode_t *opnodes[MAXDAGNODES]; // operation nodes
	dnode_t *sbnodes[MAXDAGNODES]; // symbol nodes
};

// global module handler
extern mod_t mod;

// optimize function
void partition_basic_blocks(void);
void construct_flow_graph(void);

// optimize entry
void optim(void);
#endif /* End of _OPTIM_H_ */
