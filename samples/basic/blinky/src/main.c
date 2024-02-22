/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * NOTE:
 * 	Zephyr 개발환경 설치 가이드에서 default로 지정한 Path: ~/zephyrproject/zephyr/ 을 벗어나서,
 *	따로 폴더 만들어서 개발방법:
 *
 * 	요약하면:
 *
 * 	$ cp -r ~/zephyrproject/zephyr/samples/basic/blinky ~/.		//복제한다
 * 	$ cd ~
 * 	$ source ~/zephyrproject/zephyr/zephyr-env.sh			//터미널 새로 열때마다, 필수
 * 	$ west build -p always -b nucleo_h743zi blinky			//이제 git 으로 따로 관리하면 된다
 * 	$ west flash
 *
 * 	회로도와 아래 2 파일을 체크해야 한다.
 * 		samples/basic/blinky/src/main.c
 * 		~/zephyrproject/zephyr/boards/arm/nucleo_h743zi/nucleo_h743zi.dts
 */

#include <stdio.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* 1000 msec = 1 sec */
#define SLEEP_TIME_MS   1000

/* The devicetree node identifier for the "led0" alias. */
#define LED0_NODE	DT_ALIAS(led0)
#define LED0_RTK	DT_ALIAS(led2)	/* PC1 */

/*
 * A build error on this line means your board is unsupported.
 * See the sample documentation for information on how to fix this.
 */
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);	/* param2: property name */

int main(void)
{
	int ret;
	bool led_state = true;

	if (!gpio_is_ready_dt(&led)) {
		return 0;
	}

	ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	while (1) {
		ret = gpio_pin_toggle_dt(&led);
		if (ret < 0) {
			return 0;
		}

		led_state = !led_state;
		printf("RTK LED state: %s\n", led_state ? "ON" : "OFF");
		k_msleep(SLEEP_TIME_MS);
	}
	return 0;
}
