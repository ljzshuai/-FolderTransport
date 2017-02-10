#include<iostream>
#include<memory>
#include<Windows.h>
#include<WinSock.h>
#include<stdint.h>
#include<stdint.h>
#include<string>
#include<string.h>
#include<vector>
#include<direct.h>
#include<io.h>
#include<direct.h>
#include<memory>
#include<stdlib.h>
#include<time.h>
#include<sys/types.h>
#include<fstream>
#include<sys/stat.h>
#include<assert.h>
#include<stdio.h>
#include<boost/filesystem.hpp>

#define invalid_socket		(unsigned)(~0)

//using namespace std;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::cout;
using std::cin;
using std::endl;

#define PACKET_MLEN			8388608
typedef long long			llong;
typedef boost::filesystem::recursive_directory_iterator boost_rd_iterator;

#pragma comment(lib,"ws2_32.lib")


/*
	数据结构--包
	_header 表明这个包的类型和大小
	union   存放文件名或者文件数据
*/
#pragma  pack(1)
typedef struct file_packet_s
{
	struct head
	{
		int				_id;	// 验证
		int				_type;	// =0 文件名; =1 文件数据; =2 所有文件发送完毕
		unsigned		_mlen;	// 包的大小
	}_header;
	union 
	{
		struct 
		{
			int		_path_num; //路径长度(供boost使用)
			char	_fname[MAX_PATH];
		}fileinfo;
		char	_mdata[PACKET_MLEN];
	};
	file_packet_s();
}file_packet_t;


struct recv_pkt{	
	unsigned	_buf_max;		//缓冲区大小
	char*		_buf;			//接收包
	unsigned	_buf_used;		//buf已经使用的大小
	unsigned	_head_id;		//验证
	unsigned	_where;			//进行第几步
	unsigned	_head_sz;		//包头大小
	recv_pkt();
};

