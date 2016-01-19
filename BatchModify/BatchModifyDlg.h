
// BatchModifyDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

enum enumNameType
{
	NameType_Num    = 0,
	NameType_Date   = 1,
	NameType_Letter = 2
};

struct struModifyInfo
{
	CString strPath;         // �ļ���·��
	CString strSuffix;       // Ҫ�޸ĵ��ļ����ͣ���׺����
	CString strAddStr;       // Ҫ���ӵ��ֶ�
	CString strPos;          // �ֶ�Ҫ���ӵ�λ��
	enumNameType eNameType;  // �����ֱ������
	struModifyInfo()
	{
		strPath = _T("");
		strSuffix = _T("");
		strAddStr = _T("");
		strPos = _T("");
		eNameType = NameType_Num;
	}
};
// CBatchModifyDlg �Ի���
class CBatchModifyDlg : public CDialog
{
// ����
public:
	CBatchModifyDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BATCHMODIFY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CString m_strFilePath;
	BOOL InitCombobox();
public:
	afx_msg void OnBnClickedBtnGetpath();
	afx_msg void OnBnClickedBtnSuffixok();
	afx_msg void OnBnClickedBtnSetsuffix();
	afx_msg void OnBnClickedBtnStart();
private:
	CEdit m_editAddStr;
	CEdit m_editPath;
	CEdit m_editSuffix;
	CComboBox m_combAddPos;
	struModifyInfo m_stModifyInfo;
	bool m_bIsHelpVisible;
public:

	BOOL CBatchModifyDlg::GetModifyStruct(struModifyInfo& stModifyInfo);
	BOOL CBatchModifyDlg::ModifyFileName();

	afx_msg void OnBnClickedBtnHelp();
	afx_msg void OnDestroy();
private:
	CComboBox m_comboSkin;
public:
	afx_msg void OnCbnSelchangeComboSkin();
};
