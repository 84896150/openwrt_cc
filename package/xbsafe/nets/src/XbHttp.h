#ifndef XBHTTP_H
#define XBHTTP_H

#include <wchar.h>
#include <string>
#include "Common.h"

#pragma pack(push,1)
typedef struct _WebPageTestResult{
	DWORD LoadInSize;//�����ֽ���
	UINT  HttpCd; //������ҳ�ķ�����
	double LoadTime;//��ҳ����ʱ��
	double DnsTime;//����������ʱ��
	double ConnTime;//����ʱ��
	double FstPckTime;//�װ�ʱ��
	double RecvDataTime;//��������ʱ��
}WebPageTestResult;
#pragma pack(pop)

class CXbHttp
{
public:
	CXbHttp(void);
	~CXbHttp(void);
public:
	//���÷��ʳ�ʱ�ĺ�����
	void SetTimeout(int Interval = 15000);

	SOCKET  m_sSocket;
	
	//ָ��ip��ַ���Ե�ʱ��ʹ��
	void SetAddrInfo(const wchar_t *pIp,const unsigned short port);

	// ���������ݡ�
	void SetFlushingMode();

	//-1��ʾʧ�ܣ�0��ʾ�ɹ�
	int Get(const wchar_t *pwszUrl);
	//-1��ʾʧ�ܣ�0��ʾ�ɹ�
	int Post(const wchar_t *pwszUrl,const char *pPostData);

	const char *GetRecvWebContent();
	const char *GetHttpRecvHeader();
	const char *GetServerIp();

	DWORD GetTotalSize();
	DWORD GetLoadSizeInBytes();
	double GetLoadPageTime();
	double GetDnsTime();
	double GetConnectTime();
	double GetFstPkgTime();
	//-1��ʾapi socket_error�������ӳ�ʱ���Ǹ�ֵΪ��Ӧʱ��
	double GetTcpResponceTime(const wchar_t *pServerHost, const unsigned short port = 80);

	int ParseUrltoDomainName(const wchar_t *pUrl);
	bool WaitForWrite();
	bool WaitForRead();
	bool CreateSocket();
	int SendData(const char *pbuf,DWORD dwsize);
	int RecvData(BYTE **pbuf,DWORD *pDwsize); //��Ҫ������ɾ���յ���buf��delete [] buf;
	int FlushingRecvData(DWORD *pDwsize);
	void DisConnect();
	
	void GetTestResult(WebPageTestResult *pResult);
private:
	bool Send(const char *pPostData,int type);
	bool RecvData_();
	int  RequestData(const wchar_t *pwszUrl,const char *pPostData,int type);
	void ProcessTransferEncodeChunked();
	bool GetHTTPRspHeader();
	bool GetHTTPRspCode();
	DWORD FormatRequestHeader(const char *pServer,const char *pObject,DWORD dwcontentlen = 0,int itype = 0);//itype 0Ϊget��1Ϊpost
private:
	int     m_iTimeout;
	bool m_FlushingMode;

	std::wstring m_strUrl;
	std::wstring m_strUrlObj;
	std::wstring m_strSvrDns;
	
	std::string m_strSvrIP;
	std::string m_StrReqBody;
	std::string m_strRspHdr;
	std::string m_requestheader;
	UINT m_uPort;
	UINT m_uHttpCd;
	UINT m_TotalSize;
	double m_loadTime;
	double m_dnsTime;
	double m_connTime;
	double m_fstpacketTime;
	double m_recvdataTime;
};


#endif