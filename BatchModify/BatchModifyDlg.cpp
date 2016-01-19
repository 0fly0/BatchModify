
// BatchModifyDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "BatchModify.h"
#include "BatchModifyDlg.h"
#include "GlobalFunc/FuncPath.h"
#include "SkinPPWTL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBatchModifyDlg 对话框




CBatchModifyDlg::CBatchModifyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBatchModifyDlg::IDD, pParent)
	,m_bIsHelpVisible(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_strFilePath = _T("");
}

void CBatchModifyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADDSTR, m_editAddStr);
	DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);
	DDX_Control(pDX, IDC_EDIT_SUFFIX, m_editSuffix);
	DDX_Control(pDX, IDC_COMBO_ADDPOS, m_combAddPos);
	DDX_Control(pDX, IDC_COMBO_SKIN, m_comboSkin);
}

BEGIN_MESSAGE_MAP(CBatchModifyDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BTN_GETPATH, &CBatchModifyDlg::OnBnClickedBtnGetpath)
	ON_BN_CLICKED(IDC_BTN_SUFFIXOK, &CBatchModifyDlg::OnBnClickedBtnSuffixok)
	ON_BN_CLICKED(IDC_BTN_SETFSUFIX, &CBatchModifyDlg::OnBnClickedBtnSetsuffix)
	ON_BN_CLICKED(IDC_BTN_START, &CBatchModifyDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_HELP, &CBatchModifyDlg::OnBnClickedBtnHelp)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_SKIN, &CBatchModifyDlg::OnCbnSelchangeComboSkin)
END_MESSAGE_MAP()


// CBatchModifyDlg 消息处理程序

BOOL CBatchModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
// 
	skinppLoadSkin("vladstudio.ssk");
	InitCombobox();
	CRect rectDlg;
	GetWindowRect(&rectDlg);
	CRect rectBtn;
	GetDlgItem(IDC_BTN_HELP)->GetWindowRect(&rectBtn);
	rectDlg.bottom = rectBtn.bottom + 20;
	MoveWindow(rectDlg);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBatchModifyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBatchModifyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBatchModifyDlg::OnBnClickedBtnGetpath()
{
	CString strOriginPath;
	GetDlgItemText(IDC_EDIT_PATH,strOriginPath);
	TCHAR szPath[MAX_PATH];     //存放选择的目录路径 
	ZeroMemory(szPath, sizeof(szPath));   

	BROWSEINFO bi;  
	memset(&bi,0,sizeof BROWSEINFO);
	bi.hwndOwner = this->m_hWnd;   
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;  
	bi.lpszTitle = _T("请选择路径");
	bi.ulFlags = 0;   
	bi.lpfn = NULL;   
	bi.lParam = 0;   
	bi.iImage = 0; 

	LPITEMIDLIST lpidl = SHBrowseForFolder(&bi);  
	if (lpidl)
	{
		SHGetPathFromIDList(lpidl, szPath);
		m_strFilePath.Format(_T("%s"), szPath);
		SetDlgItemText(IDC_EDIT_PATH,m_strFilePath);
	}
	if (!lpidl)
	{
		m_strFilePath = strOriginPath;
	}
}

void CBatchModifyDlg::OnBnClickedBtnSuffixok()
{
	GetDlgItem(IDC_EDIT_SUFFIX)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SETFSUFIX)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SUFFIXOK)->EnableWindow(FALSE);
}

void CBatchModifyDlg::OnBnClickedBtnSetsuffix()
{
	GetDlgItem(IDC_EDIT_SUFFIX)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SETFSUFIX)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SUFFIXOK)->EnableWindow(TRUE);
}

void CBatchModifyDlg::OnBnClickedBtnStart()
{
	CString strPath;
	CString strSuffix;
	GetDlgItemText(IDC_EDIT_PATH,strPath);
	GetDlgItemText(IDC_EDIT_ADDSTR,strSuffix);

	if (strPath == _T("")||strSuffix == _T(""))
	{
		MessageBox(_T("路径或字段为空！"),MB_OK);
		return ;
	}
	if(AfxMessageBox(_T("确定修改吗？"),MB_OKCANCEL)==IDOK)
	{
		GetModifyStruct(m_stModifyInfo);

		if (!FuncPath::IsExist(m_stModifyInfo.strPath))
		{
			CString strMessage;
			strMessage.Format(_T("文件夹\"%s\"不存在!"),m_stModifyInfo.strPath);
			MessageBox(strMessage);
			return ;
		}

			if (ModifyFileName())
			{
				AfxMessageBox(_T("修改完成！"));
			}

	}
}

