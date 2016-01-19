#ifndef _SYSCONFIG_H_
#define _SYSCONFIG_H_

/********************************************************
  Copyright (C), 2000-20**, Gero Tech. Co., Ltd.
  File name:      // SysCfg.h
  Author:       
Version:      
Date: 2015/11/05
  Description:   ��ϵͳ�������ļ����ж�д������DPI��·��Ŀ¼�� 
  Others:       
  ʹ��˵����
  1. ����ʹ��֮ǰ����ʼ������m_strInstancePathΪexe�ĵ�ǰ·����
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           ����
**********************************************************/

#include "IniFile.h"

class CSysCfg
{
public:
	CSysCfg(void);
	~CSysCfg(void);

public:
	static void InitInstancePath(CString );
	static int GetPictrueDPI();
	static void SetPictrueDPI(int nDPI);
	static CString GetPathSave();
	static void SetPathSave(CString strPath);

private:
	// �����
	static CString m_strInstancePath;
	
};


#endif