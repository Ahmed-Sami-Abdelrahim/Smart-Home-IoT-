#ifndef FILE_OPERATION
#define FILE_OPERATION


#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/gpio.h>
#include <sys/types.h>


int driver_close(struct inode *device_file, struct file *instance);
int driver_open(struct inode *device_file, struct file *instance);


ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs);
ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs);


#endif // FILE_OPERATION