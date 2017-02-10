#include "file.h"
class ClientSocket
{
public:

	SOCKET		    _client;
	file_packet_t	_pkt;				//要发送的包
	unsigned		_pkt_send_sz;		//当前包已经发送的大小

	FILE *		    _file;				//正在打包的文件
	unsigned		_file_sz;			//正在打包的文件大小
	unsigned		_file_pkt_sz;		//当前文件已经被打包的大小

	int			    _file_num;			//还需发送的文件数
	int				final_;				//是否所有文件全部发完
	
	int				_path_num;			//需发送目录前的路径长度

	const vector<boost::filesystem::path> &_path;		//需要发送的文件的路径

	int read_m();			//装订一个新包
	int send_m();			

	ClientSocket(const vector<boost::filesystem::path>&);
private:
	ClientSocket();
};


