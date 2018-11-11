#include "utils.h"

#define LICENSE "GPL"
#define AUTHOR "MANFREDO Jennifer"
#define DESCRIPTION "capteur temp"


static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = ds_open,
	.read = ds_read,
	.write = ds_write,
	.release = ds_release,
};

dev_t dev;
struct cdev *my_cdev;
static struct class* ds18b20_class;
uint8_t scratchpad[9] = {0,0,0,0,0,0,0,0,0};
uint32_t val;
uint8_t config;
int resolution;

static int ds18b20_init(void)
{
	printk(KERN_INFO "ds18b20 init\n");

	if(alloc_chrdev_region(&dev,0,1,NAME) < 0) //0 ->starting minor,nb device you need
	{
		printk(KERN_ALERT "ERROR alloc_chrdev_region\n");
		return -EINVAL;
	}
	printk(KERN_INFO "Init allocated major=%d minor=%d\n",MAJOR(dev),MINOR(dev));
	my_cdev = cdev_alloc();
	cdev_init(my_cdev,&fops);
	cdev_add(my_cdev,dev,1);

	if(!gpio_is_valid(gpio_num))
	{
		printk(KERN_ALERT "ERROR pin gpio invalid\n");
		return -ENODEV;
	}
	ds18b20_class = class_create(THIS_MODULE,NAME); //create device node in /dev
	device_create(ds18b20_class,NULL,dev,NULL,"%s%d",NAME,MINOR(dev)); /*	registering dev
										dev_create(struct class,struct device,dev_t,
												const char,other arg)*/
	if(gpio_request(gpio_num,NAME) < 0)
	{
		printk(KERN_ALERT "ERROR gpio_request\n");
		return -ENODEV;
	}

	return 0;
}

uint32_t ds_get_temperature(void)
{
	uint16_t timeout = 0xFFFF;
	//uint8_t scratchpad[2] = {0,0};
	int8_t digit = 0;
	uint16_t decimal = 0;

	if(reset())
	{
		printk(KERN_INFO " 1er ds18b20 is not responding\n");
		return -ENODEV;
	}
	write_byte(CMD_SKIP_ROM);
	write_byte(CMD_CONV_TEMP);

	while(!read_bit() && timeout > 0)
		timeout --;

	if(timeout == 0)
	{
		printk(KERN_INFO "ds18b20 conversion has timeout\n");
		return -ENODEV;
	}

	if(reset())
	{
		printk(KERN_INFO " 2eme ds18b20 is not responding\n");
		return -ENODEV;
	}
        write_byte(CMD_SKIP_ROM);
        write_byte(CMD_RSCRATCHPAD);
	scratchpad[0] = read_byte();
	scratchpad[1] = read_byte();

	digit = scratchpad[0] >> 4;

	digit |= (scratchpad[1] & 0x7) << 4;

	decimal = scratchpad[0] & 0xf;
	decimal *= DECIMAL_STEPS_12BIT;

	resolution = 0;
	return digit * 10000 + decimal ;

}

void set_resolution()
{
	printk(KERN_INFO "set res = %d\n",res);
	switch(res)
	{
		case 9:
			config = 0x1f;
			break;
		case 10:
			config = 0x3f;
			break;
		case 11:
                        config = 0x5f;
                        break;
		case 12:
                        config = 0x7f;
                        break;
	}
	printk(KERN_INFO "set config = %u\n",config);


}

uint32_t reset(void)
{
	uint32_t i;

	put_low();
	make_delay(480);
	flush_line();
	make_delay(60);
	i = read_state();
	make_delay(420);

	return i;
}
void put_low(void)
{
	gpio_direction_output(gpio_num,0);
	gpio_set_value(gpio_num,0);
}

void make_delay(uint16_t us)
{
	udelay(us);
}

uint8_t read_bit(void)
{
	uint8_t b = 0;

	put_low();
	make_delay(1);
	flush_line();
	make_delay(14);

	if(read_state())
		b = 1;

	make_delay(45);

	return b;
}

uint8_t read_byte(void)
{
	uint8_t i = 8,n = 0;

	while(i --)
	{
		n >>= 1;
		n |= (read_bit() << 7);
	}

	return n;
}

uint32_t read_state(void)
{
	return gpio_get_value(gpio_num);
}

void write_byte(uint8_t b)
{
	uint8_t i = 8;
	while(i--)
	{
		write_bit(b & 1);
		b >>= 1;
	}
}

void write_bit(uint8_t bit)
{
	put_low();
	make_delay(1);
	if(bit)
		flush_line();
	make_delay(60);
	flush_line();
}

void flush_line(void)
{
	gpio_direction_input(gpio_num);
}

static ssize_t ds_read(struct file *f,char *buf,size_t size,loff_t *offset)
{

	int major,minor;
	char value[16];

	major = MAJOR(file_inode(f)->i_rdev);
	minor = MINOR(file_inode(f)->i_rdev);

	printk(KERN_INFO "ds_read\n");
	switch(minor){
		case 0:
			set_resolution();
			val = ds_get_temperature();
			printk(KERN_INFO "config = %u\n",config);
			sprintf(value,"\n%u,%u",val/10000,val%10000);
			break;
		case 1:
			sprintf(value,"ds18b20");
			break;
		default:
			sprintf(value,"00.0000");
	}

	printk(KERN_INFO "%s: temp = %u,%u \n",NAME,val/10000,val%10000);

	return 0;
}

void write_scratchpad(uint8_t s1,uint8_t s2,uint8_t conf)
{
	printk(KERN_ALERT "boucle write\n");
 	reset();
        make_delay(100);
        write_byte(CMD_SKIP_ROM);
        write_byte(CMD_RSCRATCHPAD);
        write_byte(s1);
        write_byte(s2);
        write_byte(conf);

}

void copy_scratchpad(void)
{
	reset();
	make_delay(1000);
	write_byte(CMD_SKIP_ROM);
	write_byte(CMD_CPYSCRATCHPAD);
	make_delay(1000);
}


static ssize_t ds_write(struct file *f,const char *buf,size_t size, loff_t *offset)
{

        printk(KERN_INFO "ds_write\n");
	//set_resolution();
	//write_scratchpad(scratchpad[2],scratchpad[3],config);
	//make_delay(1000);
	//copy_scratchpad();
	return 0;
}

static int ds_open(struct inode *in, struct file *f)
{	int major,minor;

	major = imajor(in);
	minor = iminor(in);

	printk(KERN_INFO "ds_open\n");
	if(minor > MINORS)
	{
		printk(KERN_ALERT "minors > MINORS\n");
		return -ENODEV;
	}
	return 0;
}

static int ds_release(struct inode *in,struct file *f)
{
	printk(KERN_INFO "ds_release Closing GPIO\n");
	return 0;
}

static void ds18b20_cleanup(void)
{
	device_destroy(ds18b20_class,dev);
	class_destroy(ds18b20_class);
	cdev_del(my_cdev);
	unregister_chrdev_region(dev,gpio_num);
	gpio_free(gpio_num);
	printk(KERN_INFO "ds18b20:GOODBYE\n");
}

module_init(ds18b20_init);
module_exit(ds18b20_cleanup);

MODULE_LICENSE(LICENSE);
MODULE_AUTHOR(AUTHOR);
MODULE_DESCRIPTION(DESCRIPTION);

