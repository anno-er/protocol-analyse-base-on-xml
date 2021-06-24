#pragma once
#ifndef FUNC_LOAD_H_
#define FUNC_LOAD_H_
#include"struct.h"
#include<winsock.h>

//定义函数指针
//extern void (*xml_Create)();
//extern int32_t(*load_xml_profile)(const char* path, command_info& com_i);
//extern void (*Command_build)(command_info com_i, u_char* message);
//extern uint16_t(*Sock_Communication)(command_info com_i, u_char* sendmessage, u_char* recvmessage);
//extern void (*Command_prase)(u_char* message);

//void Func_select(char* message);
void Message_print(u_char* message, int len);
int message_len(u_char* a);

#endif // ! FUNC_LOAD_H_

