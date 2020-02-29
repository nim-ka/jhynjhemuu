#define Swap4Bytes(val) \
	( (((val) >> 24) & 0x000000FF) | (((val) >>  8) & 0x0000FF00) | \
	(((val) <<  8) & 0x00FF0000) | (((val) << 24) & 0xFF000000) )
