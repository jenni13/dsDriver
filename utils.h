#ifndef _UTILS_H

#define _UTILS_H

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/mutex.h>
#include <linux/uaccess.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/genhd.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/gpio.h>
#include <linux/delay.h>

static unsigned int gpio_num=17;
static int res = 0;
module_param(res,int,0);
MODULE_PARM_DESC(res,"resolution : 9,10,11 ou 12");

#define MINORS 16
#define NAME "ds18b20"



#define CMD_CONV_TEMP 0x44
#define CMD_RSCRATCHPAD 0xbe
#define CMD_WSCRATCHPAD 0x4e
#define CMD_CPYSCRATCHPAD 0x48
#define CMD_RECEEPROM 0xb8
#define CMD_READ_ROM 0x33
#define CMD_MATCH_ROM 0x55
#define CMD_SKIP_ROM 0xcc
#define CMD_ALARM_SEARCH 0xec
#define DECIMAL_STEPS_12BIT 625

static ssize_t ds_read(struct file *f,char *buf,size_t size,loff_t *offset);
static ssize_t ds_write(struct file *f,const char *buf,size_t size, loff_t *offset);
static int ds_open(struct inode *in, struct file *f);
static int ds_release(struct inode *in,struct file *f);

uint8_t read_bit(void);
uint8_t read_byte(void);

uint32_t reset(void);
uint32_t read_state(void);
uint32_t ds_get_temperature(void);

void write_byte(uint8_t b);
void write_bit(uint8_t bit);
void put_low(void);
void flush_line(void);
void make_delay(uint16_t us);

void set_resolution(void);
void write_scratchpad(uint8_t s1,uint8_t s2,uint8_t conf);
void copy_scratchpad(void);


#endif
