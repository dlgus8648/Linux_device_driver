#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xfe9bc451, "module_layout" },
	{ 0x478e58fd, "gpiod_unexport" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x58055dbb, "cdev_del" },
	{ 0x5cf9db0a, "class_destroy" },
	{ 0x7e1f9c52, "device_destroy" },
	{ 0x7a11c595, "gpiod_export" },
	{ 0x2cda6e8, "gpiod_direction_output_raw" },
	{ 0xfe990052, "gpio_free" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x3bae1a24, "device_create" },
	{ 0x92f847a3, "__class_create" },
	{ 0x21872aaa, "cdev_add" },
	{ 0xe7bd1d8b, "cdev_init" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0xb0fcb281, "gpiod_get_raw_value" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x56470118, "__warn_printk" },
	{ 0xd697e69a, "trace_hardirqs_on" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0xec3d2e1b, "trace_hardirqs_off" },
	{ 0x3d8560e4, "cpu_hwcaps" },
	{ 0x915df5ec, "gpiod_set_raw_value" },
	{ 0x10bbc261, "gpio_to_desc" },
	{ 0xdcb764ad, "memset" },
	{ 0x4b50cb71, "cpu_hwcap_keys" },
	{ 0x14b89635, "arm64_const_caps_ready" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xc5850110, "printk" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "987BF03FCEBF09FE5005E95");
