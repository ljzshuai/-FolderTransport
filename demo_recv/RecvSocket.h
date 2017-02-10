#include "ClientSocket.h"
class RecvSocket
{
public:
	vector<boost::filesystem::path>		_path;		//	需要发送的文件
	vector<shared_ptr<ClientSocket>>    _client;	//	已经连接上的客户

	SOCKET								_recv_sock;
	int									_path_num; //	需发送目录前的路径长度

	struct sockaddr_in					_cli_addr; //	用来accept不知道放哪

	RecvSocket();
	int RecvSocket::init(boost::filesystem::path st_path);
	int listen_m(const char *,const int & );
	SOCKET accept_m();
	void clean();
};
