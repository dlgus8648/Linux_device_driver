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
	{ 0xf9a482f9, "msleep" },
	{ 0x1fdc7df2, "_mcount" },
	{ 0x47229b5c, "gpio_request" },
	{ 0x10bbc261, "gpio_to_desc" },
	{ 0x9db0905c, "spi_setup" },
	{ 0x1b7fb81c, "spi_busnum_to_master" },
	{ 0xc5850110, "printk" },
	{ 0x76efcacc, "spi_new_device" },
	{ 0x2cda6e8, "gpiod_direction_output_raw" },
	{ 0xb3761495, "spi_sync" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xfe990052, "gpio_free" },
	{ 0x915df5ec, "gpiod_set_raw_value" },
	{ 0xf99ba194, "spi_unregister_device" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "D4A391A02CA522C9B4D4869");
