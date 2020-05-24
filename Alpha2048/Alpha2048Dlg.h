
// Alpha2048Dlg.h: 头文件
//

#pragma once


// CAlpha2048Dlg 对话框
class CAlpha2048Dlg : public CDialogEx
{
// 构造
public:
	CAlpha2048Dlg(CWnd* pParent = nullptr);	// 标准构造函数
	CToolTipCtrl m_Tip;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ALPHA2048_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedNormal();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedExit();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedEndless();
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedDiss();
	afx_msg void OnBnClickedTran();
	afx_msg void OnBnClickedIron();
};
