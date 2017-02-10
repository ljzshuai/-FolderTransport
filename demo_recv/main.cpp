#include "RecvSocket.h"

int main()
{
	shared_ptr<RecvSocket>recv= make_shared<RecvSocket>();

	if(recv->init("E:\\OpenDDS-DDS-3.8\\bin")==0)
		return -1;

	recv->_path;

	if(recv->listen_m("127.0.0.1",9001)==-1)
		return -1;

	fd_set sock_rd;
	fd_set sock_wd;

	for(;;)
	{
		int num(0);

		FD_ZERO(&sock_wd);
		FD_ZERO(&sock_rd);

		FD_SET(recv->_recv_sock,&sock_rd);
		for each(auto i in recv->_client)
		{
			FD_SET(i->_client,&sock_wd);
		}

		num = select(0, &sock_rd, &sock_wd, NULL, NULL);

		for(int i=0;i!=num;++i)
		{ 
			if(FD_ISSET(recv->_recv_sock,&sock_rd))
			{
				auto temp = make_shared<ClientSocket>(recv->_path);
				temp->_client=recv->accept_m();
				temp->_file_num=recv->_path.size();
				temp->_file_num=recv->_path.size()-1;
				temp->_path_num = recv->_path_num;
				recv->_client.push_back(temp);
				break;
			}


			for each (auto j in recv->_client)
			{
				if(FD_ISSET(j->_client,&sock_wd))
				{
					j->send_m();
				}
			}

		}
		recv->clean();
	}


}
