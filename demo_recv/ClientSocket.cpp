#include "ClientSocket.h"
ClientSocket::ClientSocket(const vector<boost::filesystem::path>& data):_path(data),_client(invalid_socket)
														,_file(NULL),_file_pkt_sz(0)
														,_file_sz(0),_pkt_send_sz(0)
														,final_(1),_file_num(0)
														,_path_num(0)
{	
}

int ClientSocket::send_m()
{
	if(_pkt_send_sz >= _pkt._header._mlen)//�ϸ����Ƿ���
	{	
		if(final_==0){
			closesocket(_client);
			_client = invalid_socket;
			return 0;
		}
		_pkt_send_sz=0;
		final_ = read_m();
	}
	 int tmp = send(_client,(char*)&_pkt+_pkt_send_sz,this->_pkt._header._mlen-_pkt_send_sz,0);
	 
	_pkt_send_sz += tmp;

	return tmp;
}

int ClientSocket::read_m()	//װ��һ���°�
{
	if(!_file && _file_num < 0)  //�����ļ��������
	{
		_pkt._header._mlen = sizeof(_pkt._header);
		_pkt._header._type = 2;
		//cout<<"���"<<endl;
		return 0;
	}

	if(_file)	//��һ���ļ�û����
	{
		_pkt._header._type = 1;
		_pkt._header._mlen = fread(_pkt._mdata,sizeof(char),sizeof(_pkt._mdata),_file);
		_file_pkt_sz += _pkt._header._mlen;
		_pkt._header._mlen += sizeof(_pkt._header);

		if(_file_pkt_sz >= _file_sz)
		{
			--_file_num;
			fclose(_file);
			_file = NULL;
		}
		//cout<<"����"<<endl;
		return 1;
	}
	//���һ�����ļ�//
	_pkt._header._type = 0;
	fopen_s(&_file,_path[_file_num].string().c_str(),"rb");
	
	_pkt.fileinfo._path_num = this->_path_num;
	sprintf_s(_pkt.fileinfo._fname,sizeof(_pkt.fileinfo._fname),_path[_file_num].string().c_str());

	_file_sz = boost::filesystem::file_size(_path[_file_num]);


	_pkt._header._mlen=sizeof(_pkt._header) + sizeof(_pkt.fileinfo._fname);
	//cout<<"��ͷ"<<endl;
	return 1;
}
