#ifndef _FUNC_PATH_H_
#define _FUNC_PATH_H_

namespace FuncPath
{
	// ��֤·���Ƿ���ڣ�����������򴴽�
	void CreateIfNotExist(const CString& strPath);

	//��ȡ�ļ��е��ļ���Ŀ
	int GetFileCount(const CString& strDir);

	// ɾ���ļ���������ļ�,����ɾ������ε��ļ����������Ӽ��ļ����Լ�Ŀ¼���ļ�
	void DeleteAllFiles(const CString& strDir);

	// ��ȡ������·��
	CString GetSystemTempPath();

	// �ж�·���Ƿ���ڣ�Ŀ¼�����ļ�
	bool IsExist(const CString& strPath);

	// ��ȡ�ļ�·���е�·��������·���еĸ�·��
	CString ExtractPath(const CString& strPath);

	// ��ȡ�ļ�·����ȡ�ļ�����������չ��
	CString ExtractFileName(const CString& strPath);
	//���ſ���·��
	BOOL CopyOneDataToSavePath(CString strSrcPath,CString strDestSavePath);
	//���Ͽ���·��
	//BOOL BatchCopyDataToSavePath(CString strDestPath,vector<CString> veSavePath,int nID,vector<CString>& veSaveImagePath);
	//ɾ������Ӱ��
	//BOOL BatchDeleteData(CString strDestPath,vector<CString> veSavePath);
	//CStringתchar*
	char*  GetMultiByte(CString str);
};

#endif