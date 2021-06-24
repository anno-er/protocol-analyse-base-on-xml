#pragma once
#ifndef STRUCT_H_
#define STRUCT_H_

#include <stdint.h>

typedef struct {
	char* protocol_name;
	char* protocol_id;
	char* protocol_Func_code;
	char* protocol_Area;
	char* protocol_Areastart;
	char* protocol_len;
	char* protocol_data;
} XML_info;

typedef struct {
	XML_info xml_i;
	unsigned short port;
	char* IP;
} command_info;





#endif //!STRUCT_H_


