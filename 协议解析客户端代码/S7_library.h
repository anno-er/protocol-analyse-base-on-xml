#pragma once
#ifndef S7_LIBRARY_H_
#define S7_LIBRARY_H_


#include<sys/types.h>
#include<winsock.h>
#include <stdint.h>
#include <stdlib.h>
#include"struct.h"
#pragma comment(lib, "ws2_32.lib")	  //socket通信相关


void Command_build_S7(command_info com_i, u_char* message);
void Command_prase_S7(u_char* message);
//uint16_t Sock_init_S7(SOCKET& server,command_info com_i);
//uint16_t SEND_MSG_S7(SOCKET sClient, u_char* message);
//uint16_t RECV_MSG_S7(SOCKET sClient, u_char* message);

int32_t load_S7_xml_profile(const char* path, command_info& cpm_i);  //S7xml文件加载甘薯
void S7_xml_Create();  //S7xml文件创建函数
uint16_t Sock_Communication_S7(command_info com_i, u_char* sendmessage, u_char* recvmessage);
void S7_message_rebulid(u_char* sendmessage);//命令重构
#endif // !S7_LIBRARY_H_


