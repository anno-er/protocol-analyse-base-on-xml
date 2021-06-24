//#include<iostream>
//#include<winsock.h>
//#pragma comment(lib,"ws2_32.lib")
//using namespace std;
//void initialization();
//void S7_response_to_request(u_char* recvmessage,u_char* sendmessage);
////定义内存空间
//int Q[100] = { 0 };
//int M[100] = { 0 };
//
//int main() {
//
//
//	//为内存空间赋值
//	for (int i = 0; i < 100; i++)
//	{
//		Q[i] = i * 2;
//		M[i] = i * 3;
//	}
//	//定义长度变量
//	int send_len = 0;
//	int recv_len = 0;
//	int len = 0;
//	//定义发送缓冲区和接受缓冲区
//	char send_buf[100];
//	char recv_buf[100];
//	//定义服务端套接字，接受请求套接字
//	SOCKET s_server;
//	SOCKET s_accept;
//	//服务端地址客户端地址
//	SOCKADDR_IN server_addr;
//	SOCKADDR_IN accept_addr;
//	initialization();
//	//填充服务端信息
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	server_addr.sin_port = htons(5010);
//	//创建套接字
//	s_server = socket(AF_INET, SOCK_STREAM, 0);
//	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
//		cout << "套接字绑定失败！" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "套接字绑定成功！" << endl;
//	}
//	//设置套接字为监听状态
//	if (listen(s_server, SOMAXCONN) < 0) {
//		cout << "设置监听状态失败！" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "设置监听状态成功！" << endl;
//	}
//	cout << "服务端正在监听连接，请稍候...." << endl;
//	//接受连接请求
//	len = sizeof(SOCKADDR);
//	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
//	if (s_accept == SOCKET_ERROR) {
//		cout << "连接失败！" << endl;
//		WSACleanup();
//		return 0;
//	}
//	cout << "连接建立，准备接受数据" << endl;
//	//接收数据
//	while (1) {
//		recv_len = recv(s_accept, recv_buf, 100, 0);
//		if (recv_len < 0) {
//			cout << "接受失败！" << endl;
//			break;
//		}
//		else {
//			cout<<"Receive message from "<< inet_ntoa(accept_addr.sin_addr)<<"content is:\n";
//			for (int i = 0; i < recv_len; i++) {
//				printf("0x%.2x ", (u_char)recv_buf[i]);
//			}
//			printf("\n");
//		}
//		//cout << "请输入回复信息:";
//		//cin >> send_buf;
//		/*************************************/
//		S7_response_to_request((u_char*)recv_buf, (u_char*)send_buf);
//		/////////
//		send_len = send(s_accept, send_buf, 100, 0);
//		if (send_len < 0) {
//			cout << "发送失败！" << endl;
//			break;
//		}
//		//(20000);
//	}
//	//关闭套接字
//	closesocket(s_server);
//	closesocket(s_accept);
//	//释放DLL资源
//	WSACleanup();
//	return 0;
//}
//void initialization() {
//	//初始化套接字库
//	WORD w_req = MAKEWORD(2, 2);//版本号
//	WSADATA wsadata;
//	int err;
//	err = WSAStartup(w_req, &wsadata);
//	if (err != 0) {
//		cout << "初始化套接字库失败！" << endl;
//	}
//	else {
//		cout << "初始化套接字库成功！" << endl;
//	}
//	//检测版本号
//	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
//		cout << "套接字库版本号不符！" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "套接字库版本正确！" << endl;
//	}
//	//填充服务端地址信息
//}
//
//void S7_response_to_request(u_char* recv_buf, u_char* send_buf) {
//	//header
//	send_buf[0] = 0x32;
//	send_buf[1] = 0x03;
//	send_buf[2] = 0x00;
//	send_buf[3] = 0x00;
//	send_buf[4] = 0x00;
//	send_buf[5] = 0x00;
//
//	send_buf[6] = 0x00;//parameter长度
//	send_buf[7] = 0x02;
//
//	send_buf[10] = 0x00; 	//error码
//	send_buf[11] = 0x00;
//
//	//parameter
//	send_buf[12] = recv_buf[10]; //功能码与事件计数
//	send_buf[13] = recv_buf[11];
//
//	//data
//	send_buf[14] = 0xff;
//	if (send_buf[12] == 0x04) {
//		send_buf[15] = 0x04;
//		send_buf[16] = 0x00;
//		send_buf[17] = 0x16;
//		send_buf[18] = 0x00;
//		u_char Area = recv_buf[20];
//		u_char a = recv_buf[23];
//		if (Area == 0x82) {
//			send_buf[19] = Q[a];
//		}
//		else if (Area == 0x83) {
//			send_buf[19] = M[a];
//		}
//
//		send_buf[8] = 0x00; //data长度
//		send_buf[9] = 0x06;
//	}
//	else if (send_buf[12] == 0x05) {
//		send_buf[8] = 0x00; //data长度
//		send_buf[9] = 0x01;
//
//		u_char Area = recv_buf[20];
//		u_char a = recv_buf[23];
//		if (Area == 0x82) { 
//			Q[a] = recv_buf[29];
//		}
//		else if (Area == 0x83) {
//			M[a] = recv_buf[29];
//		}
//	}
//}


