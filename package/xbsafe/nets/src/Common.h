#ifndef COMMON_H
#define COMMON_H
#include <stdlib.h>
#include <string>
#include <vector>
#include <sys/time.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//---------------------------------------------------------------------------
typedef char BOOL;
typedef unsigned char BYTE;
typedef unsigned short USHORT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef long long __int64;
typedef int SOCKET;
#define _T
#define TRUE 1
#define FALSE 0
#define BUFFSIZE 1024
#define MAX_PATH 512

#define TRACE_LOG1(format, p1) {printf(format, p1);}
//{va_list pArgList ;	va_start (pArgList, lpszFormat) ; vsntprintf( szBuffer, sizeof (szBuffer) / sizeof (TCHAR),_TRUNCATE, lpszFormat ,pArgList) ; va_end (pArgList) ; }
#define TRACE_LOG2(format, p1, p2) {printf(format, p1,p2);}
#define TRACE_LOG3(format, p1, p2, p3) {printf(format, p1,p2,p3);}
#define TRACE_MSG(msg) 
#define TRACE_TEXT(msg) {printf(msg);}

typedef struct __PingtestResult{
	int funcId;        //������
	char strip[MAX_PATH];//���Ե�ip��ַ
	int nIndx;	//���
	int nSend;   //��������
	int nLost;	//������
	int ninterval;//��������ӳ�
	double nmax;	//���ֵ
	double nmin;	//��Сֵ
	double navg;	//ƽ��ֵ
	double ndx;		//����
	int nvalCode;	//���Խ�����룬0,3��ɣ�4����ʧ�ܣ�5ȡ��
	
	int WebStatus;		//���״̬, 1: �������, 2: ����ʧ��
	int WebPageSize;    //ҳ���С(KB)
	double ResponceTime;   //��������Ӧʱ��(ms)
	double LoadTime;       //ҳ��������ʱ��(ms)
	double DNSTime;		//dns����ʱ��(ms)
	double FstPkgTime;     //http�װ�ʱ��(ms)

	int nUDPTime;	// UDP10���Ӳ���ʱ�䡣
	unsigned int nUDPPPS; //UDP10��û����ٸ���
	unsigned int nUDPBPS; //UDP10��û����ٸ��ֽ�
	unsigned int nTotalTime; //UDP����

	unsigned int nUserBandWidth; //
	unsigned int nWANBPS; //wan�ӿ�����
	unsigned int nOldAvg;
	char if_policy[128];//
	const static int INT_LR_MAX_VALUE = 0;
	const static int INT_LR_INVALID_VALUE = -1;
	const static int INT_LR_VERYLARGE_VALUE = 999999;
	const static int DEFAULT_TEST_TIMES = 200;    //���Դ���Ĭ��ֵ
	const static int DEFAULT_TEST_INTERVAL = 100; //����ʱ����Ĭ��ֵ
	
	
	inline void clear()
	{
		this->nSend = 100;
		this->ninterval = 100;  //�����Ǹ����������ĳ�ֵ 
		this->funcId = INT_LR_INVALID_VALUE;  
		this->nIndx = INT_LR_INVALID_VALUE; 
		this->nLost = INT_LR_INVALID_VALUE; 
		this->nmax = INT_LR_MAX_VALUE; 
		this->nmin = INT_LR_VERYLARGE_VALUE;
		this->navg = 0; 
		this->ndx = 0; 
		this->nvalCode = 0;
		this->WebStatus = 0;
		this->ResponceTime = 0;
		this->WebPageSize = 0;
		this->LoadTime = 0;
		this->DNSTime = 0;
		this->FstPkgTime = 0;

		this->nUDPTime = 0;
		this->nUDPPPS = 0;
		this->nUDPBPS = 0;
		this->nTotalTime = 0;
		this->nUserBandWidth = 0;
		this->nWANBPS = 0;
		this->nOldAvg = 0;
		
		memset(this->strip,0,MAX_PATH);
		memset(this->if_policy,0,128);
	}

	__PingtestResult()
	{
		this->clear();
	}

}LINETESTRESULT;

typedef struct __FunctionInfo
{
	int nfuncId;
	int ninterval;
	int ntimes;
	char szSpeedTime[100];
}FunctionInfo;

