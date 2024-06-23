#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

void write_sys_gpio(char *sys_gpio_file, char *value)
{
	int fd;
	int len = strlen(value);

	fd = open(sys_gpio_file, O_WRONLY);
	if (fd == -1) {
		printf("Error: cannot open %s\n", sys_gpio_file);
		goto err;
	}

	if (write(fd, value, len) != len) {
		printf("Error: cannot write %s\n", sys_gpio_file);
		goto err;
	}

	close(fd);
	return;
err:
	exit(1);
}

void write_sys_gpio_file(char *pin, char *sys_gpio_file, char *value)
{
	char sys_gpio[1024];

	sprintf(sys_gpio, "/sys/class/gpio/gpio%s/%s", pin, sys_gpio_file);
	write_sys_gpio(sys_gpio, value);
}

void export_gpio(char *pin)
{
	char sys_gpio[1024];

	sprintf(sys_gpio, "/sys/class/gpio/gpio%s", pin);
	if (access(sys_gpio, F_OK ) != 0 )
		write_sys_gpio("/sys/class/gpio/export", pin);
}

void unexport_gpio(char *pin)
{
	char sys_gpio[1024];

	sprintf(sys_gpio, "/sys/class/gpio/gpio%s", pin);
	if (access(sys_gpio, F_OK ) == 0 )
		write_sys_gpio("/sys/class/gpio/unexport", pin);
}

int main(int argc, char *argv[])
{
	int fd, len;
	char *pin;
	char *value;
	char sys_gpio[1024];

	if (argc != 3) {
		printf("Enter GPIO pin number / value(0 or 1)\n");
		return -1;
	}

	pin = argv[1];
	value = argv[2];
	len = strlen(pin);

	sprintf(sys_gpio, "/sys/class/gpio/gpio%s", pin);
	if (access(sys_gpio, F_OK ) == 0 )
		goto skip_export;

	fd = open("/sys/class/gpio/export", O_WRONLY);
	if (fd == -1) {
		printf("Error: cannot open GPIO export\n");
		return -1;
	}

	if (write(fd, pin, len) != len) {
		printf("Error: cannot export GPIO %s\n", pin);
		return -1;
	}

	close(fd);

skip_export:
	write_sys_gpio_file(pin, "direction", "out");
	write_sys_gpio_file(pin, "value", value);
	return 0;
}

