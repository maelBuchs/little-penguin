// SPDX-License-Identifier: GPL-2.0-only

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>

static int do_work(int loop_len)
{
	int x;

	for (x = 0; x < loop_len; ++x)
		usleep_range(10, 20);

	/* That was a long sleep, tell userspace about it */
	if (loop_len >= 10)
		pr_info(pr_fmt("We slept a long time!\n"));
	return x * loop_len;
}

static int __init my_init(void)
{
	int x = 10;

	x = do_work(x);
	return 0;
}

static void __exit my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("mbuchs");
MODULE_DESCRIPTION("Awfull shit");
