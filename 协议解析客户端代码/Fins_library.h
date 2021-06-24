#pragma once
#ifndef FINS_LIBRARY_H_
#define FINS_LIBRARY_H_


#include<sys/types.h>
#include<winsock.h>
#include <stdint.h>
#include <stdlib.h>
#include"struct.h"
#pragma comment(lib, "ws2_32.lib")	  //socket通信相关

void Fins_xml_Create();  //Fins xml文件创建函数
int32_t load_Fins_xml_profile(const char* path, command_info& cpm_i);  //Fins xml文件加载函数

void Command_build_Fins(command_info com_i, u_char* message);
void Command_prase_Fins(u_char* message);
void Fins_message_rebulid(u_char* sendmessage);//命令重构
uint16_t Sock_Communication_Fins(command_info com_i, u_char* sendmessage, u_char* recvmessage);

//uint16_t Sock_init_Fins(SOCKET& sClient, command_info com_i);
//uint16_t SEND_MSG_Fins(SOCKET sClient, u_char* message,sockaddr_in server_addr);
//uint16_t RECV_MSG_Fins(SOCKET sClient, u_char* message,sockaddr_in server_addr);




#endif // !FINS_LIBRARY_H_


