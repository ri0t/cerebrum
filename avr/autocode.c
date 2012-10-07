/* AUTOGENERATED CODE FOLLOWS!
 * This file contains the code generated from the module templates as well as
 * some glue logic. It is generated following the device config by "generate.py"
 * in this very folder. Please refrain from modifying it, modify the templates
 * and generation logic instead.
 * 
 * Device name: ar0, build version: 23, build date: 2012-10-07 20:13:33.036115
 */

#include <string.h>
#include "autocode.h"
#include "comm.h"
/*
 Copyright (C) 2012 jaseg <s@jaseg.de>

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 version 3 as published by the Free Software Foundation.
 */

#include <avr/io.h>

void callback_simple_io_24_setState (uint16_t argsize, uint8_t* args){
	PORTB &= ~(1<<5);
	if(args[0])
		PORTB |= (1<<5);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x00);
}

void callback_simple_io_24_getState (uint16_t argsize, uint8_t* args){
	uart_putc(0x00);
	uart_putc(0x01);
	uart_putc(PINB & (1<<5));
	uart_putc(0x00);
	uart_putc(0x00);
}

void callback_simple_io_24_setDirection (uint16_t argsize, uint8_t* args){
	DDRB &= ~(1<<5);
	if(args[0])
		DDRB |= (1<<5);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x00);
	uart_putc(0x00);
}

void callback_simple_io_24_getDirection (uint16_t argsize, uint8_t* args){
	uart_putc(0x00);
	uart_putc(0x01);
	uart_putc(DDRB & (1<<5));
	uart_putc(0x00);
	uart_putc(0x00);
}

#include "config.h"
#include <avr/pgmspace.h>

comm_callback comm_callbacks[] = {
	&callback_get_descriptor_auto, //0
	&callback_simple_io_24_setState, //1
	&callback_simple_io_24_getState, //2
	&callback_simple_io_24_setDirection, //3
	&callback_simple_io_24_getDirection, //4
};

const uint16_t num_callbacks = 5;

void init_auto(){
}

void loop_auto(){
}

void callback_get_descriptor_auto(uint16_t alen, uint8_t* argbuf){
	//FIXME
	uart_putc(auto_config_descriptor_length >> 8);
	uart_putc(auto_config_descriptor_length & 0xFF);
	for(const char* i=auto_config_descriptor; i < auto_config_descriptor+auto_config_descriptor_length; i++){
		uart_putc(pgm_read_byte(i));
	}
	//FIXME add crc generation
	uart_putc(0x00);
	uart_putc(0x00);
}

