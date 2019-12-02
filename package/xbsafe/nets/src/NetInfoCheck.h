#pragma once
#include <string>
#include <string.h>
#include "Common.h"

class CNetInfoCheck
{
public:
	CNetInfoCheck(void);
	~CNetInfoCheck(void);
public:
	 /// �ж�IP��ַ�Ƿ�Ϊ����IP��ַ
	 BOOL IsInnerIP(const wchar_t *ipAddress);

	 BOOL IsInnerIP(const char *ipAddress);

	 ///check the ip string is legal or not.
	 BOOL IsIPV4(const wchar_t *pwc_Strip);

	 BOOL IsIPV4(const char *pzAddr);

	 /// ��IP��ַת��ΪLong������
	 unsigned long GetIpNum(const wchar_t *ipAddress);

	 //��ȡ������Mac��ַ
	 std::wstring GetMyPcMAC();

	 //��ȡ����������
	 BOOL GetMyPcHostName(char *RecvBuf,int len);
	 //--------------------------------------------------------------------------


	 int Dns(wchar_t *wszHost,char *pIp,size_t sIpSize);
	 BOOL GetSockClientIp(SOCKET s,char *ipaddr);//local pc
	 BOOL GetSockServerIp(SOCKET s,char *ipaddr);//remote pc
	 BOOL GetCurIpWithSocket(const char *host, char *pIpAddr);//��ȡ��ǰ�û�����ip 0��ʾ�ɹ���������ʾʧ��
	 BOOL GetIpListWithWSAioctl(int &icnt);

	 BOOL GetCurUsedIp(char* pipAddr,int iplen);
	 BOOL GetLocalIP(char* pipAddr,int iplen);
private:

	 /// �ж��û�IP��ַת��ΪLong�ͺ��Ƿ�������IP��ַ���ڷ�Χ
	 BOOL IsInner(unsigned long userIp,unsigned long begin,unsigned long end);

	 ///convert the ip string to unsigned int.
	 BOOL Str2ulongIP(wchar_t *pwc_Strip,unsigned long * puint_ip);
	
};

