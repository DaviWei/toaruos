#ifndef KERNEL_MOD_SND_H
#define KERNEL_MOD_SND_H

/* The format isn't really used for anything right now */
#define SND_FORMAT_L16SLE 0  /* Linear 16-bit signed little endian */

#include <logging.h>
#include <system.h>

typedef struct snd_device {
	char name[256];            /* Name of the device. */
	void * device;             /* Private data for the device. May be NULL. */
	uint32_t playback_speed;   /* Playback speed in Hz */
	uint32_t playback_format;  /* Playback format (SND_FORMAT_*) */
} snd_device_t;

/*
 * Register a device to be used with snd
 */
int snd_register(snd_device_t * device);

/*
 * Unregister a device
 */
int snd_unregister(snd_device_t * device);

/*
 * Request a buffer to play from snd. This is to be called from the device in
 * order to fill a buffer on demand. After the call the buffer is garaunteed
 * to be filled to the size requested even if that means writing zeroes for
 * when there are no other samples.
 */
int snd_request_buf(snd_device_t * device, uint32_t size, uint8_t *buffer);

#endif  /* KERNEL_MOD_SND_H */
