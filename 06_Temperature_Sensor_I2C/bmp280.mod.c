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
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x58055dbb, "cdev_del" },
	{ 0x1944271d, "i2c_del_driver" },
	{ 0xd5d1ace1, "i2c_unregister_device" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x5cf9db0a, "class_destroy" },
	{ 0xe2e196cb, "i2c_smbus_write_byte_data" },
	{ 0x3ed42b0d, "i2c_smbus_read_word_data" },
	{ 0x1072884e, "i2c_put_adapter" },
	{ 0x47c1e9a8, "i2c_register_driver" },
	{ 0x4d592fbc, "i2c_new_device" },
	{ 0x65093f2d, "i2c_get_adapter" },
	{ 0x7e1f9c52, "device_destroy" },
	{ 0x21872aaa, "cdev_add" },
	{ 0xe7bd1d8b, "cdev_init" },
	{ 0x3bae1a24, "device_create" },
	{ 0x92f847a3, "__class_create" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xd697e69a, "trace_hardirqs_on" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0xec3d2e1b, "trace_hardirqs_off" },
	{ 0x3d8560e4, "cpu_hwcaps" },
	{ 0x4b50cb71, "cpu_hwcap_keys" },
	{ 0x14b89635, "arm64_const_caps_ready" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x656e4a6e, "snprintf" },
	{ 0xafdbd6d, "i2c_smbus_read_byte_data" },
	{ 0xc5850110, "printk" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "2B212FF02796F4E09B49204");
