#ifndef __screen__
#define __screen__

#include <cstdint>
#include "contr_mem.h"


#include "low_level.h"
#include <cstdint>



class _screen {

public:
	_screen():cur_x(0),cur_y(0) {};	

private:
	enum _screen_param{
		VIDEO_MEMORY=0xb8000,
		MAX_ROWS=25,
		MAX_COLUMNS=80,
		WHITE_ON_BLACK=0x0f,
		SCREEN_CTRL_REG=0x3d4,
		SCREEN_DATA_REG=0x3d5
	};		

private:
	uint16_t *textpointer;
	int32_t cur_x;
	int32_t cur_y;

	contr_mem _mem0;
	_contr_regs _regs;

	void move_cursor(){
		uint16_t temp;
		temp = cur_y*_screen_param::MAX_COLUMNS + cur_x;
		
		_regs.port_byte_put(_screen_param::SCREEN_CTRL_REG, 14);
		_regs.port_byte_put(_screen_param::SCREEN_DATA_REG, temp >> 8);
		_regs.port_byte_put(_screen_param::SCREEN_CTRL_REG, 15);
		_regs.port_byte_put(_screen_param::SCREEN_DATA_REG, temp);
	}

	void cls(){
		uint16_t blank;
		uint16_t attribute_byte;
				
		attribute_byte = _screen_param::WHITE_ON_BLACK << 8;
		blank = attribute_byte | 0x20;

		
		for(int32_t i=0; i<_screen_param::MAX_ROWS; i++){
			_mem0.memset(textpointer+ i*_screen_param::MAX_COLUMNS, blank, _screen_param::MAX_COLUMNS);		
		}

		cur_x = 0;
		cur_y = 0;
			
		move_cursor();		
	}

	void scroll(){
		uint16_t temp, blank, attribute_byte;


		attribute_byte = _screen_param::WHITE_ON_BLACK << 8;	
		blank = attribute_byte | 0x20;



		if ( cur_y >= _screen_param::MAX_ROWS ){
			temp = cur_y - _screen_param::MAX_ROWS + 1;
			_mem0.memcpy(textpointer, textpointer + temp*_screen_param::MAX_COLUMNS, (_screen_param::MAX_ROWS - temp) * _screen_param::MAX_COLUMNS * 2);

			_mem0.memset(textpointer + (_screen_param::MAX_ROWS - temp)*_screen_param::MAX_COLUMNS, blank, _screen_param::MAX_COLUMNS);
			cur_y = MAX_ROWS - 1;
		}

	}

	void printchar(const char ch){
		uint16_t *where;
		uint16_t attribute_byte;

		attribute_byte = _screen_param::WHITE_ON_BLACK << 8;

		if ( ch == 0x08 ){
			if ( cur_x > 0 ){
				cur_x--;
			}

			where = textpointer + cur_y*_screen_param::MAX_COLUMNS + cur_x;
			*where = attribute_byte | 0x20;
		}

		if ( ch == 0x09 ){
			cur_x = (cur_x + 8) & ~(8-1);
		}

		if ( ch == '\r' ){
			cur_x = 0;
		}

		if ( ch == '\n' ){
			cur_y++;
			cur_x = 0;
		}

		if ( ch >= ' ' ){
			where = textpointer + cur_y*_screen_param::MAX_COLUMNS + cur_x;
			*where = attribute_byte | ch;
			cur_x++;
		}

		if ( cur_x >= _screen_param::MAX_COLUMNS ){
			cur_x = 0;
			cur_y++;
		}

		scroll();
		move_cursor();

	}

public:

	void print(const uint8_t *str) {
		int i;
		for(i=0; str[i]!='\0'; i++){
			printchar(str[i]);
		}
	}

	

	void init_video() {
		
		textpointer = reinterpret_cast<uint16_t *>(_screen_param::VIDEO_MEMORY);
		
		cls();	
	}

};

#endif
