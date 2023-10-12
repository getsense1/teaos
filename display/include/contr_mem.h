#ifndef __contr_mem__
#define __contr_mem__


#include "screen.h"



class contr_mem{

private:	
	uint8_t	_tmp0; //C++ check

public:
	contr_mem() : _tmp0(0) {}		
	

public:
	bool memcpy(uint8_t *dest, const uint8_t *src, int32_t count){
		/* code to copy 'count' bytes of data from 'src' to
		*  'dest' */

		for(int32_t i=0; i<count; i++)
			dest[i] = src[i];
			
			
		return true;
	}

	bool memcpy(uint16_t *dest, const uint16_t *src, int32_t count){
		/* code to copy 'count' bytes of data from 'src' to
		*  'dest' */

		for(int32_t i=0; i<count; i++)
			dest[i] = src[i];
			
			
		return true;
	}

	bool memset(uint8_t *dest, uint8_t val, int32_t count){
		/* code here to set 'count' bytes in 'dest' to 'val'.
		*  return 'dest' */
		
		for(int32_t i=0; i<count; i++)
			dest[i] = val;
			
		return true;
	}

	bool memset(uint16_t *dest, uint16_t val, int32_t count){
		/* Same as above, but this time, we're working with a 16-bit
		*  'val' and dest pointer. Your code can be an exact copy of
		*  the above, provided that your local variables if any, are
		*  unsigned short */

		for(int32_t i=0; i<count; i++)
			dest[i] = val;
		
		return true;
	}
	


	
	
};	

#endif