typedef struct __TestAddrInfo
{
	char addr[MAX_PATH];
	int nport;
}TestAddrInfo;

struct NetworkPort;
typedef struct __PluginParam{
	struct NetworkPort* port;         //���ݻش�socket.
	int nbusinessType; 	//ҵ����Դ���
	int ncmd;			//0��ʾ������1��ʾֹͣ��2��ѯ���
	int nReqId;			//��Ϣ�е�ID�ֶ�
	char szCmdType[100];//��Ϣ�е������ֶ�
	char szSeqId[100];	//��Ϣ�е����к�
	char ExtendInfo[256]; //���ٽ������Ҫ���ص���Ϣ����|�ָ
	char TestToken[128]; //ԭ�ⲻ���ش� ҵ���̨��ǡ�
	char UUID[128]; //ԭ�ⲻ���ش� ҵ���̨��ǡ�
	char UserBandWidth[64]; //�û�������Ϣ�������ڲ����ٽ��������
	
	char SpeedAddr[MAX_PATH*5];
	FunctionInfo funcList[5]; //���ݾ����ҵ����룬���ɲ��Թ�����Ŀ
	TestAddrInfo addrInfo[5];
}PluginParam;

class TAutoMem
{
private:
	BYTE *pData;
	DWORD dwSize;
public:
	TAutoMem(DWORD uSize):pData(NULL)
	{
		pData = new BYTE[uSize];
		if(pData) 
		{
			dwSize = uSize;
			memset(pData, 0, dwSize);
		}
	}

	~TAutoMem()
	{
		Free();
	}

	void ReSize(DWORD uSize)
	{
		if((uSize != dwSize) && (uSize > 0))
		{
			if(pData)
			{
				delete []pData;
				pData = NULL;  
				dwSize = 0;
			}

			pData = new BYTE[uSize];
			if(pData) 
			{
				dwSize = uSize;
				memset(pData, 0, dwSize);
			}
		}
	}

	bool ReAlloc(DWORD uSize)
	{
		bool balloc = false;

		if((uSize > 0))
		{
			BYTE *tmp = NULL;
			tmp = pData;

			pData = NULL;
			pData = new BYTE[dwSize + uSize];
			if(pData) 
			{
				dwSize += uSize;
				memset(pData, 0, dwSize);
				if (tmp)
				{
					memcpy(pData,tmp,dwSize - uSize);
					delete [] tmp;
				}
				balloc = true;
			}else
			{
				pData = tmp;
			}
		}
		return balloc;
	}

	void Clean()
	{
		if (pData)
		{
			memset(pData, 0, dwSize);
		}
	}

	void Free()
	{
		if(pData)
		{
			delete []pData;
			pData = NULL;  
			dwSize = 0;
		}
	}

	BYTE * GetBuffer() {return pData;}
	DWORD GetSize() {return dwSize;}
};


class TElapsed
{
private:
	struct timeval beginTime;
	
	double tv_sub(struct timeval *endtime,struct timeval *begintime)
	{		
		long sec = endtime->tv_sec - begintime->tv_sec;
		long usec = endtime->tv_usec - begintime->tv_usec;
		if(sec < 0) sec = 0;
		if(usec < 0) usec = 0;
		return (sec * 1000.0 + usec/1000.0);
	};
public:
	TElapsed()
	{
		memset(&beginTime,0,sizeof(struct timeval));
	};
	//---------------------------------------------------------------------

	void Begin()                         //��ʼ����
	{
		gettimeofday(&beginTime,NULL);        
	};
	//---------------------------------------------------------------------

	double End()                         //ֹͣ����,�õ�ʱ���ֵ(����)
	{
		struct timeval endTime;
		gettimeofday(&endTime,NULL);
		
		return tv_sub(&endTime,&beginTime);
	};
	//---------------------------------------------------------------------
};

class CCommonInit{
public:
	CCommonInit();
	~CCommonInit();
public:
	int GetRand(int nSeed);
	int GetRand(int LSeed, int RSeed);
};