/**********************************************  Fins  **********************************************************************/
#include<WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include<iostream>
using namespace std;
int DM[100] = { 0 };
int CIO[100] = { 0 };
#pragma comment(lib, "Ws2_32.lib")
void Fins_response_to_request(u_char* recv_buf, u_char* send_buf) {
	//header
	send_buf[0] = 0xc0;
	send_buf[1] = 0x00;
	send_buf[2] = 0x07;
	send_buf[3] = 0x00;

	send_buf[4] = recv_buf[7];
	send_buf[5] = 0x00;
	send_buf[6] = 0x00;

	send_buf[7] = recv_buf[4];
	send_buf[8] = 0x00;

	send_buf[9] = recv_buf[9];//sid标识


	send_buf[10] = recv_buf[10]; 	//func_code
	send_buf[11] = recv_buf[11];

	send_buf[12] = 0x00;   //结束码
	send_buf[13] = 0x00;

	if (recv_buf[11] == 0x01) {
		send_buf[14] = 0x00;

		u_char Area = recv_buf[12];
		u_char a = recv_buf[14];
		if (Area == 0x82) {
			send_buf[15] = DM[a];
		}
		else if (recv_buf[12] == 0x30) {
			send_buf[15] = CIO[a];
		}
		else {}
	}
	else if (recv_buf[11] == 0x02) {
		u_char Area = recv_buf[12];
		u_char a = recv_buf[14];
		if (Area == 0x82) {
			DM[a] = recv_buf[19];
		}
		else if (recv_buf[12] == 0x30) {
			CIO[a] = recv_buf[19];
		}
		else {}
	}
	else {
	}
}
int  main()
{
	u_char send_buf[100] = { 0 };
	u_char recv_buf[100] = { 0 };
	for (int i = 0; i < 100; i++)
	{
		DM[i] = i * 2;
		CIO[i] = i * 3;
	}
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return false;
	}

	//UDP 服务端
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s != SOCKET_ERROR) {
		cout << "UDP_FINS服务器建立成功" << endl;
	}
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9600);
	int result = bind(s, (sockaddr*)&addr, sizeof(addr));
	if (result == 0) {
		cout << "客户端绑定成功,正在等待接受：" << endl;
	}

	SOCKADDR_IN addr2;
	INT addrSize2 = sizeof(addr2);
	//char buff[256] = { 0 };
	//接受客户端数据

	int nRecv = recvfrom(s, (char*)recv_buf, sizeof(recv_buf), 0, (sockaddr*)&addr2, &addrSize2);

	int Port2 = ntohs(addr2.sin_port);
	char* ip = inet_ntoa(addr2.sin_addr);
	cout << "Receive some data from: " << ip << ":" << Port2 << endl;
	cout<<recv_buf<<endl;

	
	int ret = connect(s, (sockaddr*)&addr2, addrSize2);
	//printf("connect:   %d  \n", ret);
	if (ret == 0)
	{
		int ret2 = send(s, "Success", 8, 0);
		printf("\nConnect Success\n");
	}
	else {
		int ret2 = send(s, "Failed", 7, 0);
		printf("\nConnect Failed\n");
	}

	while (1) {
		//memset(recv_buf, 0, 100);
		nRecv=recv(s, (char*)recv_buf, sizeof(recv_buf), 0);
		cout << "Receive some data from: " << ip << ":" << Port2 << endl;
		for (int i = 0; i < nRecv; i++) {
			printf("0x%.2x ", (u_char)recv_buf[i]);
		}
		printf("\n");
		Fins_response_to_request(recv_buf, send_buf);
		send(s, (char*)send_buf, sizeof(recv_buf), 0);
	}
	return 0;
}

