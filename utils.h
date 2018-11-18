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

#define FALSE 0
#define TRUE  1

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


static unsigned char dscrc_table[] = {
        0, 94,188,226, 97, 63,221,131,194,156,126, 32,163,253, 31, 65,
      157,195, 33,127,252,162, 64, 30, 95,  1,227,189, 62, 96,130,220,
       35,125,159,193, 66, 28,254,160,225,191, 93,  3,128,222, 60, 98,
      190,224,  2, 92,223,129, 99, 61,124, 34,192,158, 29, 67,161,255,
       70, 24,250,164, 39,121,155,197,132,218, 56,102,229,187, 89,  7,
      219,133,103, 57,186,228,  6, 88, 25, 71,165,251,120, 38,196,154,
      101, 59,217,135,  4, 90,184,230,167,249, 27, 69,198,152,122, 36,
      248,166, 68, 26,153,199, 37,123, 58,100,134,216, 91,  5,231,185,
      140,210, 48,110,237,179, 81, 15, 78, 16,242,172, 47,113,147,205,
       17, 79,173,243,112, 46,204,146,211,141,111, 49,178,236, 14, 80,
      175,241, 19, 77,206,144,114, 44,109, 51,209,143, 12, 82,176,238,
       50,108,142,208, 83, 13,239,177,240,174, 76, 18,145,207, 45,115,
      202,148,118, 40,171,245, 23, 73,  8, 86,180,234,105, 55,213,139,
       87,  9,235,181, 54,104,138,212,149,203, 41,119,244,170, 72, 22,
      233,183, 85, 11,136,214, 52,106, 43,117,151,201, 74, 20,246,168,
      116, 42,200,150, 21, 75,169,247,182,232, 10, 84,215,137,107, 53};

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

int OWSearch(void);
unsigned char docrc8(unsigned char value);
void OWTargetSetup(unsigned char family_code);
int OWNext(void);
#endif
