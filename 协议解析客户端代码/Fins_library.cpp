#include"S7_library.h"
#include"tinyxml.h"
#include<iostream>
using namespace std;

void Fins_xml_Create() {
	TiXmlDocument* doc = new TiXmlDocument();
	TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc->LinkEndChild(declaration);

	TiXmlElement* ProtocolRoot = new TiXmlElement("Protocol");
	doc->LinkEndChild(ProtocolRoot);

	TiXmlElement* createname = new TiXmlElement("name");
	ProtocolRoot->LinkEndChild(createname);
	TiXmlText* nameText = new TiXmlText("Fins");
	createname->LinkEndChild(nameText);

	TiXmlElement* createID = new TiXmlElement("ID");
	ProtocolRoot->LinkEndChild(createID);
	TiXmlText* IDText = new TiXmlText("2");
	createID->LinkEndChild(IDText);

	TiXmlElement* createFuc = new TiXmlElement("Func");
	ProtocolRoot->LinkEndChild(createFuc);
	TiXmlText* Fuc_code = new TiXmlText("read");
	createFuc->LinkEndChild(Fuc_code);

	TiXmlElement* createArea = new TiXmlElement("Area");
	ProtocolRoot->LinkEndChild(createArea);

	TiXmlElement* createAreaname = new TiXmlElement("Areaname");
	createArea->LinkEndChild(createAreaname);
	TiXmlText* A_n = new TiXmlText("DM");
	createAreaname->LinkEndChild(A_n);

	TiXmlElement* createAreaStart = new TiXmlElement("Areastart");
	createArea->LinkEndChild(createAreaStart);
	TiXmlText* A_s = new TiXmlText("10");
	createAreaStart->LinkEndChild(A_s);

	TiXmlElement* createlength = new TiXmlElement("length");
	createArea->LinkEndChild(createlength);
	TiXmlText* len = new TiXmlText("1");
	createlength->LinkEndChild(len);

	TiXmlElement* createCircle = new TiXmlElement("Cricle");
	ProtocolRoot->LinkEndChild(createCircle);
	TiXmlText* time = new TiXmlText("500ms");
	createCircle->LinkEndChild(time);

	TiXmlElement* createData = new TiXmlElement("Data");
	ProtocolRoot->LinkEndChild(createData);
	TiXmlText* data = new TiXmlText("1");
	createData->LinkEndChild(data);

	TiXmlElement* createCOM = new TiXmlElement("COM");
	ProtocolRoot->LinkEndChild(createCOM);

	TiXmlElement* createCOMIP = new TiXmlElement("COMIP");
	createCOM->LinkEndChild(createCOMIP);
	TiXmlText* IP = new TiXmlText("127.0.0.1");
	createCOMIP->LinkEndChild(IP);

	TiXmlElement* createCOMPORT = new TiXmlElement("COMPORT");
	createCOM->LinkEndChild(createCOMPORT);
	TiXmlText* PORT = new TiXmlText("9600");
	createCOMPORT->LinkEndChild(PORT);
	doc->SaveFile("Fins.xml");
}

