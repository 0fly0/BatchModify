#include "StdAfx.h"
#include "SysCfg.h"


CString CSysCfg::m_strInstancePath = _T("");

CSysCfg::CSysCfg(void)
{
}

CSysCfg::~CSysCfg(void)
{

}

/*************************************************
  Function:       InitInstancePath
  Description:    ��ʼ��exe��·��
  Table Accessed: 
  Table Updated:  
  Input:          exe��·��         
  Output:         
  Return:         
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           ����
****************************************************/
void CSysCfg::InitInstancePath(CString strPath)
{
	m_strInstancePath = strPath;
}

/*************************************************
  Function:       GetPictrueDPI
  Description:    ��ȡ��ini�ļ��е�DPIֵ
  Table Accessed: 
  Table Updated:  
  Input:                
  Output:         
  Return:         
    ��ini�ļ��е�DPIֵ
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           ����
****************************************************/
int CSysCfg::GetPictrueDPI()
{
	CString strFilePath = m_strInstancePath + _T("SysCfg.ini");
	CIniFile fileCfg;
	fileCfg.SetFileName(strFilePath);
	int nDPI = fileCfg.LoadInt(_T("SysCfg"),_T("DPI"),0);
	return nDPI;
}


/*************************************************
  Function:       SetPictrueDPI
  Description:    ������ini�ļ��е�DPIֵ
  Table Accessed: 
  Table Updated:  
  Input:       
    ��ini�ļ��е�DPIֵ
  Output:         
  Return:         
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           ����
****************************************************/
void CSysCfg::SetPictrueDPI(int nDPI)
{
	CString strFilePath = m_strInstancePath + _T("SysCfg.ini");
	CIniFile fileCfg;
	fileCfg.SetFileName(strFilePath);
	fileCfg.SaveValue(_T("SysCfg"),_T("DPI"),nDPI);
}

/*************************************************
  Function:       GetPathSave
  Description:    ��ȡ��ini�ļ��еĴ洢·��ֵ
  Table Accessed: 
  Table Updated:  
  Input:       
  Output:         
  Return:  
    ��ini�ļ��еĴ洢·��ֵ
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           ����
****************************************************/
CString CSysCfg::GetPathSave()
{
	CString strFilePath = m_strInstancePath + _T("SysCfg.ini");
	CIniFile fileCfg;
	fileCfg.SetFileName(strFilePath);
	CString strPath = fileCfg.LoadString(_T("SysCfg"),_T("Path"),0);
	return strPath;
}

/*************************************************
  Function:       SetPathSave
  Description:    ������ini�ļ��еĴ洢·��ֵ
  Table Accessed: 
  Table Updated:  
  Input:       
    ��ini�ļ��еĴ洢·��ֵ
  Output:         
  Return:  
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           ����
****************************************************/
void CSysCfg::SetPathSave(CString strPath)
{
	CString strFilePath = m_strInstancePath + _T("SysCfg.ini");
	CIniFile fileCfg;
	fileCfg.SetFileName(strFilePath);
	fileCfg.SaveValue(_T("SysCfg"),_T("Path"),strPath);
}