/********************************************************
  Copyright (C), 2000-2015, Gero sinco Tech. Co., Ltd.
  File name:   FuncPath.cpp  
  Author:      KFX    
  Version:     1.0.0     
  Date:        2014/07/03
  Description: ʵ�ֶ�·���Ĵ���������֤����ȡ�ͽ�����
  History:      
       <Date>		<Version>	<Author>	<Modification>
	1. 2014/07/03	1.0.0		KFX			����
*************************************************/

#include "../stdafx.h"
#include "FuncFile.h"
#include "FuncPath.h"

namespace FuncPath
{
	// ��ȡ������·��
	CString GetSystemTempPath()
	{
		TCHAR szPathJpg[1024];
		::GetTempPath(1024,szPathJpg);
		
		return CString(szPathJpg);
	}

	// ��ȡ�ļ�·���е�·��������·���еĸ�·��
	CString ExtractPath(const CString& strPath)
	{
		if( strPath.IsEmpty() )
			return _T("");

		int nLabelPos = -1;
		nLabelPos = strPath.ReverseFind(_T('\\'));
		if( nLabelPos == -1)
			nLabelPos = strPath.ReverseFind(_T('/'));	

		if( nLabelPos <= 0)
			return _T("");

		CString strTemp = strPath;
		return strTemp.Left(nLabelPos);
	}

	// ��ȡ�ļ�·����ȡ�ļ�����������չ��
	CString ExtractFileName(const CString& strPath)
	{
		CString strParentPath = ExtractPath(strPath);

		// ��·��������������ļ���
		if( strParentPath.IsEmpty() )
			return strPath;

		return strPath.Right( strPath.GetLength() - strParentPath.GetLength() - 1 );
	}

	// ��֤·���Ƿ���ڣ�����������򴴽�
	void CreateIfNotExist(const CString& strPath)
	{
		if( !IsExist(strPath) )
		{
			int iIndex = strPath.Find('\\',0);
			
			// �����༶·��
			while( iIndex > 0 )
			{
				CString strTemp = strPath.Left(iIndex+1);
				if( !IsExist(strTemp) )
				{
					::CreateDirectory(strTemp,NULL);
				}
				
				iIndex = strPath.Find('\\',iIndex+1);
			}

			// �ڵ�ǰ����·����ֱ�Ӵ�����Ŀ¼
			if( iIndex <= 0 )	
			{
				if( !IsExist(strPath) )
					::CreateDirectory(strPath,NULL);

				return ;
			}
		}
	}

	// �ж�·���Ƿ���ڣ�Ŀ¼�����ļ�
	bool IsExist(const CString& strPath)
	{
		//CFuncTrace oTrace(_T("FuncPath::IsExist: strPath = ") + strPath);
		wchar_t* ch = (wchar_t*)((LPCTSTR)strPath);
		//wchar_t* chTemp = MultiByteToWideChar(strPath);
		return _waccess(ch,0) != -1;
	}

	//��ȡ�ļ��е��ļ���Ŀ
	int GetFileCount(const CString& strDir)
	{
		int nCount = 0;
		CFileFind finder;
		
		BOOL bWorking = finder.FindFile(strDir + "\\*.*");
		while(bWorking)
		{
			bWorking = finder.FindNextFile();			
			if (!finder.IsDirectory())
				nCount++;
		}
		
		return nCount;
	}

	void DeleteAllFiles(const CString& strDir)
	{
		//CFuncTrace oTrace("FuncPath::DeleteAllFiles", true);

		CFileFind finder;
		BOOL bWorking = finder.FindFile(strDir + "\\*.*");
		while(bWorking)
		{
			bWorking = finder.FindNextFile();
			if (!finder.IsDirectory())
			{
				FuncFile::Delete(finder.GetFilePath());
			}
		}
	}

	//���ſ���·��
	BOOL CopyOneDataToSavePath(CString strSrcPath,CString strDestSavePath)
	{
		if(strDestSavePath.IsEmpty())
			return FALSE;
		if(strDestSavePath.IsEmpty())
			return FALSE;
		return ::CopyFile(strSrcPath,strDestSavePath,FALSE);
	}
	//���Ͽ���·��
// 	BOOL BatchCopyDataToSavePath(CString strDestPath,vector<CString> veSavePath,int nID,vector<CString>& veSaveImagePath)
// 	{
// 		if(veSavePath.empty())
// 			return FALSE;
// 		vector<CString>::iterator it=veSavePath.begin();
// 		BOOL bCopySucess = TRUE;
// 		for (; it!=veSavePath.end(); it++)
// 		{
// 			CString strFileName = *it;
// 			CString strTempID ;
// 			strTempID.Format(_T("_%d."),nID);
// 			CString strTempPathName = ExtractFileName(strFileName);
// 			strTempPathName.Replace(_T("."),strTempID);
// 			CString strFilePath = strDestPath+_T("\\")+strTempPathName;
// 			if (!CopyOneDataToSavePath(*it,strFilePath))
// 			{
// 				bCopySucess =  FALSE;
// 			}
// 			veSaveImagePath.push_back(strFilePath);
// 		}
// 		
// 		if (!bCopySucess)
// 		{
// 			BatchDeleteData(strDestPath,veSavePath);
// 		}
// 		return bCopySucess;
// 	}

// 	BOOL BatchDeleteData(CString strDestPath,vector<CString> veSavePath)
// 	{
// 		if(veSavePath.empty())
// 			return FALSE;
// 		vector<CString>::iterator it=veSavePath.begin();
// 		for (; it!=veSavePath.end(); it++)
// 		{
// 			CString strFileName = *it;
// 			CString strFilePath = strDestPath+ExtractFileName(strFileName);
// 			::DeleteFile(strFilePath);
// 		}
// 		return TRUE;
// 	}

	char*  GetMultiByte(CString str)  
	{
		char* szChar = NULL;
		int len = 0;
#ifdef _UNICODE
		len = WideCharToMultiByte(CP_ACP,0,str,-1,NULL,0,NULL,NULL);
		szChar = new char[len];   //���ֽ�Ϊ��λ
		memset(szChar,0,len);
		WideCharToMultiByte(CP_ACP,0,str,-1,szChar,len,NULL,NULL);
#else
		len = str.GetLength();
		char* szBuf = str.GetBuffer(str.GetLength());
		szChar = new char[len];
		strcpy_s(szChar,len,szBuf);
		str.ReleaseBuffer();
#endif
		return szChar;
	}

};