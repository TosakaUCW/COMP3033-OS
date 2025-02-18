/*
	File: hello.c
	Author: Bohan YANG
	Student ID: 2330016056
	Date: 2025/02/18
*/
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <linux/fs.h>
#include <linux/jiffies.h>

#define BUFFER_SIZE 128
#define PROC_NAME "hello"

//for kernel version (5.6.0) or above
//find your Linux system kernel version:  
//$ sudo uname -a   or  $ cat /proc/version
#define HAVE_PROC_OPS

ssize_t proc_read(struct file *file, char  *usr_buf, size_t count, loff_t *pos);

#ifdef HAVE_PROC_OPS
static struct proc_ops ops={
	.proc_read = proc_read,
};

#else
static struct file_operations ops = {
	.owner = THIS_MODULE,
	.read = proc_read,
};
#endif 

/* This function is called when the module is loaded. */
int proc_init(void)
{
	/* creates the /proc/hello entry */
	proc_create(PROC_NAME, 0666, NULL, &ops);
	return 0;
}
/* This function is called when the module is removed. */
void proc_exit(void)
{
	/* removes the /proc/hello entry */
	remove_proc_entry(PROC_NAME, NULL);
}


/* This function is called each time /proc/hello is read */
ssize_t proc_read(struct file *file, char *usr_buf, size_t count, loff_t *pos)
{
	int rv = 0;
	char buffer[BUFFER_SIZE];
	static int completed = 0;
	if (completed) {
		completed = 0;
		return 0;
	}
	completed = 1;
	
	/* print my student id */
	rv = sprintf(buffer, "2330016056∖n");
	
	/* copies kernel space buffer to user space usr buf */
	raw_copy_to_user(usr_buf, buffer, rv);
	return rv;
}

module_init(proc_init);
module_exit(proc_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hello Module");
MODULE_AUTHOR("Bohan YANG");