int32_t load_Fins_xml_profile(const char* path, command_info& com_i) {
	TiXmlDocument d(path);
	if (d.LoadFile() != true) {
		std::cout << "Load XML_File Failed!" << std::endl;
		return -1;
	}
	//获取根元素
	TiXmlElement* rootElement = d.RootElement();
	//获取name
	TiXmlElement* name = rootElement->FirstChildElement("name");
	com_i.xml_i.protocol_name = new char[strlen(name->GetText())];
	strcpy(com_i.xml_i.protocol_name, name->GetText());

	//获取ID
	TiXmlElement* ID = rootElement->FirstChildElement("ID");
	com_i.xml_i.protocol_id = new char[strlen(ID->GetText())];
	strcpy(com_i.xml_i.protocol_id, ID->GetText());

	//获取功能码
	TiXmlElement* Func_code = rootElement->FirstChildElement("Func");
	com_i.xml_i.protocol_Func_code = new char[strlen(Func_code->GetText())];
	strcpy(com_i.xml_i.protocol_Func_code, Func_code->GetText());

	//获取内存区
	TiXmlElement* Area = rootElement->FirstChildElement("Area");
	TiXmlElement* Areaname = Area->FirstChildElement("Areaname");
	com_i.xml_i.protocol_Area = new char[strlen(Areaname->GetText())];
	strcpy(com_i.xml_i.protocol_Area, Areaname->GetText());

	//获取内存起始位置
	TiXmlElement* Areastart = Area->FirstChildElement("Areastart");
	com_i.xml_i.protocol_Areastart = new char[strlen(Areastart->GetText())];
	strcpy(com_i.xml_i.protocol_Areastart, Areastart->GetText());

	//获取数据操作长度
	TiXmlElement* length = Area->FirstChildElement("length");
	com_i.xml_i.protocol_len = new char[strlen(length->GetText())];
	strcpy(com_i.xml_i.protocol_len, length->GetText());

	int a = atoi(length->GetText());

	//获取数据
	if (strcmp(com_i.xml_i.protocol_Func_code, "write") == 0) {
		TiXmlElement* data = rootElement->FirstChildElement("Data");
		com_i.xml_i.protocol_data = new char[strlen(data->GetText())];
		strcpy(com_i.xml_i.protocol_data, data->GetText());;
	}

	//获取IP
	TiXmlElement* COM = rootElement->FirstChildElement("COM");
	TiXmlElement* COMIP = COM->FirstChildElement("COMIP");
	com_i.IP = new char[strlen(COMIP->GetText())];
	strcpy(com_i.IP, COMIP->GetText());
	//获取端口号
	TiXmlElement* COMPORT = COM->FirstChildElement("COMPORT");
	char* tmp = new char[strlen(COMPORT->GetText())];
	strcpy(tmp, COMPORT->GetText());
	com_i.port = u_short(atoi(tmp));
	return 0;

}  

void Command_build_Fins(command_info com_i, u_char* message) {
	//message-header 10bytes
	message[0] = 0x80;
	message[1] = 0x00;
	message[2] = 0x02;
	message[3] = 0x00;

	message[4] = 0x00;  //目的地IP最后一段，
	message[5] = 0x00;
	message[6] = 0x00;
		
	message[7] = 0x00; //本地网络地址
	message[8] = 0x00;

	message[9] = 0x00; //标识符,自己设定

	message[10] = 0x01;
	//message-parameter
	int len = atoi(com_i.xml_i.protocol_len);
	if (strcmp(com_i.xml_i.protocol_Func_code, "read") == 0) {
		message[11] = 0x01;
	}
	else if (strcmp(com_i.xml_i.protocol_Func_code, "write") == 0) {
		message[11] = 0x02;
	}
	else {}

	if (strcmp(com_i.xml_i.protocol_Area, "DM") == 0) {
		message[12] = 0x82;
	}
	else if (strcmp(com_i.xml_i.protocol_Area, "CIO") == 0) {
		message[12] = 0x30;
	}
	else {
	}

	//起始位置
	message[13] = 0x00;
	int a_s = atoi(com_i.xml_i.protocol_Areastart);
	message[14] = char(a_s);
	message[15] = 0x00; //字节bit位

	//长度
	message[16] = 0x00;
	message[17] = char(len);

	//WriteData
	if (strcmp(com_i.xml_i.protocol_Func_code, "write") == 0) {
		//多个数据的处理
		int data = atoi(com_i.xml_i.protocol_data);
		message[18] = 0x00;
		message[19] = char(data);
	}
	return;
}

void Command_prase_Fins(u_char* message) {
	if (message[11] == 0x01) {
		if (message[12] == 0x00) {
			std::cout << "读取PLC数据成功！数据为： ";
			printf("%d\n", message[15]);
		}
		else {
			std::cout << "读取PLC数据失败！错误码为：" << message[12] << std::endl;
		}
	}
	else if (message[11] == 0x02) {
		if (message[12] == 0x00) {
			std::cout << "PLC数据写入成功！" << std::endl;
		}
		else {
			std::cout << "PLC数据写入失败！错误码为：" << hex << message[12] << std::endl;
		}
	}
}


void fins_sock_initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
		return;
	}
	else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}
	else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息
}

//uint16_t Sock_init_Fins(SOCKET& sClient, command_info com_i) {
//	fins_sock_initialization();
//
//	sockaddr_in local_addr, server_addr;
//	memset(&local_addr, 0, sizeof(SOCKADDR_IN));
//	memset(&server_addr, 0, sizeof(SOCKADDR_IN));
//
//	if (sClient = socket(AF_INET, SOCK_DGRAM, 0) < 0) {
//		cout << "Open UDP failed\n";
//		WSACleanup();
//		return -1;
//	}
//	local_addr.sin_family = AF_INET;
//	local_addr.sin_addr.s_addr= htonl(INADDR_ANY);
//	local_addr.sin_port = htons(0);
//	if (bind(sClient, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
//		cout << "bind failed\n";
//		return -1;
//	}
//
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_addr.s_addr =inet_addr(com_i.IP);
//	server_addr.sin_port = htons(com_i.port);
//
//	return 0;
//}

