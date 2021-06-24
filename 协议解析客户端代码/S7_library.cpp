#include"S7_library.h"
#include"tinyxml.h"
#include<iostream>
using namespace std;



void S7_xml_Create() {
	TiXmlDocument* doc = new TiXmlDocument();
	TiXmlDeclaration* declaration = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc->LinkEndChild(declaration);

	TiXmlElement* ProtocolRoot = new TiXmlElement("Protocol");
	doc->LinkEndChild(ProtocolRoot);

	TiXmlElement* createname = new TiXmlElement("name");
	ProtocolRoot->LinkEndChild(createname);
	TiXmlText* nameText = new TiXmlText("S7_TCP");
	createname->LinkEndChild(nameText);

	TiXmlElement* createID = new TiXmlElement("ID");
	ProtocolRoot->LinkEndChild(createID);
	TiXmlText* IDText = new TiXmlText("1");
	createID->LinkEndChild(IDText);

	TiXmlElement* createFuc = new TiXmlElement("Func");
	ProtocolRoot->LinkEndChild(createFuc);
	TiXmlText* Fuc_code = new TiXmlText("read");
	createFuc->LinkEndChild(Fuc_code);

	TiXmlElement* createArea = new TiXmlElement("Area");
	ProtocolRoot->LinkEndChild(createArea);

	TiXmlElement* createAreaname = new TiXmlElement("Areaname");
	createArea->LinkEndChild(createAreaname);
	TiXmlText* A_n = new TiXmlText("Q");
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
	TiXmlText* PORT = new TiXmlText("5010");
	createCOMPORT->LinkEndChild(PORT);

	doc->SaveFile("S7_TCP.xml");
}

