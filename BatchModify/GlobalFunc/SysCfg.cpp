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
  Description:    初始化exe的路径
  Table Accessed: 
  Table Updated:  
  Input:          exe的路径         
  Output:         
  Return:         
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           创建
****************************************************/
void CSysCfg::InitInstancePath(CString strPath)
{
	m_strInstancePath = strPath;
}

/*************************************************
  Function:       GetPictrueDPI
  Description:    获取在ini文件中的DPI值
  Table Accessed: 
  Table Updated:  
  Input:                
  Output:         
  Return:         
    在ini文件中的DPI值
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           创建
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
  Description:    设置在ini文件中的DPI值
  Table Accessed: 
  Table Updated:  
  Input:       
    在ini文件中的DPI值
  Output:         
  Return:         
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           创建
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
  Description:    获取在ini文件中的存储路径值
  Table Accessed: 
  Table Updated:  
  Input:       
  Output:         
  Return:  
    在ini文件中的存储路径值
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           创建
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
  Description:    设置在ini文件中的存储路径值
  Table Accessed: 
  Table Updated:  
  Input:       
    在ini文件中的存储路径值
  Output:         
  Return:  
  Others:         
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           创建
****************************************************/
void CSysCfg::SetPathSave(CString strPath)
{
	CString strFilePath = m_strInstancePath + _T("SysCfg.ini");
	CIniFile fileCfg;
	fileCfg.SetFileName(strFilePath);
	fileCfg.SaveValue(_T("SysCfg"),_T("Path"),strPath);
}