#include "Client.h"

int Client::case0()  //判断有没有完整的包头
{
	int time = _file_pkt._buf_used - _file_pkt._head_sz;
	for(int i=0;i!=time;++i)
	{
		if(strncmp(_file_pkt._buf+i,(char *)&_file_pkt._head_id,sizeof(_file_pkt._head_id))==0){
			memmove(_file_pkt._buf,_file_pkt._buf+i,sizeof(file_packet_t)-i);
			_file_pkt._buf_used -= i;
			_pkt = (file_packet_t*) _file_pkt._buf;
			_file_pkt._where = 1;
			return 1;
		}
	}
	memmove(_file_pkt._buf,_file_pkt._buf+time,sizeof(file_packet_t)-time);
	return 0;
}

int Client::case1(const char * dir_path) //处理包
{
	switch(_pkt->_header._type)
	{
	case 0:{
		if (_file)
			fclose(_file);

		boost::filesystem::path temp_path(_pkt->fileinfo._fname);
		string temp_str;
		int temp_num(0);

		for (boost::filesystem::path::iterator it = temp_path.begin(); it != temp_path.end(); ++it)
		{
			if (temp_num < _pkt->fileinfo._path_num){
				++temp_num;
				continue;
			}
			temp_str += (*it).string() + "\\";
		}
		temp_str.erase(temp_str.end() - 1);

		temp_str = string(dir_path) + "\\" + temp_str;

		boost::filesystem::create_directories(boost::filesystem::path(temp_str.c_str()).parent_path());

		fopen_s(&_file,temp_str.c_str(), "wb+");
		_file_pkt._buf_used -= _pkt->_header._mlen;
		memmove(_file_pkt._buf, _file_pkt._buf + _pkt->_header._mlen, sizeof(file_packet_t) - _pkt->_header._mlen);
	
		cout << "包头" << endl;
		return 0;
		break;
	}
	case 1:
		fwrite(_pkt->_mdata,sizeof(char),_pkt->_header._mlen-sizeof(_pkt->_header),_file);
		_file_pkt._buf_used -= _pkt->_header._mlen;
		memmove(_file_pkt._buf,_file_pkt._buf+_pkt->_header._mlen,sizeof(file_packet_t)-_pkt->_header._mlen);
		cout<<"数据"<<endl;
		return 0;
		break;
	case 2:
		fclose(_file);
		closesocket(_client);
		_file=NULL;
		cout<<"下载完成"<<endl;
		return 1;
		break;
	default:
		break;

	}
	return 0;
}

int Client::recv_m()
{
	return recv(_client,_file_pkt._buf+_file_pkt._buf_used,sizeof(file_packet_t)-_file_pkt._buf_used,0);
}

int Client::read_m(const char * dir_path)  
{
	unsigned temp =recv_m();
	cout<<temp<<endl;
	_file_pkt._buf_used += temp;

	switch (_file_pkt._where)
	{
	case 0:
		if(_file_pkt._buf_used >= _file_pkt._head_sz)
			case0();
		else{
			_file_pkt._where = 0;
			break;
		}
		if(_file_pkt._where!=1)
			break;
	case 1:
		if(_file_pkt._buf_used >= _pkt->_header._mlen)
			if(case1(dir_path))
				return 1;
			else
				break;
	default:
		break;
	}
	return 0;
}

Client::Client():_client(invalid_socket),_pkt(NULL),_file(NULL)
{

}

int Client::connect_m(const  char* addr,const int & port)
{
	WSADATA wsadata;
	struct sockaddr_in clin;

	if(WSAStartup(MAKEWORD(2,2),&wsadata)!=0)
	{
		cout<<"load winsock fail"<<endl;
		return -1;
	}

	clin.sin_family=AF_INET;
	clin.sin_port=htons(port);
	clin.sin_addr.s_addr=inet_addr(addr);

	_client=socket(AF_INET,SOCK_STREAM,0);
	if(_client==INVALID_SOCKET)
	{
		cout<<"socket() fail "<<WSAGetLastError()<<endl;
		return -1;
	}

	if((connect(_client,(struct sockaddr* )&clin,sizeof(clin)))==INVALID_SOCKET)
	{
		cout<<"connect fail"<<endl;
		return -1;
	}
	return 1;
}