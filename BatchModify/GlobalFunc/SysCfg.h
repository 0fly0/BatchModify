#ifndef _SYSCONFIG_H_
#define _SYSCONFIG_H_

/********************************************************
  Copyright (C), 2000-20**, Gero Tech. Co., Ltd.
  File name:      // SysCfg.h
  Author:       
Version:      
Date: 2015/11/05
  Description:   对系统的配置文件进行读写；包括DPI和路径目录。 
  Others:       
  使用说明：
  1. 请在使用之前，初始化变量m_strInstancePath为exe的当前路径。
  History:        
     <Date>      <Version>    <Author>    <Modification>
1.2015/11/05      1.0.0         ZCQ           创建
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
	// 输入的
	static CString m_strInstancePath;
	
};


#endif