#include"S7_library.h"
#include"Fins_library.h"
#include"struct.h"
#include"tinyxml.h"
#include<iostream>
#include<string.h>
#include"Func_load.h"

//int char_len(u_char* a) {
//	int i = 0;
//	while (a[i] != 204) {
//		i++;
//	}
//	return i;
//}

using namespace std;
int main() {
	
	u_char sendmessage[100];
	u_char recvmessage[100];
	command_info com_i = { 0 };
	char Protocolname[20] = { 0 };
	cout << "Please enter Protocol name:(S7_TCP or Fins): " ;
	cin >> Protocolname;
	
	//函数的选择
	//void (*xml_Create)() = S7_xml_Create;
	//int32_t(*load_xml_profile)(const char* path, command_info & com_i) = load_S7_xml_profile;
	//void (*Command_build)(command_info com_i, u_char * message) = Command_build_S7;
	//uint16_t(*Sock_Communication)(command_info com_i, u_char * sendmessage, u_char * recvmessage) = Sock_Communication_S7;
	//void (*Command_prase)(u_char * message) = Command_prase_S7;
	if (strcmp(Protocolname, "S7_TCP") == 0) {
		void (*xml_Create)() = S7_xml_Create;
		int32_t(*load_xml_profile)(const char* path, command_info & com_i) = load_S7_xml_profile;
		void (*Command_build)(command_info com_i, u_char * message) = Command_build_S7;
		uint16_t(*Sock_Communication)(command_info com_i, u_char * sendmessage, u_char * recvmessage) = Sock_Communication_S7;
		//void (*Command_prase)(u_char * message) = Command_prase_S7;
		char* xmlname = strcat(Protocolname, ".xml");


		xml_Create();
		load_xml_profile(xmlname, com_i);
		Command_build(com_i, sendmessage);
		int len = message_len(sendmessage);
		Message_print(sendmessage, len);
		Sock_Communication(com_i, sendmessage, recvmessage);
		//Command_prase(recvmessage);
	}
	else if (strcmp(Protocolname, "Fins") == 0) {
		void (*xml_Create)() = Fins_xml_Create;
		int32_t(*load_xml_profile)(const char* path, command_info & com_i) = load_Fins_xml_profile;
		void (*Command_build)(command_info com_i, u_char * message) = Command_build_Fins;
		uint16_t(*Sock_Communication)(command_info com_i, u_char * sendmessage, u_char * recvmessage) = Sock_Communication_Fins;

		char* xmlname = strcat(Protocolname, ".xml");
		xml_Create();
		load_xml_profile(xmlname, com_i);
		Command_build(com_i, sendmessage);
		int len = message_len(sendmessage);
		//Message_print(sendmessage, len);
		Sock_Communication(com_i, sendmessage, recvmessage);
	}
	else {
	}


	//char* xmlname = strcat(Protocolname, ".xml");

	////void (*xml_Create)() = Fins_xml_Create;
	//xml_Create();

	////int32_t(*load_xml_profile)(const char* path, command_info & com_i) = load_Fins_xml_profile;
	//load_xml_profile(xmlname, com_i);


	////void (*command_build)(command_info com_i,u_char* message) = Command_build_Fins;
	//Command_build(com_i, sendmessage);
	//int len = message_len(sendmessage);
	//Message_print(sendmessage, len);
	///************************************测试报文输出*******************************************************/

	////for (int i = 0; i < 20; i++) {
	////	printf("0x%.2x ", sendmessage[i]);
	////}

	////char* a = com_i.IP;
	////printf("%s\n", a);

	///*************************************十六进制高低位****************************************************/
	////int n = 1234;
	////byte a[2] = { 0 };
	////a[0] = n/256;
	////a[1] = n % 256;

	////printf("%.2x", a[0]);
	////printf("%.2x", a[1]);

	///**************************************** socket数据发送与接收 *****************************************/

	////uint16_t(*Sock_Communication)(command_info com_i, u_char * sendmessage, u_char * recvmessage) = Sock_Communication_Fins;
	//Sock_Communication(com_i, sendmessage, recvmessage);

	////void (*Command_prase)(u_char * message) = Command_prase_Fins;
	//Command_prase(recvmessage);

	return 0;
}

