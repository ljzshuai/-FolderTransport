#include "file.h"
file_packet_t::file_packet_s()
{
	
	_header._id=999999;
	_header._type=3;
	_header._mlen=0;
	memset(_mdata,0,sizeof(_mdata));	
	
}

recv_pkt::recv_pkt(): _buf_used(0),_head_id(999999),_where(0)
{
	_buf=(char*) new file_packet_t;
	_buf_max=sizeof(file_packet_t);
	_head_sz=sizeof(file_packet_t::head);
}