BOOL CBatchModifyDlg::GetModifyStruct(struModifyInfo& stModifyInfo)
{
	CString strTemp = _T("");
	GetDlgItemText(IDC_EDIT_PATH,strTemp);
	stModifyInfo.strPath = strTemp;
	GetDlgItemText(IDC_EDIT_SUFFIX,strTemp);
	stModifyInfo.strSuffix = strTemp;
	GetDlgItemText(IDC_EDIT_ADDSTR,strTemp);
	stModifyInfo.strAddStr = strTemp;
	
	int index = m_combAddPos.GetCurSel();
	m_combAddPos.GetLBText(index,strTemp);
	stModifyInfo.strPos = strTemp;
	return TRUE;
}

BOOL CBatchModifyDlg::ModifyFileName()
{
	CFileFind finder;
	//CString strFullPath = m_stModifyInfo.strPath;
	CString strFilePath = m_stModifyInfo.strPath;
	char* chFullPath;
	CString strFileName;
	if (!FuncPath::IsExist(strFilePath))
	{
		CString strMessage;
		strMessage.Format(_T("路径:\"%s\"不存在!"),strFilePath);
		MessageBox(strMessage);
		return FALSE;
	}

	BOOL bWorking=finder.FindFile(strFilePath+_T("\\*.*")); 

	if(!bWorking)
	{
		AfxMessageBox(_T("目录为空!"));
		finder.Close();
		return FALSE;
	}
	while(bWorking)
	{ 
		bWorking = finder.FindNextFile(); 

		if(finder.IsDots())
			continue;
		if (finder.IsDirectory())
		{
			continue;
		}

		// 重命名
		strFilePath = finder.GetRoot();
		strFileName = finder.GetFileName();
		if (m_stModifyInfo.strPos == _T("文件名前"))
		{
			chFullPath = FuncPath::GetMultiByte( finder.GetFilePath());
			strFileName = m_stModifyInfo.strAddStr + strFileName;
			CString strFullPathNew = strFilePath + strFileName;
			char* chFullPathNew = FuncPath::GetMultiByte(strFullPathNew);
			rename(chFullPath,chFullPathNew);
		}
		if (m_stModifyInfo.strPos == _T("文件名后"))
		{
			chFullPath = FuncPath::GetMultiByte(finder.GetFilePath());
			int iIndex = strFileName.ReverseFind('.');
			strFileName.Insert(iIndex,m_stModifyInfo.strAddStr);
			CString strFullPathNew = strFilePath + strFileName;
			char* chFullPathNew = FuncPath::GetMultiByte(strFullPathNew);
			rename(chFullPath,chFullPathNew);
		}

	}
	finder.Close();
	return TRUE;
}

BOOL CBatchModifyDlg::InitCombobox()
{
	m_combAddPos.InsertString(0,_T("文件名前"));
	m_combAddPos.SetItemData(0,0);
	m_combAddPos.InsertString(1,_T("文件名后"));
	m_combAddPos.SetItemData(1,1);
	m_combAddPos.SetCurSel(0);

	int iIndex = 0;
	m_comboSkin.InsertString(iIndex,_T("简约"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("祥云"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("金属"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("Mac"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("Vista"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("XP经典"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("当前系统"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.SetCurSel(0);

	return TRUE;
}


void CBatchModifyDlg::OnBnClickedBtnHelp()
{
	CRect rect;
	GetWindowRect(&rect);

	if (!m_bIsHelpVisible)
	{
		rect.bottom += 150;
	}
	else
	{
		rect.bottom -= 150;;
	}
	MoveWindow(rect);
	m_bIsHelpVisible = !m_bIsHelpVisible;
}

void CBatchModifyDlg::OnDestroy()
{
	skinppRemoveSkin();
	skinppExitSkin();
	CDialog::OnDestroy();

}

void CBatchModifyDlg::OnCbnSelchangeComboSkin()
{
	skinppRemoveSkin();
	int iIndex = m_comboSkin.GetCurSel() + 1;
	switch (iIndex)
	{
	case 1:
		skinppLoadSkin("vladstudio.ssk");
		break;
	case 2:
		skinppLoadSkin("RisingDragon.ssk");
		break;
	case 3:
		skinppLoadSkin("UMskin.ssk");
		break;
	case 4:
		skinppLoadSkin("AquaOS.ssk");
		break;
	case 5:
		skinppLoadSkin("Vista.ssk");
		break;
	case 6:
		skinppLoadSkin("XP-Luna.ssk");
		break;
	case 7:
		break;
	default:
		break;
	}
	Invalidate();
}
