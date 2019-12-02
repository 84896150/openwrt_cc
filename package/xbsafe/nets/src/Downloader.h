
#ifndef DownloaderH
#define DownloaderH
//---------------------------------------------------------------------------
#include <string>
#include <vector>
#include "TThread.h"
#include "Common.h"
#include "SpeedTest.h"
//---------------------------------------------------------------------------

typedef struct _ThreadParam
{     
    TSITE   *pSite1;
    TSITE   *pSite2;
    int     *pControl;
	int	    *pStatus;
	DWORD	*pdwSize;
	long	*pThreadCnt;
}THREADPARAM;

typedef struct _UpThreadParam
{     
	TSITE   *pSite1;
	TSITE   *pSite2;
	int     *pControl;
	int	    *pStatus;
	DWORD	*pdwSize;
	long	*pThreadCnt;
}UPTHREADPARAM;


//���������߳�
class TRecvThread : public TCThread
{
private:
    TSITE       Site1, Site2;
    int        *pFControl;
    SOCKET      FSocket;

    int         FType;                  //1: http, 2: ftp
    wchar_t     FServerIP[40];          //������IP
    wchar_t     DomainName[80];         //����
    wchar_t     FObject[100];           //���ض���
    wchar_t     UserName[40];           //ftp�û���
    wchar_t     Password[40];           //ftp����
    int         FPort;                  //�˿ں�

	long		*pDLThreadCount;
    int         *pFStatus;                //0: �գ� 1: ��ȡ������Ϣ 2: �������أ�3��ȡ��, 4: ���� 5�����
    DWORD       *pFSize;                  //�����ش�С
    //CMutex_		m_Mutex;     
	void AnalyseUrl(int idx);   
    
    BOOL AnalyseFtp(const wchar_t *sURL);
	BOOL AnalyseHttp(const wchar_t *sURL);
	BOOL MakeRequestParam(std::string &strReq);
	BOOL SendRequest(std::string &strReq);
	BOOL GetHTTPrecvHeader(std::string &strHeader);
    BOOL DownloadHttpFile(const wchar_t *sURL);
	BOOL DownloadFtpFile_Socket(const wchar_t *sURL);
	int  SendCommandToServer(SOCKET &st,const char * pcmd,std::string *strRecv);
	BOOL ParsePasvData(std::string &strRecv,std::string &strIp,int &nPort);
    BOOL CreateSocket(SOCKET *pSocket,const wchar_t *pIp, unsigned short nport,int ntype = 0);//0��ʾhttp���أ�1��ʾftpcmd��2��ʾftpdata
protected:
    void Execute();
public:
    TRecvThread(bool CreateSuspended, THREADPARAM *para);
    virtual ~TRecvThread();
	void Run();
};
//---------------------------------------------------------------------------
  
class TSendThread : public TCThread
{
private:
	int         *pFStatus;                //0: �գ� 1: ��ȡ������Ϣ 2: �������أ�3��ȡ��, 4: ���� 5�����
	DWORD       *pFSize;                  //�����ش�С
	long		*pULThreadCount;
	//CMutex_		m_Mutex;    
	UPTHREADPARAM UpPara;
protected:
	void Execute();
	bool UpLoad(TSITE *pSite);
public:
	TSendThread(bool CreateSuspended, UPTHREADPARAM *para);
	virtual ~TSendThread();
	void Run();
};

//---------------------------------------------------------------------------

class TWebThread : public TCThread
{
private:
    std::wstring Url;
    TWEBINFO *pWebInfo;
    int FControl;         //�������Ƴ����Ƿ�ֹͣ
	
protected:
    void Execute();

public:
    TWebThread(std::wstring webPage, TWEBINFO *pInfo);
    virtual ~TWebThread();

    void Terminate() { Terminated(true); }
	void Run();
};
//---------------------------------------------------------------------------

class TDownloader
{
private:  
    int FControl;
    int FStatus;
	
	DWORD dwDSize1,dwDSize2,dwDSize3,dwDSize4;
	DWORD dwUSize1,dwUSize2,dwUSize3,dwUSize4;
	int FDStatus1,FDStatus2,FDStatus3,FDStatus4;
	int FUStatus1,FUStatus2,FUStatus3,FUStatus4;
	long ThreadCount;

	TWEBINFO WebItems[10];
	TWebThread *pthread[10];
	TRecvThread *pDownThread[5];
	TSendThread *pUpThread[5];
public:
    TDownloader();
    ~TDownloader();
              
    void StartDownload(TSITE *pSite, int Items);
    void StopDownload();
    int GetStatus();
    DWORD GetSize();

	void StartUpLoad(TSITE *pSite, int Items);
	void StopUpLoad();
	int GetUpStatus();
	DWORD GetUpSize();
	
	void StartWebTest(std::vector<std::wstring> &urlList, int itemCnt);
	void StopWebTest();
	TWEBINFO * GetWebTestItem(int indx);
	void StopWebThread(int indx);
};         

//---------------------------------------------------------------------------

#endif
