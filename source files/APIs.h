/*
 * APIs.h
 *
 * Created: 05/01/2021 2:18:37 PM
 *  Author: OLAOLUWA
 */ 


#ifndef API_H_
#define API_H_

void ConfigAnalogComparator(void);
void ConfigTimer0(void);
void BlockingDelay(uint32_t numberOfIncrements);
void StartSoapPump(void);
void StopSoapPump(void);
void StartWaterPump(void);
void StopWaterPump(void);

#endif /* API_H_ */
