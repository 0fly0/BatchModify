#ifndef _FUNC_PATH_H_
#define _FUNC_PATH_H_

namespace FuncPath
{
	// 验证路径是否存在，如果不存在则创建
	void CreateIfNotExist(const CString& strPath);

	//获取文件夹的文件数目
	int GetFileCount(const CString& strDir);

	// 删除文件夹里面的文件,仅仅删除本层次的文件，不包括子级文件夹以及目录的文件
	void DeleteAllFiles(const CString& strDir);

	// 获取缓冲区路径
	CString GetSystemTempPath();

	// 判断路径是否存在，目录或者文件
	bool IsExist(const CString& strPath);

	// 提取文件路径中的路径，或者路径中的父路径
	CString ExtractPath(const CString& strPath);

	// 提取文件路径提取文件名，包括扩展名
	CString ExtractFileName(const CString& strPath);
	//单张拷贝路径
	BOOL CopyOneDataToSavePath(CString strSrcPath,CString strDestSavePath);
	//集合拷贝路径
	//BOOL BatchCopyDataToSavePath(CString strDestPath,vector<CString> veSavePath,int nID,vector<CString>& veSaveImagePath);
	//删除集合影像
	//BOOL BatchDeleteData(CString strDestPath,vector<CString> veSavePath);
	//CString转char*
	char*  GetMultiByte(CString str);
};

#endif