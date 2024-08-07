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
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xc1514a3b, "free_irq" },
	{ 0xa202bdab, "__register_chrdev" },
	{ 0x92d5838e, "request_threaded_irq" },
	{ 0x87424afe, "gpiod_to_irq" },
	{ 0xaeabb44b, "gpiod_set_debounce" },
	{ 0xfe990052, "gpio_free" },
	{ 0xb19b0b63, "gpiod_direction_input" },
	{ 0x10bbc261, "gpio_to_desc" },
	{ 0x47229b5c, "gpio_request" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0xc5850110, "printk" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "D4657B6673BAF840C16BFFF");
