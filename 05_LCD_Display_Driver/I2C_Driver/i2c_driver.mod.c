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
	{ 0x1944271d, "i2c_del_driver" },
	{ 0xd5d1ace1, "i2c_unregister_device" },
	{ 0x1072884e, "i2c_put_adapter" },
	{ 0x47c1e9a8, "i2c_register_driver" },
	{ 0x4d592fbc, "i2c_new_device" },
	{ 0x65093f2d, "i2c_get_adapter" },
	{ 0xc5850110, "printk" },
	{ 0xf9a482f9, "msleep" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x1582cdb2, "i2c_transfer_buffer_flags" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("i2c:ssd1306_oled");

MODULE_INFO(srcversion, "9D8F14E8EF8CA84F13377E7");
