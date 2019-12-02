// RouterLine.h : Declare the exported functions for the DLL application.
//
#ifndef ROUTERLINE_H
#define ROUTERLINE_H
#include <string.h>
#include <vector>
#include <string>
#include "Common.h"

class CRouterLineQ 
{
public:
	CRouterLineQ();
	~CRouterLineQ();

public:
	const std::string& GetStartTime(){ return m_startTm;  }
	std::vector<LINETESTRESULT>& GetResult(){ return m_vecResult; }

	//��ʼ����ǰ�࣬��netevmchecker��xbmain�ĳ���ģ�����룬����ʼ����ص�����
	//pServGuid:������������ɵ�guid����Ϊͳһ����id,���û�У��������������������ȡ��
	//times:���ٴ�Ϊһ�飬ping���ٴ�
	//nInterval���������
	BOOL  Initialize(int times,int nInterval,const char *ptestIp,int *nrun);

	//�����������������߳�
	int  TraceRouterLineStart();
public:
	BOOL TestLineRoutes();
	void GetRouterLine();
	BOOL PingSpecRouter(const char *pHost,int nSeq);
	BOOL CheckVecIpEqual(std::vector<std::string> ipv1,std::vector<std::string> ipv2);
	double GetDxValue(std::vector<double> &vecVals,double nex);
private:
	std::string m_testip;
	std::string m_startTm;
	int 	*m_prun;
	int		m_pingtms;//��������
	int		m_pingInterval;//�������
	
	std::vector<std::string> m_vectRouterLine1;	
	std::vector<LINETESTRESULT> m_vecResult;//��·���Լ����Ľ����
};

#endif