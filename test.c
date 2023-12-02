#include "tb_all.h"

typedef struct elm {
	int a;
	int b;
	char c;
	int d;
} elm;


static void elm_dtor(
	elm *e
) {}
static void elm_log(
	elm *e
)
{
	printf("Element %p :\n", e);
	printf("  a : %d.\n", e->a);
	printf("  b : %d.\n", e->b);
	printf("  c : %d.\n", e->c);
	printf("  d : %d.\n", e->d);
}

TB_FIFO_API(elm, &elm_dtor, &elm_log);

int main() {
	
	elm e0 = {0, 1, 2, 3};
	elm e1 = {1, 2, 3, 4};
	elm e2 = {2, 3, 4, 5};
	elm e3 = {3, 4, 5, 6};
	elm e4 = {4, 5, 6, 7};

	elm_fifo *fifo = elm_fifo_ctor();

	elm_fifo_push(fifo, &e0);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e1);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e2);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e3);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e4);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e0);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e0);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e1);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e1);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e2);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e2);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e3);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e3);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e4);
	printf("FIFO :\n");
	elm_fifo_log(fifo);
	elm_fifo_push(fifo, &e4);
	printf("FIFO :\n");
	elm_fifo_log(fifo);

	uaddr nb = tb_fifo_nb(fifo);
	while (nb--) {
		printf("READ : .\n");
		elm_log(elm_fifo_read(fifo));
		printf("DEL : .\n");
		elm_fifo_del(fifo);
		printf("FIFO :\n");
		elm_fifo_log(fifo);
	}
	assert(fifo->nb == 0);

	tb_fifo_dtor(fifo);

}
