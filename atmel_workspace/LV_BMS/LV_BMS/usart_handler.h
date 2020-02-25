/*
 * usart_handler1.h
 *
 * Created: 2020-02-25 13:22:56
 *  Author: mat15mal
 */ 


#ifndef USART_HANDLER_H_
#define USART_HANDLER_H_



//handles the messages from usart and decides the action
void usart_done(void);

//String arrays initialization used in the usart handler function
void usart_strings_init(void);
#endif /* USART_HANDLER_H_ */