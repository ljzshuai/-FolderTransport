#include "RecvSocket.h"

void RecvSocket::clean()	//	清除断开的连接
{
	std::vector<shared_ptr<ClientSocket>>::iterator it;
	for (it = _client.begin(); it != _client.end();)
	{
		if ((*it)->_client == invalid_socket)
		{
			it = _client.erase(it);
		}
		else
		{
			it++;
		}
	}
}
SOCKET RecvSocket::accept_m()
{
	int abc=sizeof(_cli_addr);
	return accept(this->_recv_sock,(struct sockaddr*)&this->_cli_addr,&abc);
	

}
int RecvSocket::listen_m(const char * addr,const int & port) 
{

	struct sockaddr_in  ser;
	WSADATA				_wsadata;

	if(WSAStartup(MAKEWORD(2,2),&_wsadata)!=0)
	{
		cout<<"load winsock fail"<<endl;
		return -1;
	}

	ser.sin_family=AF_INET;
	ser.sin_port=htons(port);
	ser.sin_addr.s_addr=inet_addr(addr);

	_recv_sock=socket(AF_INET,SOCK_STREAM,0);
	if(_recv_sock==INVALID_SOCKET)
	{
		cout<<"socket() fail "<<WSAGetLastError()<<endl;
		return -1;
	}

	if((bind(_recv_sock,(LPSOCKADDR)&ser,sizeof(ser))) == SOCKET_ERROR)
	{
		cout<<"bind fail"<<endl;
		return -1;
	}

	if(listen(_recv_sock,10)==SOCKET_ERROR)
	{
		cout<<"listen() fail"<<WSAGetLastError()<<endl;
		return -1;
	}
	return 1;
}

RecvSocket::RecvSocket() :_recv_sock(invalid_socket), _path_num(0)
{

}


int RecvSocket::init(boost::filesystem::path st_path) //装载需要发送的文件路径
{
	

	boost_rd_iterator end;
	int path_num(0);

	for (boost::filesystem::path::iterator it = st_path.begin(); it != st_path.end(); ++it)
		++path_num;
	this->_path_num = path_num;

	for (boost_rd_iterator pos(st_path); pos != end; pos++)
	{
		if (boost::filesystem::is_regular_file(*pos))
		_path.push_back(*pos);
	}
	if (_path.empty())
		return 0;

	return 1;
}
