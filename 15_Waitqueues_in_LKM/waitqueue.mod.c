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
	{ 0xeae3dfd6, "__const_udelay" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x1e1e079e, "wake_up_process" },
	{ 0x6c3bad51, "kthread_create_on_node" },
	{ 0xa202bdab, "__register_chrdev" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x3854774b, "kstrtoll" },
	{ 0xdcb764ad, "memset" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0xd697e69a, "trace_hardirqs_on" },
	{ 0xec3d2e1b, "trace_hardirqs_off" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x4b50cb71, "cpu_hwcap_keys" },
	{ 0x3d8560e4, "cpu_hwcaps" },
	{ 0x14b89635, "arm64_const_caps_ready" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x8ddd8aad, "schedule_timeout" },
	{ 0xc5850110, "printk" },
	{ 0x92540fbf, "finish_wait" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x1000e51, "schedule" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x1fdc7df2, "_mcount" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A2C7BBF9C8FE053AD859AF0");
