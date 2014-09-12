#include "leds_hal.h"
#include "../leds_hal_define.h"

int dev_file = 0;


int led_on(struct led_control_device_t *dev, int32_t led)
{
	return led_on_off(dev, led, 1);
}

int led_off(struct led_control_device_t *dev, int32_t led)
{

	return led_on_off(dev, led, 0);
}
int led_device_close(struct hw_device_t* device)
{
	struct led_control_device_t* ctx = (struct led_control_device_t*) device;
	if (ctx)
	{
		free(ctx);
	}
	close(dev_file);
	return 0;
}
static void leds_init_gpm()
{

}
static int led_device_open(const struct hw_module_t* module, const char* name,
		struct hw_device_t** device)
{
	struct led_control_device_t *dev;
	dev = (struct led_control_device_t *) malloc(sizeof(*dev));
	memset(dev, 0, sizeof(*dev));

	dev->hw_device.tag = HARDWARE_DEVICE_TAG;
	dev->hw_device.version = 0;
	dev->hw_device.module = (struct hw_module_t*) module;
	dev->hw_device.close = led_device_close;

	dev->set_on = led_on;
	dev->set_off = led_off;

	//*device = &dev->hw_device;
	*device = (hw_device_t*) dev;

	dev_file = open("/dev/s3c6410_leds_hal", O_RDWR);
	if (dev_file < 0)
	{
		LOGI("LED Stub: open /dev/s3c6410_leds_hal  fail.");
	}
	else
	{
		LOGI("LED Stub: open /dev/s3c6410_leds_hal success .");
	}
	leds_init_gpm();
	return 0;
}

static struct hw_module_methods_t led_module_methods = { open: led_device_open };

struct led_module_t HAL_MODULE_INFO_SYM = { hw_module:
{ tag: HARDWARE_MODULE_TAG, version_major: 1, version_minor: 0, id
		: LED_HARDWARE_MODULE_ID, name: "Sample LED HAL Stub", author: "Lining",
		methods: &led_module_methods, }

};

/*struct hw_module_t HAL_MODULE_INFO_SYM =
 { tag: HARDWARE_MODULE_TAG, version_major: 1, version_minor: 0, id
 : LED_HARDWARE_MODULE_ID,
 name: "Sample LED HAL Stub",
 author: "Lining",
 methods: &led_module_methods,

 };*/

