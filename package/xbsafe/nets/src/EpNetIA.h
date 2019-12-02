#ifndef EPNETIA_H
#define EPNETIA_H

#include <string>
#include <vector>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include "PhysicalSocket.h"
#include "Common.h"

#define UDP_PACKET           9
#define TCP_PACKET           8
#define SUB_UDP_DELAY        91
#define SUB_UDP_LOST         92
#define SUB_UDP_MSG          93
#define SUB_TCP_SERVER_CMD   80
#define SUB_TCP_DELAY        81
#define SUB_TCP_LOST         82
#define SUB_TCP_MSG          83

#define PACKET_LIMIT_MSG     1376

struct NetTestPacketHeader
{
	BYTE			mark[6];			//�����ʾ
	BYTE            type;               // ���� ���͵İ����ͣ�udp��tcp��
	BYTE            code;               // ���� �����ʹ��� ��Ϊ83��93ʱ˵��Я�����ݣ���Ҫ����content���ж�ulDatalen
	UINT          id;                 // ��ʶ ��ǰ���̵�id
	UINT          number;             // ���к�
	unsigned long	sendstamp;          // ���͵�ʱ���
	unsigned long	recvstamp;			// ���յ�ʱ���
	unsigned long	ulDatalen;			// ��ʾ���滹��û�����ݸ��棬���Ϊ0��ʾ��Я�����ݰ���content����code�ж��Ƿ������ݣ�����������ʾ��������Ч���ݰ����棬contentΪ����
	BYTE			content[PACKET_LIMIT_MSG];		// ��������codeΪ83������ֶδ洢���ǽ����������֣�����ֻ��Я����������ݣ���������

	NetTestPacketHeader()
	{
		memset(this,0,sizeof(NetTestPacketHeader));
		mark[0] = 0x01;
		mark[1] = 0x02;
		mark[2] = 0x03;
		mark[3] = 0x04;
		mark[4] = 0x05;
		mark[5] = 0x06;
	}
};

//itype��0 Client��Server���������Ϣ��������pMsg��
//�ӷ��������յ���������Ϣ���ϲ���д���LoginOK��LogoutOK��OnlineUserList��NetSpeedTestInfo��
//1socke���ӷ������ɹ���2socket���ӷ�����ʧ�ܣ�3��������
//10Ϊudp������
//11Ϊudp��socket�����ɹ���12Ϊudp socket����
typedef void ( *FNetNotify)(int itype,const NetTestPacketHeader *pPacketHeader,wchar_t *pExtraMsg);

class EpNetIA
{
public:
	EpNetIA(void);
	~EpNetIA(void);
public:
	BOOL TcpInit(FNetNotify cbnn,const char *pServer,USHORT tcpPort);
	BOOL UdpInit(FNetNotify cbnn,const char *pServer,USHORT udpPort);


	int Recv();
	BOOL SendBye();
	BOOL Start();
	void Stop();
	int GetSocketState(); //0�Ѿ��رգ�1�������ӣ�2������

	void UpCallBack(int itype,const NetTestPacketHeader *pPacketHeader = NULL,wchar_t *pMsg = NULL)
	{
		if (m_Cb != NULL)
		{
			m_Cb(itype,pPacketHeader,pMsg);
		}
	}
	BOOL m_bRun;
	int m_tcpRecv;
	int m_udpRecv;
	BOOL CreateUdpConn();
	BOOL SendPacket(int type,NetTestPacketHeader &ntph);
	PhysicalSocket m_pys;
	PhysicalSocket m_pysUdp;
private:
	FNetNotify m_Cb;
	struct sockaddr_in sin;
	struct sockaddr_in udpsin;

	std::string m_serverhost;//������ip�������������ơ�
	USHORT m_uport;//���������ӵĶ˿ں�tcp
	USHORT m_udpport;//���������ӵĶ˿ں�udp
	std::vector<std::string> m_vecMsg;
	std::string m_currentMsg;
	pthread_t m_RecvThread;
	pthread_t m_UdpRecvThread;
private:
	void CleanUp();
	void CloseSocket(PhysicalSocket &pys){ if (pys.GetState() != PhysicalSocket::CS_CLOSED) pys.Close();  }
};

#endif