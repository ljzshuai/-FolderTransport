#include "file.h"
class Client
{
public:
	recv_pkt   _file_pkt;
	SOCKET		_client;
	file_packet_t * _pkt;
	FILE *			_file;

	Client();
	int connect_m(const char *,const int &);
	int read_m(const char * dir_path);
	int recv_m();
	int case0();
	int case1(const char * dir_path);
	void case2();
};
