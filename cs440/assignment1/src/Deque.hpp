/* Copyright 2018 Austin Ward */
#ifndef Austin_Ward_DEQUE_HPP
#define Austin_Ward_DEQUE_HPP

#include <dlfcn.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <random>
#include <unistd.h>

#define Deque_DEFINE(t)                                                        \
struct DEQUE_##t##_IT;                                                         \
typedef struct DEQUE_##t##_IT Deque_##t##_Iterator;                            \
                                                                               \
typedef struct DEQUE_##t {                                                     \
  t *buf;                                                                      \
  int _front;                                                                  \
  int _back;                                                                   \
  size_t _size;                                                                \
  size_t _total;                                                               \
  bool (*cmp_func) (const t &, const t &);                                     \
  size_t (*size) (struct DEQUE_##t *);                                         \
  bool (*empty) (struct DEQUE_##t *);                                          \
  char type_name[6 + sizeof(#t)] = "Deque_" #t;                                \
  void (*clear) (struct DEQUE_##t *);                                          \
  void (*dtor) (struct DEQUE_##t *);                                           \
  void (*push_back) (struct DEQUE_##t *, t);                                   \
  void (*push_front) (struct DEQUE_##t *, t);                                  \
  t& (*pop_front) (struct DEQUE_##t *);                                        \
  t& (*pop_back) (struct DEQUE_##t *);                                         \
  t& (*front) (struct DEQUE_##t *);                                            \
  t& (*back) (struct DEQUE_##t *);                                             \
  Deque_##t##_Iterator (*begin) (struct DEQUE_##t *);                          \
  Deque_##t##_Iterator (*end) (struct DEQUE_##t *);                            \
  t& (*at) (struct DEQUE_##t *, int);                                          \
  void (*sort) (struct DEQUE_##t *,                                            \
		  Deque_##t##_Iterator, Deque_##t##_Iterator);                 \
} Deque_##t;                                                                   \
typedef struct DEQUE_##t##_IT {                                                \
  Deque_##t *deq;                                                              \
  int base;                                                                    \
  int offset;                                                                  \
  void (*inc) (Deque_##t##_Iterator *);                                        \
  void (*dec) (Deque_##t##_Iterator *);                                        \
  t& (*deref) (Deque_##t##_Iterator *);                                        \
} Deque_##t##_Iterator;                                                        \
                                                                               \
void Deque_##t##_ctor(Deque_##t *deq,                                          \
		bool (*cmp_func) (const t &, const t &));                      \
void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator *it,                       \
		Deque_##t *(&deq));                                            \
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it,                       \
		Deque_##t##_Iterator e);                                       \
bool Deque_##t##_equal(Deque_##t, Deque_##t);                                  \
int t##_mod(int, int);                                                         \
int t##_compare(const void *, const void *, void* deq);                        \
void t##_clear(Deque_##t *deq);                                                \
void t##_dtor(Deque_##t *deq);                                                 \
size_t t##_size(Deque_##t *deq);                                               \
bool t##_empty(Deque_##t *deq);                                                \
void t##_push_back(Deque_##t *deq, t);                                         \
void t##_push_front(Deque_##t *deq, t);                                        \
t& t##_pop_back(Deque_##t *deq);                                               \
t& t##_pop_front(Deque_##t *deq);                                              \
t& t##_back(Deque_##t *deq);                                                   \
t& t##_front(Deque_##t *deq);                                                  \
void t##_grow(Deque_##t *(&deq));                                              \
bool t##_full(Deque_##t *(&deq));                                              \
t& t##_at(Deque_##t *deq, int);                                                \
Deque_##t##_Iterator t##_begin(Deque_##t *deq);                                \
Deque_##t##_Iterator t##_end(Deque_##t *deq);                                  \
void t##_sort(struct DEQUE_##t *, Deque_##t##_Iterator,                        \
		Deque_##t##_Iterator);                                         \
void t##_inc(Deque_##t##_Iterator *it);                                        \
void t##_dec(Deque_##t##_Iterator *it);                                        \
t& t##_deref(Deque_##t##_Iterator *it);                                        \
                                                                               \
void Deque_##t##_ctor(Deque_##t *deq,                                          \
		bool (*cmp_func)(const t&, const t&)) {                        \
  deq->buf = (t *) malloc(4 * sizeof(t));                                      \
  deq->_front = 0;                                                             \
  deq->_back = -1;                                                             \
  deq->_total = 0;                                                             \
  deq->_size = 4;                                                              \
  deq->cmp_func = cmp_func;                                                    \
  deq->clear = t##_clear;                                                      \
  deq->dtor = t##_dtor;                                                        \
  deq->size = t##_size;                                                        \
  deq->empty = t##_empty;                                                      \
  deq->push_front = t##_push_front;                                            \
  deq->push_back = t##_push_back;                                              \
  deq->pop_front = t##_pop_front;                                              \
  deq->pop_back = t##_pop_back;                                                \
  deq->front = t##_front;                                                      \
  deq->back = t##_back;                                                        \
  deq->begin = t##_begin;                                                      \
  deq->end = t##_end;                                                          \
  deq->at = t##_at;                                                            \
  deq->sort = t##_sort;                                                        \
}                                                                              \
                                                                               \
void t##_dtor(Deque_##t *deq) {                                                \
  free(deq->buf);                                                              \
}                                                                              \
                                                                               \
void t##_clear(Deque_##t *deq) {                                               \
  deq->_front = deq->_total = 0;                                               \
  deq->_back = -1;                                                             \
  deq->_total = 0;                                                             \
}                                                                              \
                                                                               \
size_t t##_size(Deque_##t *deq) {                                              \
  return deq->_total;                                                          \
}                                                                              \
                                                                               \
bool t##_empty(Deque_##t *deq) {                                               \
  return !deq->_total;                                                         \
}                                                                              \
                                                                               \
void t##_push_front(Deque_##t *deq, t val) {                                   \
  if (t##_full(deq)) t##_grow(deq);                                            \
  deq->buf[t##_mod(deq->_front++, deq->_size)] = val;                          \
  deq->_total++;                                                               \
}                                                                              \
                                                                               \
void t##_push_back(Deque_##t *deq, t val) {                                    \
  if (t##_full(deq)) t##_grow(deq);                                            \
  deq->buf[t##_mod(deq->_back--, deq->_size)] = val;                           \
  deq->_total++;                                                               \
}                                                                              \
                                                                               \
t& t##_pop_front(Deque_##t *deq) {                                             \
  deq->_total--;                                                               \
  return deq->buf[t##_mod(deq->_front-- - 1, deq->_size)];                     \
}                                                                              \
                                                                               \
t& t##_pop_back(Deque_##t *deq) {                                              \
  deq->_total--;                                                               \
  return deq->buf[t##_mod(deq->_back++ + 1, deq->_size)];                      \
}                                                                              \
                                                                               \
t& t##_front(Deque_##t *deq) {                                                 \
  return deq->buf[t##_mod(deq->_front - 1, deq->_size)];                       \
}                                                                              \
                                                                               \
t& t##_back(Deque_##t *deq) {                                                  \
  return deq->buf[t##_mod(deq->_back + 1, deq->_size)];                        \
}                                                                              \
                                                                               \
void t##_grow(Deque_##t *(&deq)) {                                             \
  t *temp_buf = deq->buf;                                                      \
  deq->buf = (t *) malloc(2 * deq->_size * sizeof(t));                         \
  for (size_t i = 0; i < deq->_size * 2; ++i)                                  \
    deq->buf[i] = t();                                                         \
  for(int i = 0; deq->_total--; i++)                                           \
    deq->buf[i] = temp_buf[t##_mod(deq->_back++ + 1, deq->_size)];             \
  deq->_back = -1;                                                             \
  deq->_total = deq->_front = deq->_size - 1;                                  \
  free(temp_buf);                                                              \
  deq->_size *= 2;                                                             \
}                                                                              \
                                                                               \
bool t##_full(Deque_##t *(&deq)) {                                             \
  return deq->_total == deq->_size - 1;                                        \
}                                                                              \
                                                                               \
/* Adapted from https://stackoverflow.com/a/2074403/6119317 */                 \
int t##_mod(int i, int j) {                                                    \
  int val = i;                                                                 \
  uint32_t temp = val >> 31;                                                   \
  val ^= temp;                                                                 \
  val += temp & 1;                                                             \
  if (i + val != 0) return val % j;                                            \
  if (val % j) return j - (val % j);                                           \
  if (val) return j - 1;                                                       \
  return 0;                                                                    \
}                                                                              \
                                                                               \
Deque_##t##_Iterator t##_begin(Deque_##t *deq) {                               \
  Deque_##t##_Iterator it;                                                     \
  Deque_##t##_Iterator_ctor(&it, deq);                                         \
  it.base = deq->_front - 1;                                                   \
  return it;                                                                   \
}                                                                              \
                                                                               \
Deque_##t##_Iterator t##_end(Deque_##t *deq) {                                 \
  Deque_##t##_Iterator it;                                                     \
  Deque_##t##_Iterator_ctor(&it, deq);                                         \
  it.base = deq->_back;                                                        \
  return it;                                                                   \
}                                                                              \
                                                                               \
t& t##_at(Deque_##t *deq, int idx) {                                           \
  int i = deq->_front - (idx + 1);                                             \
  int j = deq->_size;                                                          \
  int m = t##_mod(i, j);                                                       \
  return deq->buf[m];                                                          \
}                                                                              \
                                                                               \
bool Deque_##t##_equal(Deque_##t d1, Deque_##t d2) {                           \
  if (d1._total != d2._total) return false;                                    \
  bool cmp1, cmp2;                                                             \
  for(size_t i = 0; i < d1._total; i++) {                                      \
    cmp1 = (*d1.cmp_func)(d1.at(&d1, i), d2.at(&d2, i));                       \
    cmp2 = (*d1.cmp_func)(d2.at(&d2, i), d1.at(&d1, i));                       \
    if (cmp1 != cmp2) return false;                                            \
  }                                                                            \
  return true;                                                                 \
}                                                                              \
                                                                               \
void t##_sort(Deque_##t *deq, Deque_##t##_Iterator start,                      \
		Deque_##t##_Iterator end) {                                    \
	int sort_size = 0;                                                     \
        t *temp_buf;                                                           \
	if(Deque_##t##_Iterator_equal(start, end)) {                           \
	sort_size = deq->_total;                                               \
                                                                               \
	temp_buf = (t *) malloc(sort_size * sizeof(t));                        \
	int i = 0;                                                             \
        for (; i < sort_size; i++) temp_buf[i] = t();                          \
	i = 0;                                                                 \
	for(Deque_##t##_Iterator it = start; i < sort_size; it.inc(&it))       \
		temp_buf[i++] = it.deref(&it);                                 \
                                                                               \
         qsort_r(temp_buf, sort_size, sizeof(t), t##_compare, deq);            \
	  i = sort_size - 1;                                                   \
	for(Deque_##t##_Iterator it = start; i >= 0; it.inc(&it))              \
		it.deref(&it) = temp_buf[i--];                                 \
	} else {                                                               \
	for(Deque_##t##_Iterator it = start;                                   \
			!Deque_##t##_Iterator_equal(it, end); it.inc(&it))     \
          sort_size++;                                                         \
                                                                               \
	temp_buf = (t *) malloc(sort_size * sizeof(t));                        \
	int i = 0;                                                             \
        for (; i < sort_size; i++) temp_buf[i] = t();                          \
	i = 0;                                                                 \
	for(Deque_##t##_Iterator it = start;                                   \
			!Deque_##t##_Iterator_equal(it, end); it.inc(&it))     \
		temp_buf[i++] = it.deref(&it);                                 \
                                                                               \
  qsort_r(temp_buf, sort_size, sizeof(t), t##_compare, deq);                   \
	  i = sort_size - 1;                                                   \
	for(Deque_##t##_Iterator it = start;                                   \
			!Deque_##t##_Iterator_equal(it, end); it.inc(&it))     \
		it.deref(&it) = temp_buf[i--];                                 \
	}                                                                      \
  free(temp_buf);                                                              \
}                                                                              \
                                                                               \
int t##_compare(const void *arg1, const void *arg2, void* deq) {               \
  Deque_##t *d = (Deque_##t*) deq;                                             \
  bool cmp1 = (*d->cmp_func)(*((t*)(arg1)), *((t*)(arg2)));                    \
  bool cmp2 = (*d->cmp_func)(*((t*)(arg2)), *((t*)(arg1)));                    \
  if (cmp1) return 1;                                                          \
  if (cmp2) return -1;                                                         \
  else return 0;                                                               \
}                                                                              \
                                                                               \
void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator *it,                       \
		Deque_##t *(&deq)) {                                           \
  it->offset = 0;                                                              \
  it->deq = deq;                                                               \
  it->inc = t##_inc;                                                           \
  it->dec = t##_dec;                                                           \
  it->deref = t##_deref;                                                       \
}                                                                              \
                                                                               \
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator it,                       \
		Deque_##t##_Iterator e) {                                      \
  return &(it.deq->buf[t##_mod(it.base + it.offset, it.deq->_total)]) ==       \
	 &(e.deq->buf[t##_mod(e.base + e.offset, e.deq->_total)]);             \
}                                                                              \
                                                                               \
void t##_inc(Deque_##t##_Iterator *it) {                                       \
  it->offset++;                                                                \
}                                                                              \
                                                                               \
void t##_dec(Deque_##t##_Iterator *it) {                                       \
  it->offset--;                                                                \
}                                                                              \
                                                                               \
t& t##_deref(Deque_##t##_Iterator *it) {                                       \
  return it->deq->buf[t##_mod(it->base - it->offset, it->deq->_size)];         \
}

#endif
