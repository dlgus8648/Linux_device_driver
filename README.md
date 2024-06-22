# Linux Device Driver Development Practice using Raspberry Pi 4B

This repository contains practice exercises for developing Linux device drivers using the Raspberry Pi 4B.

## Introduction

The goal of this project is to provide hands-on experience in developing Linux device drivers on the Raspberry Pi 4B. This includes setting up the development environment, writing simple drivers, and testing them on the Raspberry Pi.

## Prerequisites

1. **Raspberry Pi 4B**: Ensure you have an SD card with Raspbian OS installed.
2. **Computer**: You will need a computer to connect to your Raspberry Pi via SSH or directly.
3. **Internet Connection**: Required for installing and updating packages.

## Setting Up the Environment

1. **Update and Upgrade Your System**

    ```sh
    sudo apt update
    sudo apt upgrade
    ```

2. **Install Necessary Packages**

    ```sh
    sudo apt install raspberrypi-kernel-headers build-essential
    ```

3. **Clone This Repository**

    ```sh
    git clone https://github.com/yourusername/linux-device-driver-practice.git
    cd linux-device-driver-practice
    ```


|Project|Features|
|---|---|
|1. Hello World Linux Kernel Module|WEB|
|2. Device Numbers and Files|WEB / EXE|
|3. Auto Device File creation & Read - Write - Callback|WEB|
|4. GPIO driver|WEB|
|5. LCD Display Driver(SSD1306) using I2C protocol|WEB|
|6. LCD Display Driver(SSD1306) using SPI protocol|WEB / EXE|
|7. PWM Driver|WEB|
|8. Temperature Sensor(BMP280) using I2C protocol|WEB|
|9. Temperature Sensor(BMP280) using SPI protocol|WEB / EXE|
|10. High Resolution Timer in a Linux Kerenel Module|WEB|
|11. Parameters for a Linux Kerenl Module|WEB|
|12. IOCTL in a Linux kerenl module|WEB|
|13. Treads in a Linux Kerenl Module|WEB / EXE|
|14. Sending a signal from Kerenl to Userspace|WEB|
|15. The Poll Callback in a Linux Kerenl Module|WEB|
|16. Waitqueues in a Linux Kerenl Module|WEB|
|17. Create procfs entries from a Linux Kernel Module|WEB|
|18. Create sysfs entries from a Linux Kernel Module|WEB / EXE|
|19. Parsing from the Device tree in a Linux Kerenl Module|WEB|
|20. Device Tree GPIO Driver|WEB|
|21. Device Tree Driver for an I2C device|WEB|
|22. Device Tree Driver for an SPI device|WEB|
|23. Dynamical memory management in a Linux Kernel Module|WEB|
|24. Misc device|WEB|
|25. Mutex exclusive access to shared resources|WEB / EXE|



