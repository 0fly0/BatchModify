/********************************************************
  Copyright (C), 2000-2015, Gero sinco Tech. Co., Ltd.
  File name:   FuncPath.cpp  
  Author:      KFX    
  Version:     1.0.0     
  Date:        2014/07/03
  Description: 实现对路径的处理，包括验证，读取和解析等
  History:      
       <Date>		<Version>	<Author>	<Modification>
	1. 2014/07/03	1.0.0		KFX			创建
*************************************************/

#include "../stdafx.h"
#include "FuncFile.h"
#include "FuncPath.h"

namespace FuncPath
{
	// 获取缓冲区路径
	CString GetSystemTempPath()
	{
		TCHAR szPathJpg[1024];
		::GetTempPath(1024,szPathJpg);
		
		return CString(szPathJpg);
	}

	// 提取文件路径中的路径，或者路径中的父路径
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

	// 提取文件路径提取文件名，包括扩展名
	CString ExtractFileName(const CString& strPath)
	{
		CString strParentPath = ExtractPath(strPath);

		// 无路径，假设其就是文件名
		if( strParentPath.IsEmpty() )
			return strPath;

		return strPath.Right( strPath.GetLength() - strParentPath.GetLength() - 1 );
	}

	// 验证路径是否存在，如果不存在则创建
	void CreateIfNotExist(const CString& strPath)
	{
		if( !IsExist(strPath) )
		{
			int iIndex = strPath.Find('\\',0);
			
			// 创建多级路径
			while( iIndex > 0 )
			{
				CString strTemp = strPath.Left(iIndex+1);
				if( !IsExist(strTemp) )
				{
					::CreateDirectory(strTemp,NULL);
				}
				
				iIndex = strPath.Find('\\',iIndex+1);
			}

			// 在当前程序路径下直接创建该目录
			if( iIndex <= 0 )	
			{
				if( !IsExist(strPath) )
					::CreateDirectory(strPath,NULL);

				return ;
			}
		}
	}

	// 判断路径是否存在，目录或者文件
	bool IsExist(const CString& strPath)
	{
		//CFuncTrace oTrace(_T("FuncPath::IsExist: strPath = ") + strPath);
		wchar_t* ch = (wchar_t*)((LPCTSTR)strPath);
		//wchar_t* chTemp = MultiByteToWideChar(strPath);
		return _waccess(ch,0) != -1;
	}

	//获取文件夹的文件数目
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

	//单张拷贝路径
	BOOL CopyOneDataToSavePath(CString strSrcPath,CString strDestSavePath)
	{
		if(strDestSavePath.IsEmpty())
			return FALSE;
		if(strDestSavePath.IsEmpty())
			return FALSE;
		return ::CopyFile(strSrcPath,strDestSavePath,FALSE);
	}
	//集合拷贝路径
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
		szChar = new char[len];   //以字节为单位
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