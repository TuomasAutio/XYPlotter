/*
 * user_vcom.h
 *
 *  Created on: 5.9.2017
 *      Author: krl
 */

#ifndef USER_VCOM_H_
#define USER_VCOM_H_

/* remove comment on the following line to make CDC task to poll without yielding/blocking */
//#define POLLING_CDC

/* number of USB receive buffers */
#define RCV_BUFFERS 16
/* size of receive buffers */
#define RCV_BUFSIZE 64


/* this is needed to start CDC USB task. Since CDC functions are written in C we need
 * extern "C" - declaration to tell C++ compiler to use C naming convention for this function.
 */
#ifdef __cplusplus
extern "C"
{
#endif

/* Virtual com port main task */
void cdc_task(void *pvParameters);

/* Writes data to USB com port, maximum length not restricted.
 * This function it thread safe and blocks until the data has been transmitted.
 *  */
void USB_send(uint8_t *data, uint32_t length);

/* Reads data from USB com port.
 * Function returns number of received bytes.
 * Function blocks until data is available. This function is thread safe and
 * requires no locking.
 * Length must be at least RCV_BUFSIZE. If length is smaller some data may be discarded.
 * Function checks data sizes and never overflows buffers. If available data is longer than specified buffer
 * size the excess data is discarded */
uint32_t USB_receive(uint8_t *data, uint32_t length);

#ifdef __cplusplus
}
#endif


#endif /* USER_VCOM_H_ */
