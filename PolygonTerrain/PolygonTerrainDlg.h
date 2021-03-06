
// PolygonTerrainDlg.h : header file
//

#pragma once
#include <vector>

// CPolygonTerrainDlg dialog
class CPolygonTerrainDlg : public CDialog
{
// Construction
public:
	CPolygonTerrainDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_POLYGONTERRAIN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//    afx_msg void OnBnClickedOk();
//    afx_msg void OnBnClickedButton2();
//    afx_msg void OnStatic();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    void PrintPolygon(CPaintDC& dc, std::vector<POINT>& polygon, COLORREF crColor);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
private:
    std::vector<POINT> m_vecPolygon;
    std::vector<POINT> m_vecP1;
    std::vector<POINT> m_vecP2;
    std::vector<POINT> m_vecP3;
public:
    afx_msg void OnMenuPolygon1();
    afx_msg void OnMenuPolygon2();
    afx_msg void OnBnClickedButton2();
};
