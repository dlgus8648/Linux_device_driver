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


# Demo
![2](https://github.com/dlgus8648/Linux_device_driver/assets/139437162/d22209a7-98de-4a7e-b700-42fe316cc613)

https://github.com/dlgus8648/Linux_device_driver/assets/139437162/87a13d17-dc89-43cd-99c2-c49c02bcb85b

