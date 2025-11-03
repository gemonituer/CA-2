// SPDX-License-Identifier: GPL-2.0
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>

MODULE_AUTHOR("gemonituer");
MODULE_DESCRIPTION("Kernel module that prints a user-defined number of 'Hello, world!' messages");
MODULE_LICENSE("GPL");

static uint num_messages = 1;
module_param(num_messages, uint, 0444);
MODULE_PARM_DESC(num_messages, "Number of 'Hello, world!' messages to print at load time");

struct hello_data {
	struct list_head list;
	ktime_t timestamp;
};

static LIST_HEAD(hello_list);

static int __init hello_init(void)
{
	struct hello_data *entry;
	uint i;

	pr_info("loading module\n");

	if (num_messages == 0 || (num_messages >= 5 && num_messages <= 10)) {
		pr_warn("suspicious num_messages=%u (expected 1–4)\n",
			num_messages);
	} else if (num_messages > 10) {
		pr_err("invalid num_messages=%u (>10)\n", num_messages);
		return -EINVAL;
	}

	for (i = 1; i <= num_messages; i++) {
		entry = kmalloc(sizeof(*entry), GFP_KERNEL);
		if (!entry) {
			pr_err("failed to allocate memory for entry %u\n", i);
			return -ENOMEM;
		}

		entry->timestamp = ktime_get();
		list_add_tail(&entry->list, &hello_list);

		pr_info("[%u] Hello, world!\n", i);
	}

	pr_info("module loaded (num_messages=%u)\n", num_messages);
	return 0;
}

static void __exit hello_exit(void)
{
	struct hello_data *entry, *tmp;
	int i = 1;

	pr_info("unloading module\n");

	list_for_each_entry_safe(entry, tmp, &hello_list, list) {
		pr_info("[%d] timestamp (ns): %lld\n",
			i++, ktime_to_ns(entry->timestamp));
		list_del(&entry->list);
		kfree(entry);
	}

	pr_info("memory freed, module unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
