// SPDX-License-Identifier: GPL-2.0
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

#include "hello1.h"

MODULE_AUTHOR("gemonituer");
MODULE_DESCRIPTION("Kernel module that provides print_hello() and manages the list of messages");
MODULE_LICENSE("GPL");

static LIST_HEAD(hello_list);

void print_hello(unsigned int entry_num)
{
	struct hello_data *entry;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		pr_err("failed to allocate memory for new hello_data entry %u\n",
		       entry_num);
		return;
	}

	entry->timestamp = ktime_get();

	entry->t_start = ktime_get();
	pr_info("[%u] Hello, world!\n", entry_num);
	entry->t_end = ktime_get();

	list_add_tail(&entry->list, &hello_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello_init(void)
{
	pr_info("module loaded\n");
	return 0;
}

static void __exit hello_exit(void)
{
	struct hello_data *entry, *tmp;
	int i = 1;

	pr_info("unloading module\n");

	list_for_each_entry_safe(entry, tmp, &hello_list, list) {
		s64 print_time_ns = ktime_to_ns(ktime_sub(entry->t_end, entry->t_start));

		pr_info("[%d] timestamp (ns): %lld, time spent (ns): %lld\n",
			i++, ktime_to_ns(entry->timestamp), print_time_ns);

		list_del(&entry->list);
		kfree(entry);
	}

	pr_info("memory freed, module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
