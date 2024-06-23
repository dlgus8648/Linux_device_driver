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
	int fd;
	char *pin;

	if (argc != 2) {
		printf("Enter GPIO pin number\n");
		return -1;
	}

	pin = argv[1];

	export_gpio(pin);

	write_sys_gpio_file(pin, "direction", "out");
	for (int i = 0; i < 4; i++) {
		write_sys_gpio_file(pin, "value", "1");
		sleep(1);
		write_sys_gpio_file(pin, "value", "0");
		sleep(1);
	}

	unexport_gpio(pin);
	return 0;
}


