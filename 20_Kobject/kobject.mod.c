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
	{ 0x9236eb2f, "kobject_put" },
	{ 0x572b6840, "sysfs_create_group" },
	{ 0x83f26d26, "kobject_create_and_add" },
	{ 0x138ebfb1, "kernel_kobj" },
	{ 0xe783e261, "sysfs_emit" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x8c8569cb, "kstrtoint" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "5DF63FC54B7543DB281FBF4");
