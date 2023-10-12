#ifndef __low_level__
#define __low_level__

typedef struct _contr_regs{
	
	uint8_t port_byte_get(uint16_t port){
		// A handy C wrapper function that reads a byte from the specified port
		// "=a" ( result ) means : put AL register in variable RESULT when finished
		// "d" ( port ) means : load EDX with port
		uint8_t result;
		__asm__("in %%dx, %%al" : "=a" (result) : "d" (port));
		return result;
	}

	void port_byte_put(uint16_t port, uint8_t data){
		// "a" ( data ) means : load EAX with data
		// "d" ( port ) means : load EDX with port
		__asm__("out %%al, %%dx" : :"a" (data), "d" (port));
	}

	uint16_t port_word_get(uint16_t port){
		uint16_t result;
		__asm__("in %%dx, %%ax" : "=a" (result) : "d" (port));
		return result;
	}

	void port_word_put(uint16_t port, uint16_t data){
		__asm__("out %%ax, %%dx" : :"a" (data), "d" (port));
	}

};


#endif