int fins_message_len(u_char* a) {
	int i = 0;
	while (a[i] != 204) {
		i++;
	}
	return i;
}

//uint16_t SEND_MSG_Fins(SOCKET sClient, u_char* message, sockaddr_in server_addr) {
//	uint16_t send_len = sendto(sClient, (char*)message, fins_message_len(message), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
//	if (send_len < 0) {
//		cout << "数据发送失败！" << endl;
//		return -1;
//	}
//	else {
//		return send_len;
//	}
//}
//
//uint16_t RECV_MSG_Fins(SOCKET sClient, u_char* message, sockaddr_in server_addr) {
//	int addrlen = sizeof(server_addr);
//	int recv_len = recvfrom(sClient, (char*)message, 100, 0, (struct sockaddr*)&server_addr, &addrlen);
//	if (recv_len < 0) {
//		cout << "接受失败！" << endl;
//		return -1;
//	}
//	else {
//		return recv_len;
//	}
//}

void Fins_message_rebulid(u_char* sendmessage) {
	char tmp[20] = { 0 };
	cout << "please enter fun_conde(read or write): ";
	cin >> tmp;
	if (strcmp(tmp, "read") == 0) {
		sendmessage[11] = 0x01;
		sendmessage[18] = 204;//如果是读的话，将sendmessage[18]
	}
	else if (strcmp(tmp, "write") == 0) {
		sendmessage[11] = 0x02;
	}
	else {}

	cout << "please enter Areaname(DM or CIO): ";
	cin >> tmp;
	if (strcmp(tmp, "DM") == 0) {
		sendmessage[12] = 0x82;
	}
	else if (strcmp(tmp, "CIO") == 0) {
		sendmessage[12] = 0x30;
	}
	else {}

	int Area_start;
	cout << "please enter Areastart(0-100):";
	cin >> Area_start;
	sendmessage[14] = u_char(Area_start);

	if (sendmessage[11] == 0x02) {
		sendmessage[18] = 0x00;
		int data;
		cout << "please enter write data(int):";
		cin >> data;
		sendmessage[19] = char(data);
	}
}

uint16_t Sock_Communication_Fins(command_info com_i , u_char* sendmessage,u_char* recvmessage) {
	fins_sock_initialization();
	SOCKET sClient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	if (sClient == SOCKET_ERROR) {
		cout << "Open UDP failed\n";
		WSACleanup();
		return -1;
	}

	SOCKADDR_IN local_addr;
	memset(&local_addr, 0, sizeof(local_addr));
	local_addr.sin_addr.S_un.S_addr = INADDR_ANY;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(0);
	//int a = bind(sClient, (sockaddr*)&local_addr, sizeof(local_addr));

	if (bind(sClient, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
		cout << "bind failed\n";
		return -1;
	}

	SOCKADDR_IN server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(com_i.IP);
	server_addr.sin_port = htons(com_i.port);

	int addrlen = sizeof(server_addr);
	sendto(sClient, "Client CDL try to connect Fins_UDP", strlen("Client CDL try to connect Fins_UDP"), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
	recvfrom(sClient, (char*)recvmessage, 100, 0, (struct sockaddr*)&server_addr, &addrlen);
	cout << "Connect result: " << recvmessage << endl;

	while (1) {
		Fins_message_rebulid(sendmessage);
		int a = fins_message_len(sendmessage);
		uint16_t send_len = sendto(sClient, (char*)sendmessage, fins_message_len(sendmessage), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
		if (send_len < 0) {
			cout << "数据发送失败！" << endl;
			return -1;
		}
		else {
		}
		int recv_len = recvfrom(sClient, (char*)recvmessage, 100, 0, (struct sockaddr*)&server_addr, &addrlen);
		if (recv_len < 0) {
			cout << "接受失败！" << endl;
			return -1;
		}
		else {
		}
		Command_prase_Fins(recvmessage);
	}
	closesocket(sClient);
	WSACleanup();

	return 0;
}

