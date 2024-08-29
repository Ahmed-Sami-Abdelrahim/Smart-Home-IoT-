#include "gpio-file-operation"

char buffer [255];
size_t buffer_pointer =0;


ssize_t driver_read(struct file *File, char *user_buffer, size_t count, loff_t *offs){
    printk("driver read is called but pin is just output\n");
    return -ENOSYS;
}


ssize_t driver_write(struct file *File, const char *user_buffer, size_t count, loff_t *offs){
    int not_copied;
    char value;
    printk("driver_write!, count is %ld\n, count");

    /* Copy data to user */
    not_copied = copy_from_user(&value, user_buffer, sizeof(value));
    /* Setting LED */
    switch(value){
        case '0': 
            gpio_set_value(21, 0);
            break;
        case '1':
            gpio_set_value(21, 1);
        default:
            printk("Invalid Input!\n");
            break;
    }

count=count-not_copied;
return count;

}


/** 
* @brief This function is called when the device file is opened
*/


int driver_open(struct inode *device_file, struct file *instance){
    printk("dev_nr - open was called\n");
    return 0;
}

int driver_close(struct inode *device_file, struct file *instance){
    printk("dev_nr - close was called\n");
    return 0;
}