// PengIniFile.cpp: implementation of the CIniFile  class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IniFile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CIniFile::CIniFile ()
{
	m_strFilePath=_T("");
}

CIniFile::~CIniFile ()
{

}
CIniFile::CIniFile (LPCTSTR lpszPathName)
{
	m_strFilePath=lpszPathName;
}

BOOL CIniFile::SaveValue(CString strSecttionName,CString strKeyName,LPCTSTR lpString)
{

	if(m_strFilePath.IsEmpty())
		return FALSE;
	if(::WritePrivateProfileString(strSecttionName,strKeyName,lpString,m_strFilePath))
		return TRUE;
	else
		return FALSE;
}

BOOL CIniFile::SaveValue(CString strSecttionName,CString strKeyName,double dValue)
{
	if(m_strFilePath.IsEmpty())
		return FALSE;
	CString strTemp;
	strTemp.Format(_T("%f"),dValue);
	if(::WritePrivateProfileString(strSecttionName,strKeyName,strTemp,m_strFilePath))
		return TRUE;
	else
		return FALSE;
}
BOOL CIniFile::SaveValue(CString strSecttionName,CString strKeyName,int iValue)
{
	if(m_strFilePath.IsEmpty())
		return FALSE;
	CString strTemp;
	strTemp.Format(_T("%i"),iValue);
	if(::WritePrivateProfileString(strSecttionName,strKeyName,strTemp,m_strFilePath))
		return TRUE;
	else
		return FALSE;
}
CString CIniFile::LoadString(CString strSecttionName,CString strKeyName)
{
	CString strReturn=_T("");
	TCHAR szRead[256];
    ::GetPrivateProfileString(strSecttionName,strKeyName,_T("Error"),szRead,256,m_strFilePath);
	if(_tcscmp(szRead,_T("Error"))==0)
	{
		return strReturn;
	}
	else
	{
		strReturn.Format(_T("%s"),szRead);
		return strReturn;
	}
}
double CIniFile::LoadDouble(CString strSecttionName,CString strKeyName)
{
	double dReturnValue=0.00;
	TCHAR szRead[12];
    ::GetPrivateProfileString(strSecttionName,strKeyName,_T("Error"),szRead,12,m_strFilePath);
	if(_tcscmp(szRead,_T("Error"))==0)
	{
		return dReturnValue;
	}
	else
	{

#ifdef _UNICODE
		dReturnValue=_wtof(szRead);
#else
		dReturnValue=atof(szRead);
#endif
		return dReturnValue;
	}
}

float CIniFile::LoadFloat(CString strSecttionName,CString strKeyName)
{
	float fReturnValue=0.00;
	TCHAR szRead[12];
    ::GetPrivateProfileString(strSecttionName,strKeyName,_T("Error"),szRead,12,m_strFilePath);
	if(_tcscmp(szRead,_T("Error"))==0)
	{
		return fReturnValue;
	}
	else
	{
#ifdef _UNICODE
		fReturnValue=float(_wtof(szRead));
#else
		fReturnValue=float(atof(szRead));
#endif
		return fReturnValue;
	}
}

int CIniFile::LoadInt(CString strSecttionName,CString strKeyName)
{
	int iReturnValue=0;
	iReturnValue=::GetPrivateProfileInt(strSecttionName,strKeyName,-9999,m_strFilePath);
	if(iReturnValue==-9999)
		return iReturnValue;
	else
		return iReturnValue;
}

CString CIniFile::LoadString(CString strSecttionName,CString strKeyName,CString strDefault)
{
	CString strReturn=_T("");
	TCHAR szRead[256];
    ::GetPrivateProfileString(strSecttionName,strKeyName,_T("Error"),szRead,256,m_strFilePath);
	if(_tcscmp(szRead,_T("Error"))==0)
	{		
		return strReturn;
	}
	else
	{
		strReturn.Format(_T("%s"),szRead);
		return strReturn;
	}
}
double CIniFile::LoadDouble(CString strSecttionName,CString strKeyName,double dDefault)
{
	double dReturnValue=0.00;
	TCHAR szRead[12];
    ::GetPrivateProfileString(strSecttionName,strKeyName,_T("Error"),szRead,12,m_strFilePath);
	if(_tcscmp(szRead,_T("Error"))==0)
	{
		if (SaveValue(strSecttionName,strKeyName,dDefault))
		{ 
			dReturnValue=dDefault;
			return dReturnValue;
		}
		else
    		return dReturnValue;
	}
	else
	{
#ifdef _UNICODE
		dReturnValue=_wtof(szRead);
#else
		dReturnValue=atof(szRead);
#endif
		return dReturnValue;
	}
}

float CIniFile::LoadFloat(CString strSecttionName,CString strKeyName,float fDefault)
{
	float fReturnValue=0.00;
	TCHAR szRead[12];
    ::GetPrivateProfileString(strSecttionName,strKeyName,_T("Error"),szRead,12,m_strFilePath);
	if(_tcscmp(szRead,_T("Error"))==0)
	{
		if (SaveValue(strSecttionName,strKeyName,fDefault))
		{ 
			fReturnValue=fDefault;
			return fReturnValue;
		}
		else
			return fReturnValue;
	}
	else
	{
#ifdef _UNICODE
		fReturnValue=float(_wtof(szRead));
#else
		fReturnValue=float(atof(szRead));
#endif
		return fReturnValue;
	}
}

int CIniFile::LoadInt(CString strSecttionName,CString strKeyName,int iDefault)
{
	int iReturnValue=0;
	iReturnValue=::GetPrivateProfileInt(strSecttionName,strKeyName,-9999,m_strFilePath);
	if(iReturnValue==-9999)
	{
		if (SaveValue(strSecttionName,strKeyName,iDefault))
		{ 
			iReturnValue=iDefault;
			return iReturnValue;
		}
		else
			return iReturnValue;
	}
	else
		return iReturnValue;
}
CString CIniFile::CreateFullFileName(CString strFileName)
{
	CString strReturn;
	TCHAR szFilePath[256];
	memset(szFilePath,0,256*sizeof(TCHAR));
	GetModuleFileName(NULL,szFilePath,256);
	//If the function succeeds, the return value is the length,
	//in TCHARacters, of the string copied to the buffer.
	for(int i=256;i>4;i--)
	{
		if(szFilePath[i]=='\\')
		{
			szFilePath[i+1]='\0';
			break;
		}
	}
	strReturn.Format(_T("%s%s"),szFilePath,strFileName.GetBuffer(0));
	return strReturn;
}

	