#ifndef _FUNC_FILE_H_
#define _FUNC_FILE_H_

namespace FuncFile
{
	//long CalculateFileSize(const CString& strFile);
	//unsigned char* ReadFile(const CString& strFile);
	bool WriteFile(const CString& strFile, const unsigned char* pBuffer, long nSize);
	
	CString GetFileVersion(const CString& strFilePath);

	void Delete(const CString& strPath);
	void Delete(const vector<CString>& vecFiles);
	void DeleteDirectory(CString strPath,CString strSuffix);
};

#endif