//#include<iostream>
//#include<winsock.h>
//#pragma comment(lib,"ws2_32.lib")
//using namespace std;
//void initialization();
//void S7_response_to_request(u_char* recvmessage,u_char* sendmessage);
////�����ڴ�ռ�
//int Q[100] = { 0 };
//int M[100] = { 0 };
//
//int main() {
//
//
//	//Ϊ�ڴ�ռ丳ֵ
//	for (int i = 0; i < 100; i++)
//	{
//		Q[i] = i * 2;
//		M[i] = i * 3;
//	}
//	//���峤�ȱ���
//	int send_len = 0;
//	int recv_len = 0;
//	int len = 0;
//	//���巢�ͻ������ͽ��ܻ�����
//	char send_buf[100];
//	char recv_buf[100];
//	//���������׽��֣����������׽���
//	SOCKET s_server;
//	SOCKET s_accept;
//	//����˵�ַ�ͻ��˵�ַ
//	SOCKADDR_IN server_addr;
//	SOCKADDR_IN accept_addr;
//	initialization();
//	//���������Ϣ
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
//	server_addr.sin_port = htons(5010);
//	//�����׽���
//	s_server = socket(AF_INET, SOCK_STREAM, 0);
//	if (bind(s_server, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
//		cout << "�׽��ְ�ʧ�ܣ�" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "�׽��ְ󶨳ɹ���" << endl;
//	}
//	//�����׽���Ϊ����״̬
//	if (listen(s_server, SOMAXCONN) < 0) {
//		cout << "���ü���״̬ʧ�ܣ�" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "���ü���״̬�ɹ���" << endl;
//	}
//	cout << "��������ڼ������ӣ����Ժ�...." << endl;
//	//������������
//	len = sizeof(SOCKADDR);
//	s_accept = accept(s_server, (SOCKADDR*)&accept_addr, &len);
//	if (s_accept == SOCKET_ERROR) {
//		cout << "����ʧ�ܣ�" << endl;
//		WSACleanup();
//		return 0;
//	}
//	cout << "���ӽ�����׼����������" << endl;
//	//��������
//	while (1) {
//		recv_len = recv(s_accept, recv_buf, 100, 0);
//		if (recv_len < 0) {
//			cout << "����ʧ�ܣ�" << endl;
//			break;
//		}
//		else {
//			cout<<"Receive message from "<< inet_ntoa(accept_addr.sin_addr)<<"content is:\n";
//			for (int i = 0; i < recv_len; i++) {
//				printf("0x%.2x ", (u_char)recv_buf[i]);
//			}
//			printf("\n");
//		}
//		//cout << "������ظ���Ϣ:";
//		//cin >> send_buf;
//		/*************************************/
//		S7_response_to_request((u_char*)recv_buf, (u_char*)send_buf);
//		/////////
//		send_len = send(s_accept, send_buf, 100, 0);
//		if (send_len < 0) {
//			cout << "����ʧ�ܣ�" << endl;
//			break;
//		}
//		//(20000);
//	}
//	//�ر��׽���
//	closesocket(s_server);
//	closesocket(s_accept);
//	//�ͷ�DLL��Դ
//	WSACleanup();
//	return 0;
//}
//void initialization() {
//	//��ʼ���׽��ֿ�
//	WORD w_req = MAKEWORD(2, 2);//�汾��
//	WSADATA wsadata;
//	int err;
//	err = WSAStartup(w_req, &wsadata);
//	if (err != 0) {
//		cout << "��ʼ���׽��ֿ�ʧ�ܣ�" << endl;
//	}
//	else {
//		cout << "��ʼ���׽��ֿ�ɹ���" << endl;
//	}
//	//���汾��
//	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
//		cout << "�׽��ֿ�汾�Ų�����" << endl;
//		WSACleanup();
//	}
//	else {
//		cout << "�׽��ֿ�汾��ȷ��" << endl;
//	}
//	//������˵�ַ��Ϣ
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
//	send_buf[6] = 0x00;//parameter����
//	send_buf[7] = 0x02;
//
//	send_buf[10] = 0x00; 	//error��
//	send_buf[11] = 0x00;
//
//	//parameter
//	send_buf[12] = recv_buf[10]; //���������¼�����
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
//		send_buf[8] = 0x00; //data����
//		send_buf[9] = 0x06;
//	}
//	else if (send_buf[12] == 0x05) {
//		send_buf[8] = 0x00; //data����
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

	send_buf[9] = recv_buf[9];//sid��ʶ


	send_buf[10] = recv_buf[10]; 	//func_code
	send_buf[11] = recv_buf[11];

	send_buf[12] = 0x00;   //������
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

	//UDP �����
	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s != SOCKET_ERROR) {
		cout << "UDP_FINS�����������ɹ�" << endl;
	}
	SOCKADDR_IN addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addr.sin_family = AF_INET;
	addr.sin_port = htons(9600);
	int result = bind(s, (sockaddr*)&addr, sizeof(addr));
	if (result == 0) {
		cout << "�ͻ��˰󶨳ɹ�,���ڵȴ����ܣ�" << endl;
	}

	SOCKADDR_IN addr2;
	INT addrSize2 = sizeof(addr2);
	//char buff[256] = { 0 };
	//���ܿͻ�������

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

