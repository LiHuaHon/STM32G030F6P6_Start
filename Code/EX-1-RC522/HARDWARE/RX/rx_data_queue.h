#ifndef __ESP_DATA_QUEUE_H_
#define __ESP_DATA_QUEUE_H_

#include "sys.h"
#include <string.h>
#include <stdio.h>

extern  UART_HandleTypeDef huart1;

/*缓冲队列的个数需要为2的幂*/
#define QUEUE_NODE_NUM        (1)            /*缓冲队列的大小（有多少个缓冲区）*/
#define QUEUE_NODE_DATA_LEN   (28)          /*单个接收缓冲区大小*/

/*队列的主体数据类型接口*/
#define QUEUE_DATA_TYPE  				ESP_USART_FRAME

/*缓冲接收发送串口*/
#define  QUEUE_USART                    huart1
#define  QUEUE_USART_BAUDRATE           57600

/*缓冲接收发送串口宏定义*/
#define  QUEUE_USART_IRQ                USART1_IRQn

/*数据主体*/
typedef struct 
{
	char  *head; 	                             /*缓冲区头指针*/	
	uint16_t len;                              /*接收到的数据长度*/

}ESP_USART_FRAME;

//队列结构
typedef struct {
	int         size;                          /* 缓冲区大小*/
	int         read;                          /* 读指针*/
	int         write;                         /* 写指针*/
	int read_using;	                           /*正在读取的缓冲区指针*/
	int write_using;		                       /*正在写入的缓冲区指针*/
	QUEUE_DATA_TYPE    *elems[QUEUE_NODE_NUM]; /* 缓冲区地址 */
} QueueBuffer;

extern QueueBuffer rx_queue;
extern u8 QueueNewFlage ;

void cbReadFinish(QueueBuffer *cb);
void cbWriteFinish(QueueBuffer *cb);
int cbIsFull(QueueBuffer *cb) ; 
int cbIsEmpty(QueueBuffer *cb) ;
void rx_queue_init(void);
void pull_data_from_queue(void);
void push_data_to_queue(char *src_dat,uint16_t src_len);
QUEUE_DATA_TYPE* cbWrite(QueueBuffer *cb);
QUEUE_DATA_TYPE* cbRead(QueueBuffer *cb);
QUEUE_DATA_TYPE* cbWriteUsing(QueueBuffer *cb) ;



#endif



