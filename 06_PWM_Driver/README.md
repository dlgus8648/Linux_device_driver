#  /boot/firmware/usercfg.txt
![1](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/2d0f36f8-56c1-43b7-8159-8987cf5ccbb3)

## Configuration Changes

The following changes should be placed in the `config.txt` file:
**Enable PWM on Two Channels**:
   ```
   dtoverlay=pwm-2chan,pin=12,func=4,pin2=13,func2=4
   ```
   This line enables PWM on two channels. It configures pin 12 and pin 13 for PWM functionality with the corresponding functions set to 4.


```
# Place "config.txt" changes (dtparam, dtoverlay, disable_overscan, etc.) in
# this file. Please refer to the README file for a description of the various
# configuration files on the boot partition.

dtoverlay=spi1-1cs,cs0_spidev=disabled
dtoverlay=pwm-2chan,pin=12,func=4,pin2=13,func2=4
```

Ensure you save the `config.txt` file after making these changes and reboot your system for the changes to take effect.

---
# Demo
![2](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/d22209a7-98de-4a7e-b700-42fe316cc613)

https://github.com/dlgus8648/Linux_device_driver/assets/139437162/87a13d17-dc89-43cd-99c2-c49c02bcb85b





## Overview

This document explains how to use the PWM driver to adjust the duty cycle of a PWM signal by writing characters to a device file. Each character corresponds to a specific duty cycle percentage based on its ASCII value.

## Usage

The following examples demonstrate how to use the `echo` command to write characters to the PWM driver device file (`/dev/my_pwm_driver`) and set the PWM duty cycle.

### Example Commands

1. **Set Duty Cycle to 0%**
   ```bash
   $ echo a > /dev/my_pwm_driver
   ```
   - The character `'a'` is written to the device file.
   - The `driver_write` function is called, receiving the character `'a'`.
   - The character `'a'` is converted to its ASCII value and calculated as `'a' - 'a' = 0`.
   - The PWM on-time is set to `100000000 * 0 = 0`.
   - The PWM duty cycle is set to 0%.

2. **Set Duty Cycle to 90%**
   ```bash
   $ echo j > /dev/my_pwm_driver
   ```
   - The character `'j'` is written to the device file.
   - The `driver_write` function is called, receiving the character `'j'`.
   - The character `'j'` is converted to its ASCII value and calculated as `'j' - 'a' = 9`.
   - The PWM on-time is set to `100000000 * 9 = 900000000`.
   - The PWM duty cycle is set to 90%.

3. **Set Duty Cycle to 40%**
   ```bash
   $ echo e > /dev/my_pwm_driver
   ```
   - The character `'e'` is written to the device file.
   - The `driver_write` function is called, receiving the character `'e'`.
   - The character `'e'` is converted to its ASCII value and calculated as `'e' - 'a' = 4`.
   - The PWM on-time is set to `100000000 * 4 = 400000000`.
   - The PWM duty cycle is set to 40%.

4. **Reset Duty Cycle to 0%**
   ```bash
   $ echo a > /dev/my_pwm_driver
   ```
   - The character `'a'` is written to the device file.
   - The `driver_write` function is called, receiving the character `'a'`.
   - The character `'a'` is converted to its ASCII value and calculated as `'a' - 'a' = 0`.
   - The PWM on-time is set to `100000000 * 0 = 0`.
   - The PWM duty cycle is reset to 0%.

## Summary

Each command sets the PWM duty cycle based on the character written to the device file. The following table summarizes the duty cycle settings:

| Character | Duty Cycle |
|-----------|-------------|
| `'a'`     | 0%          |
| `'j'`     | 90%         |
| `'e'`     | 40%         |

By using this method, users can easily adjust the PWM signal's duty cycle.
