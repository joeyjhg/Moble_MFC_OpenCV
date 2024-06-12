
// Moble_MFC_OpenCVDlg.h: 헤더 파일
//

#pragma once
#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

// CMobleMFCOpenCVDlg 대화 상자
class CMobleMFCOpenCVDlg : public CDialogEx
{
	Mat Resultimg;
	std::vector<Mat> Resultimgs;
	int sigma = 1;
	CFont m_font;
// 생성입니다.
public:
	CMobleMFCOpenCVDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MOBLE_MFC_OPENCV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedShowimage();
	afx_msg void DisplayImage(cv::Mat& origin, CStatic& m_pic);
	CStatic m_pic;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CStatic m_pic_result;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	CString m_strInfo;
	afx_msg void AddInfo(const CString& text);
	afx_msg void OnBnClickedButton5();
};
