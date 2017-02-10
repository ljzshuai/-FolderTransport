#include "file.h"
class ClientSocket
{
public:

	SOCKET		    _client;
	file_packet_t	_pkt;				//Ҫ���͵İ�
	unsigned		_pkt_send_sz;		//��ǰ���Ѿ����͵Ĵ�С

	FILE *		    _file;				//���ڴ�����ļ�
	unsigned		_file_sz;			//���ڴ�����ļ���С
	unsigned		_file_pkt_sz;		//��ǰ�ļ��Ѿ�������Ĵ�С

	int			    _file_num;			//���跢�͵��ļ���
	int				final_;				//�Ƿ������ļ�ȫ������
	
	int				_path_num;			//�跢��Ŀ¼ǰ��·������

	const vector<boost::filesystem::path> &_path;		//��Ҫ���͵��ļ���·��

	int read_m();			//װ��һ���°�
	int send_m();			

	ClientSocket(const vector<boost::filesystem::path>&);
private:
	ClientSocket();
};


