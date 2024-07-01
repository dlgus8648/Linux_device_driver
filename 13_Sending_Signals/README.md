
# GPIO IRQ Signal Project

This project demonstrates how to handle GPIO (General Purpose Input/Output) interrupts in a Linux environment. The project includes a userspace application and a kernel module that interact to handle GPIO signals.

## Project Structure

- `gpio_irq_signal.c`: Kernel module source code that handles GPIO interrupts.
- `testapp.c`: Userspace application that waits for signals from the kernel module.
- `Makefile`: Makefile to compile the kernel module and the userspace application.
- `README.md`: This file.

## Requirements

- Linux operating system
- GCC compiler
- Root privileges to load the kernel module and run the userspace application

## Installation and Usage

1. **Compile the Kernel Module and Userspace Application:**

   ```sh
   make
   ```

2. **Load the Kernel Module:**

   ```sh
   sudo insmod gpio_irq_signal.ko
   ```

3. **Run the Userspace Application:**

   ```sh
   sudo ./a.out
   ```

   You should see the following output indicating that the application is waiting for signals:

   ```
   PID: 2772
   Wait for signal...
   ```

![제목 없음](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/6750ff92-a56f-4cc8-8d66-589ba41056fe)


4. **Trigger the GPIO Interrupt:**

   Press the button or perform the action that triggers the GPIO interrupt. You should see messages indicating that the button was pressed:

   ```
   Button was pressed!
   Button was pressed!
   ```

5. **Check Kernel Messages:**

   You can check the kernel messages using the `dmesg` command to verify that the interrupt service routine (ISR) was called:
```markdown
   ```sh
   dmesg | tail
   ```

   Expected output:

   ```
   [  765.505581] gpio_irq_signal: Userspace app with PID 2772 is registered
   [  786.404864] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  787.684285] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  788.303539] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  788.779267] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  789.318061] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  790.553854] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  791.454770] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  791.454826] gpio_irq_signal: Interrupt was triggered and ISR was called!
   [  791.902612] gpio_irq_signal: Interrupt was triggered and ISR was called!
   ```

## DEMO


https://github.com/dlgus8648/Linux_device_driver/assets/139437162/5c52e975-90ac-4c9c-8d7a-b2a39074cebc

