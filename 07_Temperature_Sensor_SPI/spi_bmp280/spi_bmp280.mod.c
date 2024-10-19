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
	{ 0x93e37a30, "spi_write_then_read" },
	{ 0xf99ba194, "spi_unregister_device" },
	{ 0x9db0905c, "spi_setup" },
	{ 0x76efcacc, "spi_new_device" },
	{ 0xc5850110, "printk" },
	{ 0x1b7fb81c, "spi_busnum_to_master" },
	{ 0x1fdc7df2, "_mcount" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xb3761495, "spi_sync" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "9DC3508F0507591A1E82E4E");
