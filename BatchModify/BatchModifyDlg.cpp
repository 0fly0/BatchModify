
// BatchModifyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BatchModify.h"
#include "BatchModifyDlg.h"
#include "GlobalFunc/FuncPath.h"
#include "SkinPPWTL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBatchModifyDlg �Ի���




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


// CBatchModifyDlg ��Ϣ�������

BOOL CBatchModifyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
// 
	skinppLoadSkin("vladstudio.ssk");
	InitCombobox();
	CRect rectDlg;
	GetWindowRect(&rectDlg);
	CRect rectBtn;
	GetDlgItem(IDC_BTN_HELP)->GetWindowRect(&rectBtn);
	rectDlg.bottom = rectBtn.bottom + 20;
	MoveWindow(rectDlg);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBatchModifyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBatchModifyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBatchModifyDlg::OnBnClickedBtnGetpath()
{
	CString strOriginPath;
	GetDlgItemText(IDC_EDIT_PATH,strOriginPath);
	TCHAR szPath[MAX_PATH];     //���ѡ���Ŀ¼·�� 
	ZeroMemory(szPath, sizeof(szPath));   

	BROWSEINFO bi;  
	memset(&bi,0,sizeof BROWSEINFO);
	bi.hwndOwner = this->m_hWnd;   
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szPath;  
	bi.lpszTitle = _T("��ѡ��·��");
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
		MessageBox(_T("·�����ֶ�Ϊ�գ�"),MB_OK);
		return ;
	}
	if(AfxMessageBox(_T("ȷ���޸���"),MB_OKCANCEL)==IDOK)
	{
		GetModifyStruct(m_stModifyInfo);

		if (!FuncPath::IsExist(m_stModifyInfo.strPath))
		{
			CString strMessage;
			strMessage.Format(_T("�ļ���\"%s\"������!"),m_stModifyInfo.strPath);
			MessageBox(strMessage);
			return ;
		}

			if (ModifyFileName())
			{
				AfxMessageBox(_T("�޸���ɣ�"));
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
		strMessage.Format(_T("·��:\"%s\"������!"),strFilePath);
		MessageBox(strMessage);
		return FALSE;
	}

	BOOL bWorking=finder.FindFile(strFilePath+_T("\\*.*")); 

	if(!bWorking)
	{
		AfxMessageBox(_T("Ŀ¼Ϊ��!"));
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

		// ������
		strFilePath = finder.GetRoot();
		strFileName = finder.GetFileName();
		if (m_stModifyInfo.strPos == _T("�ļ���ǰ"))
		{
			chFullPath = FuncPath::GetMultiByte( finder.GetFilePath());
			strFileName = m_stModifyInfo.strAddStr + strFileName;
			CString strFullPathNew = strFilePath + strFileName;
			char* chFullPathNew = FuncPath::GetMultiByte(strFullPathNew);
			rename(chFullPath,chFullPathNew);
		}
		if (m_stModifyInfo.strPos == _T("�ļ�����"))
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
	m_combAddPos.InsertString(0,_T("�ļ���ǰ"));
	m_combAddPos.SetItemData(0,0);
	m_combAddPos.InsertString(1,_T("�ļ�����"));
	m_combAddPos.SetItemData(1,1);
	m_combAddPos.SetCurSel(0);

	int iIndex = 0;
	m_comboSkin.InsertString(iIndex,_T("��Լ"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("����"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("����"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("Mac"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("Vista"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("XP����"));
	m_comboSkin.SetItemData(iIndex,iIndex++);
	m_comboSkin.InsertString(iIndex,_T("��ǰϵͳ"));
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
