/********************************************************
  Copyright (C), 2000-2015, Gero sinco Tech. Co., Ltd.
  File name:   FuncFile.cpp 
  Author:      KFX    
  Version:     1.0.0     
  Date:        2014/06/12
  Description: 实现对文件的操作，包括文件验证读取以及删除等
  History:      
       <Date>		<Version>	<Author>	<Modification>
	1. 2014/06/12	1.0.0		KFX			创建
*************************************************/

#include "stdafx.h"
#include "FuncFile.h"
#pragma comment(lib,"Version.lib") 
namespace FuncFile
{
// 	long CalculateFileSize(const CString& strFile)
// 	{
// 		//CFuncTrace oFuncTrace("FuncFile::CalculateFileSize",true);
// 
// 		CFile file;
// 		if( !file.Open(strFile,CFile::modeRead) )
// 			return 0L;
// 
// 		long lLen = file.GetLength();
// 		file.Close();
// 
// 		return lLen;
// 	}

// 	unsigned char* ReadFile(const CString& strFile)
// 	{
// 		//CFuncTrace oFuncTrace("FuncFile::ReadFile",true);
// 
// 		CFile file;
// 		if( !file.Open(strFile,CFile::modeRead) )
// 			return NULL;
// 
// 		long lLen = file.GetLength();
// 		unsigned char* result = new unsigned char[lLen + 1];
// 
// 		memset(result,0, lLen + 1 );
// 		file.Read(result,lLen);
// 
// 		file.Close();
// 		return result;
// 	}

	bool WriteFile(const CString& strFile, const unsigned char* pBuffer, long nSize)
	{
		//CFuncTrace oFuncTrace("FuncFile::WriteFile",true);

		CFile fileSave;
		if( !fileSave.Open(strFile,CFile::modeCreate | CFile::modeReadWrite) )
		{
			return false;
		}

		fileSave.Write((void*)pBuffer,nSize);
		fileSave.Close();

		return true;
	}

	// 获取文件信息中的版本信息
	CString GetFileVersion(const CString& strFilePath)
	{
		CString szResult(_T("0.0.0.0"));

		if (strFilePath.GetLength() <= 0 || !::PathFileExists(strFilePath))
		{
			return szResult;
		}

		DWORD dwTemp;
		DWORD dwSize = ::GetFileVersionInfoSize(strFilePath, &dwTemp);
		if (dwSize == 0)
		{
			return szResult;
		}

		BYTE *pData = new BYTE[dwSize+1];
		if (pData == NULL)
		{
			return szResult;
		}

		if (!::GetFileVersionInfo(strFilePath, 0, dwSize, pData))
		{
			delete[] pData;
			return szResult;
		}

		UINT uLen;
		VS_FIXEDFILEINFO *pVerInfo = NULL;
		if (!::VerQueryValue(pData, TEXT("\\"), (void **)&pVerInfo, &uLen)) 
		{
			delete[] pData;
			return szResult;
		}

		DWORD verMS = pVerInfo->dwFileVersionMS;
		DWORD verLS = pVerInfo->dwFileVersionLS;
		DWORD major = HIWORD(verMS);
		DWORD minor = LOWORD(verMS);
		DWORD build = HIWORD(verLS);
		DWORD revision = LOWORD(verLS);
		delete[] pData;

		szResult.Format(TEXT("%d.%d.%d.%d"), major, minor, build, revision);
		return szResult;
	}

	void Delete(const CString& strPath)
	{
		::DeleteFile(strPath);
	}

	void Delete(const vector<CString>& vecFiles)
	{
		for(vector<CString>::const_iterator iter = vecFiles.begin(); iter != vecFiles.end(); ++iter)
			Delete(*iter);
	}

	// 删除文件夹下指定后缀的文件
	void DeleteDirectory(CString strPath,CString strSuffix)
	{
		CString strTemp=strPath;
		CString strFilePath=strPath;
		CFileFind finder;
		BOOL bWorking;
		bWorking=finder.FindFile(strPath+_T("\\*")+strSuffix);
		while(bWorking)
		{
			bWorking = finder.FindNextFile();
			//如果是“.”则不处理
			if (finder.IsDots())
			{
				continue;
			}
			//如果是目录，继续扫描此目录
			else if (finder.IsDirectory())
			{
				strPath = finder.GetFileName();
				strTemp = strTemp+_T("\\")+strPath;
				DeleteDirectory(strTemp,strSuffix);
			}
			//文件
			else
			{
				strPath = finder.GetFileName();
				strFilePath=strFilePath+_T("\\")+strPath;
				DeleteFile(strFilePath);
				CString strCut = _T("\\")+strPath;
				strFilePath.Replace(strCut,_T(""));
				//strFilePath.TrimLeft(strCut);
			}
		}
	}

};