typedef enum{
	ENUM_ROUTE_TRACER = 100, 
	ENUM_TCP_DELAY, 
	ENUM_UDP_DELAY, 
	ENUM_UDP_LOST,
	ENUM_SPEED_DOWN,
	ENUM_SPEED_UP,
	ENUM_SPEED_PING,
	ENUM_SPEED_TRACEROUTE,
	ENUM_SPEED_TELNET,
	ENUM_SPEED_WEB_SPEED,
	ENUM_SPEED_1000M_DOWN,   //110
	ENUM_SPEED_CTC_DOWN,
	ENUM_SPEED_ROUTER_DOWN,
	ENUM_SPEED_UDP_UPLOAD
	
}EnumFuncTest; 

extern CCommonInit CommonInit;
extern bool ParseUrl(const wchar_t*strWeb,std::wstring &ustrHost,std::wstring &ustrObj,int &nPort);
extern bool ParseUrl(const char*strWeb,std::string &ustrHost,std::string &ustrObj,int &nPort);

extern int strpos(const char *pSrc, const char *pDst);
extern int stripos(const char *pSrc, const char *pDst);
extern int wstrpos(const wchar_t *pSrc, const wchar_t *pDst);
extern int wstripos(const wchar_t *pSrc,const wchar_t *pDst);
extern size_t strnicmp_fast(char *pSrc, char *pDst, size_t Len);
extern size_t wcsnicmp_fast(wchar_t *pSrc, wchar_t *pDst, size_t Len);

extern int Random(int aValue);
extern int Random(int mValue,int nValue);

extern void URLEncode(wchar_t *pzUrl, int MaxChars);
extern void DelChars(wchar_t *pzSrc);
extern void DelChars(char *pzSrc);

extern char * Byte2Hex(BYTE Val);
extern std::wstring ULToStr(unsigned long nV);

extern const char* strncut(char*strDest,char*strSource,int iStartPos,int iNum);

extern bool w2c(const wchar_t *str,std::string &pwstr);				//��unicode �ַ�ת��Ϊascii�ַ����ں����ڲ�����洢�ռ䡣
extern bool c2w(const char *str,std::wstring &pwstr);				//��ascii �ַ�ת��Ϊunicode�ַ����ں����ڲ�����洢�ռ䡣

extern bool w2c(const wchar_t *str, char *pstr, int *nsize);				
extern bool c2w(const char *str, wchar_t *pwstr, int *nsize);				

extern bool UTF8ToUnicode(const char *pUtf8,std::wstring &strUnicodeDes);
extern bool UnicodeToUTF8(const wchar_t *pUnicode,std::string &strUtf8Des);

extern std::wstring GetXmlNodeValue(const wchar_t *pwzXmlTxt, const wchar_t *pNodeName);
extern std::wstring GetXmlAttributeSValue(const wchar_t *pwzXmlTxt,const wchar_t *pAttribName);
extern int GetXmlAttributeIValue(const wchar_t *pwzXmlTxt,const  wchar_t *pAttribName);

extern std::string GetXmlNodeValue(const char *pwzXmlTxt, const char *pNodeName);
extern std::string GetXmlAttributeSValue(const char *pwzXmlTxt, const char *pAttribName);
extern int GetXmlAttributeIValue(const char *pzXmlTxt,const  char *pAttribName);

//���ܣ�ȥ���ַ����еĿո�ͽ�β��
extern std::string TrimEndLine(const char* pCode);

extern std::string& MyTrim(std::string& text);
extern std::wstring& MyTrim(std::wstring& text);

extern std::wstring& MyToLower(std::wstring& text);
extern std::wstring& MyToUpper(std::wstring& text);
extern std::string& MyToLower(std::string& text);
extern std::string& MyToUpper(std::string& text);

extern void MyWstrSplit(std::wstring& text,std::vector<std::wstring> &vec);
extern void MyAstrSplit(std::string& text,std::vector<std::string> &vec);

extern BOOL IsIPV4(wchar_t *pwzAddr);  
extern BOOL IsIPV4(char *pzAddr);  
extern bool Dns(const char *szHost,char *pIp,size_t sIpSize);

extern void GetSystemTime(std::wstring &startTime);
extern int _wtoi(const wchar_t *pvalue);
extern int checkNetLink(const char *host);
//extern bool Encode(const char *pSrc, std::string &Dst, int &r1, int &r2);
//extern bool Decode(std::string Src, std::string &Dst, int r1, int r2);

#endif