// IniFile.h: interface for the CIniFile  class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENGINIFILE_H__EB5D4837_B0FE_4F0C_BC17_CA8D5F84BC83__INCLUDED_)
#define AFX_PENGINIFILE_H__EB5D4837_B0FE_4F0C_BC17_CA8D5F84BC83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define NO_VALUE	(-9999)

class CIniFile : public CObject  
{
public:
	CIniFile ();
	CIniFile (LPCTSTR lpszPathName);
	virtual ~CIniFile ();
public:
	//Set full path of ini file
	void SetFileName(CString lpszFilePath){m_strFilePath=lpszFilePath;}
	//Get Full File path
	CString GetFileName(){return m_strFilePath;}
	//Create a file under the debug folder
	CString CreateFullFileName(CString strFileName);
	
	BOOL	SaveValue(CString strSectionName,CString strKeyName,LPCTSTR lpString);
	BOOL	SaveValue(CString strSectionName,CString strKeyName,double dValue);
	BOOL	SaveValue(CString strSectionName,CString strKeyName,int iValue);
	CString LoadString(CString strSectionName,CString strKeyName);
	CString LoadString(CString strSecttionName,CString strKeyName,CString strDefault);
	double	LoadDouble(CString strSectionName,CString strKeyName);
	double	LoadDouble(CString strSectionName,CString strKeyName,double dDefault);
	float	LoadFloat(CString strSectionName,CString strKeyName);
	float	LoadFloat(CString strSectionName,CString strKeyName,float fDefault);
	int		LoadInt(CString strSectionName,CString strKeyName,int iDefault);
	int		LoadInt(CString strSectionName,CString strKeyName);
	
protected:	
	CString m_strFilePath;
};



#endif // !defined(AFX_PENGINIFILE_H__EB5D4837_B0FE_4F0C_BC17_CA8D5F84BC83__INCLUDED_)
