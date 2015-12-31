/*
 * list.h
 *
 * Created: 22.12.2015 16:49:12
 *  Author: Raphael Lauber
 */ 


#ifndef LIST_H_
#define LIST_H_

#include "flinklib.h"
#include <stddef.h>

struct list_head {
	struct list_head *next, *prev;
};

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next, **pprev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
	list->prev = list;
}
   
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
(type *)( (char *)__mptr - offsetof(type,member) );})

#define list_entry(ptr, type, member) \
container_of(ptr, type, member)

#define list_first_entry(ptr, member) \
	list_entry((ptr)->next, member)

#define list_next_entry(pos, member) \
list_entry((pos)->member.next, member)
//list_entry((pos)->member.next, typeof(*(pos)), member)

#define list_for_each_entry(pos, head, member)				\
for (pos = list_first_entry(head, member);	\
&pos->member != (head);					\
pos = list_next_entry(pos, member))

#endif /* LIST_H_ */