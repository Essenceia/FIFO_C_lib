#include "tb_all.h"

static inline void _elm_dtor(
	tb_fifo *fifo,
	tb_fifo_elm *elm
)
{
	tb_list_rmu(&elm->elms);
	(*(fifo->elm_dtor))(elm->impl);
	free(elm->impl);
	free(elm);
}

/*
 * Construct a fifo.
 */
tb_fifo *tb_fifo_ctor(
	size_t size,
	void (*elm_dtor)(void *),
	void (*elm_log)(void *)
)
{
	assert(size);
	assert(elm_dtor);
	assert(elm_log);
	malloc__(tb_fifo, fifo);
	tb_list_init(&fifo->elms);
	fifo->size = size;
	fifo->elm_dtor = elm_dtor;
	fifo->elm_log = elm_log;
	fifo->nb = 0;
	return fifo;
}

/*
 * Destruct a fifo, delete all its elements.
 */
void tb_fifo_dtor(
	tb_fifo *fifo
)
{
	tb_fifo_elm *elm;
	tb_list_fes(elm, &fifo->elms, elms) {
		_elm_dtor(fifo, elm);
	}
	free(fifo);
}

/*
 * Print the content of @fifo.
 */
void tb_fifo_log(
	tb_fifo *fifo
)
{
	tb_fifo_elm *elm;
	tb_list_fes(elm, &fifo->elms, elms) {
		(*(fifo->elm_log))(elm->impl);
	}
}

/*
 * Allocate a new element, initialize it with @init, and push it
 * at the end of the fifo.
 * @size must be @fifo->size.
 */
void tb_fifo_push(
	tb_fifo *fifo,
	void *init,
	size_t size
)
{
	malloc__(tb_fifo_elm, elm);
	void *dst = malloc(fifo->size);
	memcpy(dst, init, fifo->size);
	tb_list_ib(&fifo->elms, &elm->elms);
	elm->impl = dst;
	SAFE_INCR(fifo->nb);
}

/*
 * Read the first element of the fifo, return its pointer.
 * @size must be @fifo->size.
 * If @fifo is empty, return 0.
 */
void *tb_fifo_read(
	tb_fifo *fifo,
	uaddr size 
)
{
	tb_fifo_elm *elm = 0;
	if (tb_list_emptyne(&fifo->elms, elm, tb_fifo_elm, elms)) return 0;
	assert(elm);
	assert(elm->impl);
	return elm->impl;
}

/*
 * Delete the first element of the fifo.
 * It must exist.
 */
void tb_fifo_del(
	tb_fifo *fifo
)
{
	tb_fifo_elm *elm = 0;
	u8 empty = tb_list_emptyne(&fifo->elms, elm, tb_fifo_elm, elms);
	assert(!empty);
	assert(elm);
	_elm_dtor(fifo, elm);
	SAFE_DECR(fifo->nb);
}

/*
 * Return the number of elements in @fifo.
 */
uaddr tb_fifo_nb(
	tb_fifo *fifo
)
{
	return fifo->nb;
}

