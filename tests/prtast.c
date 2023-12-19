#include "anlys.h"
#include "global.h"
#include "tree.h"
#include "parse.h"
#include "util.h"
#include "syntax.h"
#include <stdio.h>
#include <string.h>

int indent = 0;

void prtnode(node_t *node)
{
	indent++;
	for (int i = 1; i < indent; ++i) {
		msg(" ");
	}

	if (!node) {
		msg("(nil)");
		goto postwork;
	}

	char buf[1024];
	sprintf(buf, "#%03d %s", node->id, node->name);

	if (node->extra) {
		appendf(buf, " [%s]", node->extra);
	}

	if (node->idp) {
		ident_node_t *idp = node->idp;
		appendf(buf, " name=%s kind=%d", idp->name, idp->kind);
		syment_t *sym = idp->symbol;
		if (sym) {
			appendf(buf, " type=%d cate=%d label=%s", sym->type,
				sym->cate, sym->label);
		}
	}
	msg("%s\n", buf);

	for (int i = 0; i < node->total; ++i) {
		prtnode(node->childs[i]);
	}

postwork:
	indent--;
}

int main(int argc, char *argv[])
{
	init(argc, argv);
	parse();
	analysis();
	node_t *tree = conv_pgm_node(ast);
	prtnode(tree);
	return 0;
}
