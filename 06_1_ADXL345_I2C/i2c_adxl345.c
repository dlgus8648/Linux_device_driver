#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/i2c.h>
#include <linux/of.h>
#include <linux/delay.h>

#define ADXL345_I2C_ADDR      0x53
#define ADXL345_REG_DEVID     0x00
#define ADXL345_REG_DATA_FORMAT 0x31
#define ADXL345_REG_POWER_CTL  0x2D
#define ADXL345_REG_DATAX0    0x32
#define ADXL345_RANGE_4G      0x01
#define ADXL345_MEASURE_MODE  0x08

struct adxl345_data {
    struct i2c_client *client;
};

/* Write a single register */
static int adxl345_write_reg(struct i2c_client *client, u8 reg, u8 value)
{
    u8 buf[2] = {reg, value};
    int ret = i2c_master_send(client, buf, 2);
    if (ret < 0) {
        dev_err(&client->dev, "Failed to write register 0x%02X\n", reg);
        return ret;
    }
    return 0;
}

/* Read a single register */
static int adxl345_read_reg(struct i2c_client *client, u8 reg, u8 *value)
{
    int ret;

    ret = i2c_master_send(client, &reg, 1);
    if (ret < 0) {
        dev_err(&client->dev, "Failed to send register address 0x%02X\n", reg);
        return ret;
    }

    ret = i2c_master_recv(client, value, 1);
    if (ret < 0) {
        dev_err(&client->dev, "Failed to read register 0x%02X\n", reg);
        return ret;
    }

    return 0;
}

/* Read multiple registers */
static int adxl345_read_data(struct i2c_client *client, u8 reg, u8 *data, size_t len)
{
    int ret;

    ret = i2c_master_send(client, &reg, 1);
    if (ret < 0) {
        dev_err(&client->dev, "Failed to send register address 0x%02X\n", reg);
        return ret;
    }

    ret = i2c_master_recv(client, data, len);
    if (ret < 0) {
        dev_err(&client->dev, "Failed to read data from 0x%02X\n", reg);
        return ret;
    }

    return 0;
}

/* Initialize the ADXL345 sensor */
static int adxl345_init_device(struct i2c_client *client)
{
    u8 devid;
    u8 data[6];
    int16_t x, y, z;
    int xg_milli, yg_milli, zg_milli; // 밀리 단위

    /* Read device ID to verify communication */
    if (adxl345_read_reg(client, ADXL345_REG_DEVID, &devid)) {
        dev_err(&client->dev, "Failed to read device ID\n");
        return -EIO;
    }

    if (devid != 0xE5) {
        dev_err(&client->dev, "Invalid device ID: 0x%02X\n", devid);
        return -EINVAL;
    }

    /* Set data format to ±4g */
    if (adxl345_write_reg(client, ADXL345_REG_DATA_FORMAT, ADXL345_RANGE_4G)) {
        dev_err(&client->dev, "Failed to set data format\n");
        return -EIO;
    }

    /* Enable measurement mode */
    if (adxl345_write_reg(client, ADXL345_REG_POWER_CTL, ADXL345_MEASURE_MODE)) {
        dev_err(&client->dev, "Failed to enable measurement mode\n");
        return -EIO;
    }

    dev_info(&client->dev, "ADXL345 initialized successfully\n");

    /* Read and log X, Y, Z data */
    if (adxl345_read_data(client, ADXL345_REG_DATAX0, data, 6) == 0) {
        x = (data[1] << 8) | data[0];
        y = (data[3] << 8) | data[2];
        z = (data[5] << 8) | data[4];

        // g 단위 대신 밀리(g * 1000) 단위로 변환
        xg_milli = x * 78 / 10;
        yg_milli = y * 78 / 10;
        zg_milli = z * 78 / 10;

        dev_info(&client->dev, "Acceleration [mg]: X = %d, Y = %d, Z = %d\n",
                 xg_milli, yg_milli, zg_milli);
    } else {
        dev_err(&client->dev, "Failed to read acceleration data\n");
    }

    return 0;
}

/* Probe function for device initialization */
static int adxl345_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    struct adxl345_data *data;

    /* Allocate driver data */
    data = devm_kzalloc(&client->dev, sizeof(struct adxl345_data), GFP_KERNEL);
    if (!data)
        return -ENOMEM;

    data->client = client;

    /* Initialize the sensor */
    return adxl345_init_device(client);
}

/* Remove function */
static int adxl345_remove(struct i2c_client *client)
{
    dev_info(&client->dev, "ADXL345 removed\n");
    return 0;
}

/* Device ID table for I2C */
static const struct i2c_device_id adxl345_id[] = {
    {"adxl345", 0},
    {}
};
MODULE_DEVICE_TABLE(i2c, adxl345_id);

/* Device tree match table */
static const struct of_device_id adxl345_of_match[] = {
    {.compatible = "adi,adxl345"},
    {}
};
MODULE_DEVICE_TABLE(of, adxl345_of_match);

/* I2C driver structure */
static struct i2c_driver adxl345_driver = {
    .driver = {
        .name = "adxl345",
        .of_match_table = adxl345_of_match,
    },
    .probe = adxl345_probe,
    .remove = adxl345_remove,
    .id_table = adxl345_id,
};

module_i2c_driver(adxl345_driver);

MODULE_AUTHOR("KIMRIHYEON");
MODULE_DESCRIPTION("Linux I2C Driver for ADXL345 with Acceleration Data Logging");
MODULE_LICENSE("GPL");

