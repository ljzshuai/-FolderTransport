#include "ClientSocket.h"
class RecvSocket
{
public:
	vector<boost::filesystem::path>		_path;		//	��Ҫ���͵��ļ�
	vector<shared_ptr<ClientSocket>>    _client;	//	�Ѿ������ϵĿͻ�

	SOCKET								_recv_sock;
	int									_path_num; //	�跢��Ŀ¼ǰ��·������

	struct sockaddr_in					_cli_addr; //	����accept��֪������

	RecvSocket();
	int RecvSocket::init(boost::filesystem::path st_path);
	int listen_m(const char *,const int & );
	SOCKET accept_m();
	void clean();
};
