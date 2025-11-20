// SPDX-License-Identifier: GPL-2.0
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("gemonituer");
MODULE_DESCRIPTION("Kernel module that calls print_hello() from hello1 module");
MODULE_LICENSE("GPL");

static uint num_messages = 1;
module_param(num_messages, uint, 0444);
MODULE_PARM_DESC(num_messages, "Number of 'Hello, world!' messages to print at load time");

static int __init hello2_init(void)
{
	uint i;

	pr_info("loading module\n");

	if (num_messages == 0 || (num_messages >= 5 && num_messages <= 10)) {
		pr_warn("suspicious num_messages=%u (expected 1–4)\n",
			num_messages);
	} else if (num_messages > 10) {
		pr_err("invalid num_messages=%u (>10)\n", num_messages);
		return -EINVAL;
	}

	for (i = 1; i <= num_messages; i++)
		print_hello(i);

	pr_info("module loaded (num_messages=%u)\n", num_messages);
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("module unloaded\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
