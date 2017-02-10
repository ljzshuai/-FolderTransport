#include "Client.h"
int main()
{
	Client sclient;
	sclient.connect_m("127.0.0.1",9001);
	fd_set sock_rd;

	int flag=0;
	while(!flag)
	{
		FD_ZERO(&sock_rd);
		FD_SET(sclient._client,&sock_rd);

		select(0, &sock_rd,NULL, NULL, NULL);
		flag = sclient.read_m("E:\\新建文件夹\\a");

	}
	system("pause");
}