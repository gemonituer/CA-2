/* SPDX-License-Identifier: GPL-2.0 */
#pragma once

#include <linux/list.h>
#include <linux/ktime.h>

struct hello_data {
	struct list_head list;
	ktime_t timestamp;
	ktime_t t_start;
	ktime_t t_end;
};

void print_hello(unsigned int entry_num);
