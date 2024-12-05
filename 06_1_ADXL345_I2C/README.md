## Device Tree
```
/dts-v1/;
/plugin/;

/ {
    compatible = "brcm,bcm2835";

    fragment@0 {
        target = <&i2c1>; // Raspberry Pi 4의 두 번째 I2C 컨트롤러
        __overlay__ {
            #address-cells = <1>;
            #size-cells = <0>;
            status = "okay";

            adxl345@53 {
                compatible = "adi,adxl345";
                reg = <0x53>; // ADXL345 I2C 주소
            };
        };
    };
};
```
