#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5a18046e, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x426b950b, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xdbf6de64, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0xdb7c2b58, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x9077dafd, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x4aa7848f, __VMLINUX_SYMBOL_STR(gpiod_direction_input) },
	{ 0x64df6112, __VMLINUX_SYMBOL_STR(gpiod_get_raw_value) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x93a80a44, __VMLINUX_SYMBOL_STR(gpiod_set_raw_value) },
	{ 0x54ed4bea, __VMLINUX_SYMBOL_STR(gpiod_direction_output_raw) },
	{ 0x530456a0, __VMLINUX_SYMBOL_STR(gpio_to_desc) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0x5a7bb743, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x7e20ba1d, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0xb1ee29da, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x6dda5865, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0xb4d15de9, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb1ad28e0, __VMLINUX_SYMBOL_STR(__gnu_mcount_nc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "648F53CF96758F9BFDD180B");
