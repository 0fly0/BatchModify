
// BatchModify.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CBatchModifyApp:
// �йش����ʵ�֣������ BatchModify.cpp
//

class CBatchModifyApp : public CWinAppEx
{
public:
	CBatchModifyApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CBatchModifyApp theApp;
extern CString strInstancePath;