int32_t load_S7_xml_profile(const char* path, command_info& com_i) {
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
	if (strcmp(com_i.xml_i.protocol_Func_code,"write") == 0) {
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
	char*tmp = new char[strlen(COMPORT->GetText())];
	strcpy(tmp, COMPORT->GetText());
	com_i.port = u_short(atoi(tmp));
	return 0;
}

void Command_build_S7(command_info com_i,u_char* message) {
	//message-header 10bytes
	message[0] = 0x32;
	message[1] = 0x01;
	message[2] = 0x00;
	message[3] = 0x00;
	message[4] = 0x00;
	message[5] = 0x00;
	message[6] = 0x00;
	message[7] = 0x0e;
	message[8] = 0x00;
	message[9] = 0x06;

	//message-parameter
	int len = atoi(com_i.xml_i.protocol_len);
	if (strcmp(com_i.xml_i.protocol_Func_code, "read") == 0) {
		message[10] = 0x04;
	}
	else if (strcmp(com_i.xml_i.protocol_Func_code, "write") == 0) {
		message[10] = 0x05;
	}
	else {}
	message[11] = 0x01;
	message[12] = 0x12;
	message[13] = 0x0A;
	message[14] = 0x10;
	message[15] = 0x04;
	message[16] = 0x00;
	message[17] = char(len);
	message[18] = 0x00;
	message[19] = 0x00;
	if (strcmp(com_i.xml_i.protocol_Area, "Q") == 0) {
		message[20] = 0x82;
	}
	else if (strcmp(com_i.xml_i.protocol_Area, "M") == 0) {
		message[20] = 0x83;
	}
	else {
	}
	message[21] = 0x00;
	message[22] = 0x00;
	int a_s = atoi(com_i.xml_i.protocol_Areastart);
	message[23] = char(a_s);

	//WriteData
	if (strcmp(com_i.xml_i.protocol_Func_code, "write") == 0) {
		message[24] = 0x00;
		message[25] = 0x04;
		message[26] = 0x00;
		message[27] = char(len);

		
		int data = atoi(com_i.xml_i.protocol_data);
		message[28] = 0x00;
		message[29] = char(data);
	}
	return;
}
void Command_prase_S7(u_char* message) {
	if (message[12] == 0x04) {
		if (message[14] == 0xff) {
			std::cout << "读取PLC数据成功！数据为： ";
			printf("%d\n", message[19]);
		}
		else {
			std::cout << "读取PLC数据失败！错误码为：" << message[14] << std::endl;
		}
	}
	else if (message[12] == 0x05) {
		if (message[14] == 0xff) {
			std::cout << "PLC数据写入成功！" << std::endl;
		}
		else {
			std::cout << "PLC数据写入失败！错误码为：" << hex << message[14] << std::endl;
		}
	}
}

void S7_initialization() {
	//初始化套接字库
	WORD w_req = MAKEWORD(2, 2);//版本号
	WSADATA wsadata;
	int err;
	err = WSAStartup(w_req, &wsadata);
	if (err != 0) {
		cout << "初始化套接字库失败！" << endl;
		return;
	}else {
		cout << "初始化套接字库成功！" << endl;
	}
	//检测版本号
	if (LOBYTE(wsadata.wVersion) != 2 || HIBYTE(wsadata.wHighVersion) != 2) {
		cout << "套接字库版本号不符！" << endl;
		WSACleanup();
	}else {
		cout << "套接字库版本正确！" << endl;
	}
	//填充服务端地址信息
}

//uint16_t Sock_init_S7(SOCKET& sClient,command_info com_i) {
//	S7_initialization();
//	
//	sockaddr_in server_addr;
//	memset(&server_addr, 0, sizeof(SOCKADDR_IN));
//	server_addr.sin_family = AF_INET;
//	server_addr.sin_addr.S_un.S_addr = inet_addr(com_i.IP);
//	server_addr.sin_port = htons(com_i.port);
//	sClient = socket(AF_INET, SOCK_STREAM, 0);
//	if (connect(sClient, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
//		cout << "服务器连接失败！" << endl;
//		WSACleanup();
//		return -1;
//	}
//	else {
//		cout << "服务器连接成功！" << endl;
//	}
//	return 0;
//}

int S7_message_len(u_char* a) {
	int i = 0;
	while (a[i] != 204) {
		i++;
	}
	return i;
}

//uint16_t SEND_MSG_S7(SOCKET sClient, u_char* message) {
//	uint16_t send_len = send(sClient, (char*)message, S7_message_len((u_char*)message),0);
//	if (send_len < 0) {
//		cout << "数据发送失败！" << endl;
//		return -1;
//	}
//	else {
//		return send_len;
//	}
//}
//
//uint16_t RECV_MSG_S7(SOCKET sClient, u_char* message) {
//	int recv_len = recv(sClient, (char*)message, 100, 0);
//	if (recv_len < 0) {
//		cout << "接受失败！" << endl;
//		return -1;
//	}
//	else {
//		return recv_len;
//	}
//}

uint16_t Sock_Communication_S7(command_info com_i, u_char* sendmessage, u_char* recvmessage) {
	SOCKET sClient;
	S7_initialization();
	sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(SOCKADDR_IN));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.S_un.S_addr = inet_addr(com_i.IP);
	server_addr.sin_port = htons(com_i.port);
	sClient = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(sClient, (SOCKADDR*)&server_addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		cout << "服务器连接失败！" << endl;
		WSACleanup();
		return -1;
	}
	else {
		cout << "服务器连接成功！" << endl;
	}
	while (1) {
		S7_message_rebulid(sendmessage);
		uint16_t send_len = send(sClient, (char*)sendmessage, S7_message_len(sendmessage), 0);
		if (send_len < 0) {
			cout << "数据发送失败！" << endl;
			return -1;
		}
		else {
			cout << "数据发送成功！" << endl;
		}

		int recv_len = recv(sClient, (char*)recvmessage, 100, 0);
		if (recv_len < 0) {
			cout << "接受失败！" << endl;
			return -1;
		}
		else {
			Command_prase_S7(recvmessage);
		}
	}

	closesocket(sClient);
	WSACleanup();
	return 0;
}


void S7_message_rebulid(u_char* sendmessage) {
	char tmp[20] = { 0 };

	cout << "please enter fun_conde(read or write): ";
	cin >> tmp;
	if (strcmp(tmp, "read") == 0) {
		sendmessage[10] = 0x04;
	}
	else if (strcmp(tmp, "write") == 0) {
		sendmessage[10] = 0x05;
	}
	else {}

	cout << "please enter Areaname(Q or M): ";
	cin >> tmp;
	if (strcmp(tmp, "Q") == 0) {
		sendmessage[20] = 0x82;
	}
	else if (strcmp(tmp, "M") == 0) {
		sendmessage[20] = 0x83;
	}
	else {}

	int Area_start;
	cout << "please enter Areastart(0-100):";
	cin >> Area_start;
	sendmessage[23] = u_char(Area_start);


	if (sendmessage[10] == 0x05) {
		sendmessage[24] = 0x00;
		sendmessage[25] = 0x04;
		sendmessage[26] = 0x00;
		sendmessage[27] = 0x01;

		int data;
		cout << "please enter write data(int):";
		cin >> data;
		sendmessage[28] = 0x00;
		sendmessage[29] = char(data);
	}
}