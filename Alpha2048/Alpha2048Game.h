#pragma once


// Alpha2048Game 对话框

class Alpha2048Game : public CDialogEx
{
	DECLARE_DYNAMIC(Alpha2048Game)

public:
	Alpha2048Game(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Alpha2048Game();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Alpha2048Game };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	void StartGame();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
