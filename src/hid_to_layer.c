#define DT_DRV_COMPAT zmk_hid_to_layer

#include <raw_hid/events.h>
#include <zephyr/device.h>
#include <drivers/behavior.h>
#include <zephyr/logging/log.h>

#include <zmk/keymap.h>
#include <zmk/behavior.h>

// static int raw_hid_received_event_listener(const zmk_event_t *eh) {
    // struct raw_hid_received_event *event = as_raw_hid_received_event(eh);
    // if (event->data==0) {
        // // do something
		// zmk_keymap_layer_to(0);
    // }
	// if (event->data==1) {
        // // do something
		// zmk_keymap_layer_to(4);
    // }
	// if (event->data==2) {
        // // do something
		// zmk_keymap_layer_activate(8);
    // }
	// if (event->data==3) {
        // // do something
		// zmk_keymap_layer_deactivate(8);
    // }

    // return ZMK_EV_EVENT_BUBBLE;
// }

static void process_raw_hid_data(uint8_t *data) {
    LOG_INF("display_process_raw_hid_data - received data_type %u", data[0]);
	
    uint8_t data_type = data[0];
		switch (data_type) {
		case 0:
		zmk_keymap_layer_to(0);
		case 1:
		zmk_keymap_layer_to(4);
		case 2:
		zmk_keymap_layer_activate(8);
		case 3:
		zmk_keymap_layer_deactivate(8);
	}

static int raw_hid_received_event_listener(const zmk_event_t *eh) {
    struct raw_hid_received_event *event = as_raw_hid_received_event(eh);
    if (event) {
        process_raw_hid_data(event->data);
    }

    return ZMK_EV_EVENT_BUBBLE;
}

ZMK_LISTENER(process_raw_hid_event, raw_hid_received_event_listener);
ZMK_SUBSCRIPTION(process_raw_hid_event, raw_hid_received_event);