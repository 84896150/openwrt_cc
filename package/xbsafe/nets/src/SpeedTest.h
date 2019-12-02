
#ifndef SpeedTestH
#define SpeedTestH
#include <vector>
#include <string>
#include "Common.h"
//---------------------------------------------------------------------------
//LuanSh
//#pragma pack(push,1)
typedef struct _Site
{
	int     type;                   //��Ϊ���ط�������Ϣʱ��1: http, 2: ftp����Ϊ�ϴ���������Ϣʱ��1��http POST��2��ftp��3: TCP; 
	char url[MAX_PATH];               //����URL
	int		port;					//���ֶ�ֻ�����ϴ����٣���ʾ�������Ķ˿ڣ�ֻ��typeΪ3ʱ tcpģʽʱ��Ч��
}TSITE;

typedef struct _CommInfo
{
    TSITE   Site[5];				//���ز���վ����Ϣ,��һ��Ϊʡ����վ��
	TSITE   upServer[5];			//�ϴ�����վ����Ϣ����һ��Ϊʡ����վ��

    _CommInfo()
    {
        memset(this, 0, sizeof(_CommInfo));
    }
}TCOMMINFO, *PCOMMINFO;

typedef struct _WebInfo
{
	int     AllComplated;           //0: δ��ɣ�1��ȫ�����
    int     Index;                  //���(0-ItemCount-1)�����Ա�ʶ�ص�������һ��Url�Ľ��
    int     Status;		            //���״̬, 1: �������, 2: ����ʧ��  
	char 	IP[32];	                //�����������ȡ����ip��ַ
	double     ResponceTime;           //��������Ӧʱ��(ms)
	int     WebPageSize;            //ҳ���С(KB)
	double     LoadTime;               //ҳ��������ʱ��(ms)
	double     DNSTime;			    //dns����ʱ��(ms)
	double     FstPkgTime;	    //http�װ�ʱ��(ms)
	
    _WebInfo() { Init(); }
    void Init() { memset(this, 0, sizeof(_WebInfo)); }
}TWEBINFO, *PTWEBINFO;
//---------------------------------------------------------------------------

//#pragma pack(pop)

//��ѯ�û���Ϣ�ص���result: �����0����ȷ������Ϊ���� 
//�����ش�Ҳʹ���˸ûص���֪ͨ��������ʹ�õ����ص�ַ��id + 1000��
//typedef void (__stdcall *FQueryCallback)(int result, TCOMMINFO*);
//typedef void (*FQueryCallback)(int result, TCOMMINFO*);

//���ز��ٻص�������Status: 1: ��ʼ����, 2: ���ع�����, 3: �������, 4:����ʧ�ܣ� ��ǰ�ٶ�(kb/��)������ٶȡ�ƽ���ٶȡ������ش�С����ɰٷֱ�(0-100)
//typedef void (*FDownloadCallback)(int Status, double CurrSpeed, double MaxSpeed, double AvgSpeed, DWORD dwDownloadSize, int iPostion);
//��ҳ���ٻص�����
//typedef void (*FWebCallback)(TWEBINFO *pWebInfo);   

//�ϴ��Ļص�������Status: 0��ʼ��ʼ��,1: ��ʼ��, 2: ���ع�����, 3: �������, 4����ʧ��,iPostion����ɵİٷֱ�
//typedef void (*FUploadCallback)(int Status, double CurrSpeed, double MaxSpeed, double AvgSpeed, DWORD dwUpSize, int iPostion);
//---------------------------------------------------------------------------
class TSpeedTest
{
public:
	int NTimes;								//����ָ��������Ҫ��ʱ��
    int Status;                             //�������ز���
	
//    FQueryCallback      QCallback;          //��ѯ�û������Ϣ�ص�
//    FDownloadCallback   DloadCallback;      //�ļ����ز��ٻص�
//	FUploadCallback		ULoadCb;//�ϴ��Ĳ��ٻص�
//    FWebCallback        WebCallback;        //��ҳ��Ӧ���ٻص�
    TCOMMINFO UInfo;
   
    int     UrlCount;
    std::vector<std::wstring> PageUrl;                    //��ҳ����URL
    unsigned int UDPTime;
	unsigned int UDPPPS;
	unsigned int UDPBPS;
	unsigned int TotalTime;
	unsigned int UserBandWidth;
	unsigned int WANBPS;
	char if_policy[128];

private:
	int *m_brun;
	double CurrSpeed;
	double MaxSpeed;
	double AvgSpeed;
	unsigned long TotalSize;
	
	unsigned int TotalSendPackets;
	unsigned int TotalReceivedPackets;

	

	EnumFuncTest m_EnumTest;
	std::string m_startTm;
	std::vector<double> m_speedList;
	std::vector<TWEBINFO> m_webspeedList;
	std::vector<LINETESTRESULT> m_vecResult;
	void ComputeToResult(LINETESTRESULT &result);
public:
    TSpeedTest();
    ~TSpeedTest();

    int GetUpSpeedTestStrategy(TestAddrInfo *nAddrInfo);
	int GetDownSpeedTestStrategy(TestAddrInfo *nAddrInfo);
  
	BOOL StartDownload(int ntms,int *brun);
    void StopDownload();    

	BOOL StartRouterUDPDownload(int ntms,int *brun, const char * server, int port, int bandWidth, int PacketSize, int realPacketSize);
	BOOL StartUDPDownload(int ntms,int *brun, const char * server, int port, int user_bandWidth, int bandWidth, int PacketSize, int realPacketSize);
	BOOL AutoStartUDPDownload(int ntms,int *brun, const char * server, int port, int bandWidth, int PacketSize, int realPacketSize);

    BOOL StartWebTest(TestAddrInfo *pAddrInfo,int *brun);
    void StopWebTest();

	BOOL StartUpLoad(int ntms,int *brun);
	void StopUpLoad();
	
	double GetMaxSpeed(){return MaxSpeed;}
	double GetAvgSpeed(){return AvgSpeed;}
	std::vector<double>& GetSpeedList(){ return m_speedList;}
	
	const std::string& GetStartTime(){ return m_startTm; }
	std::vector<LINETESTRESULT>& GetResult();
	unsigned long GetTotalSize();
	unsigned int GetTotalTime();

};
//---------------------------------------------------------------------------
extern TSpeedTest SpeedCls;
//---------------------------------------------------------------------------
#endif
