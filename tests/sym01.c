#include <assert.h>
#include "symtab.h"

#define symdump()                                                              \
	do {                                                                   \
		msg("%s:%d in %s() ", __FILE__, __LINE__, __func__);           \
		symdump();                                                     \
	} while (0)

void func01();
void func02();

void add_test_symbol(char *name)
{
	syment_t *e;
	NEWENTRY(e);
	e->name = name;
	symadd(e);
}

void func01()
{
	syment_t *e;
	scope_entry("func01");
	symdump();

	e = symfind("aaa");
	assert(e && !strcmp(e->stab->nspace, "root"));

	e = symget("aaa");
	assert(!e);

	add_test_symbol("aaa");

	e = symget("aaa");
	assert(e);

	func02();

	add_test_symbol("ccc");
	symdump();

	e = symfind("aaa");
	assert(e && !strcmp(e->stab->nspace, "func01"));
	e = symfind("bbb");
	assert(e && !strcmp(e->stab->nspace, "root"));
	e = symfind("ccc");
	assert(e && !strcmp(e->stab->nspace, "func01"));
	e = symfind("ddd");
	assert(!e);

	scope_exit();
}

void func02()
{
	syment_t *e;
	scope_entry("func02");
	symdump();

	add_test_symbol("aaa");
	add_test_symbol("ddd");
	symdump();

	e = symfind("ccc");
	assert(!e);

	scope_exit();
}

int main(int argc, char *argv[])
{
	syment_t *e;
	scope_entry("root");

	add_test_symbol("aaa");
	symdump();

	add_test_symbol("bbb");
	symdump();

	e = symfind("aaa");
	assert(!strcmp(e->name, "aaa"));
	assert(!strcmp(e->stab->nspace, "root"));

	e = symfind("ccc");
	assert(e == NULL);

	func01();

	e = symfind("ccc");
	assert(e == NULL);

	scope_exit();
	return 0;
}
