
// BatchModifyDlg.h : 头文件
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
	CString strPath;         // 文件夹路径
	CString strSuffix;       // 要修改的文件类型（后缀名）
	CString strAddStr;       // 要增加的字段
	CString strPos;          // 字段要增加的位置
	enumNameType eNameType;  // 按何种编号命名
	struModifyInfo()
	{
		strPath = _T("");
		strSuffix = _T("");
		strAddStr = _T("");
		strPos = _T("");
		eNameType = NameType_Num;
	}
};
// CBatchModifyDlg 对话框
class CBatchModifyDlg : public CDialog
{
// 构造
public:
	CBatchModifyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_BATCHMODIFY_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
