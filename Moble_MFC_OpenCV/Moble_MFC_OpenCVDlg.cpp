
// Moble_MFC_OpenCVDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Moble_MFC_OpenCV.h"
#include "Moble_MFC_OpenCVDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMobleMFCOpenCVDlg 대화 상자



CMobleMFCOpenCVDlg::CMobleMFCOpenCVDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MOBLE_MFC_OPENCV_DIALOG, pParent)
	, m_strInfo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMobleMFCOpenCVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CAM_PICTURE, m_pic);
	DDX_Control(pDX, IDC_CAM_PICTURE2, m_pic_result);
	DDX_Text(pDX, IDC_EDIT_INFO, m_strInfo);
}

BEGIN_MESSAGE_MAP(CMobleMFCOpenCVDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDShowImage, &CMobleMFCOpenCVDlg::OnBnClickedShowimage)
	ON_BN_CLICKED(IDC_BUTTON1, &CMobleMFCOpenCVDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMobleMFCOpenCVDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMobleMFCOpenCVDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMobleMFCOpenCVDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CMobleMFCOpenCVDlg::OnBnClickedButton5)
END_MESSAGE_MAP()


// CMobleMFCOpenCVDlg 메시지 처리기

BOOL CMobleMFCOpenCVDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CString fontName = _T("굴림"); // CString 객체를 사용하여 "굴림" 문자열 설정

	m_font.CreatePointFont(180, fontName); // CString 객체를 매개변수로 사용
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_font);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMobleMFCOpenCVDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMobleMFCOpenCVDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMobleMFCOpenCVDlg::OnBnClickedShowimage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//char szFilter[] = "Image (*.BMP, *.GIF, *.JPG, *.PNG) | *.BMP;*.GIF;*.JPG;*.PNG;*.bmp;*.gif;*.jpg;*.png | All Files(*.*)|*.*||";
    //CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, AfxGetMainWnd());
    static TCHAR BASED_CODE szFilter[] = _T("이미지 파일(*.BMP, *.GIF, *.JPG) | *.BMP;*.GIF;*.JPG;*.bmp;*.jpg;*.gif |모든파일(*.*)|*.*||");

    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
    if (dlg.DoModal() == IDOK)
    {
        CString pathName = dlg.GetPathName();

        CT2CA pszConvertedAnsiString(pathName);

        Mat frame = cv::imread(std::string(pszConvertedAnsiString));

        // 확인을 위해 이미지가 로드되었는지 출력
        if (!frame.empty()) {
            MessageBox(_T("이미지가 성공적으로 로드되었습니다."), _T("성공"), MB_OK | MB_ICONINFORMATION);
			Resultimg = frame;
        }
        else {
            MessageBox(_T("이미지를 로드하는 데 문제가 발생했습니다."), _T("오류"), MB_OK | MB_ICONERROR);
        }


		DisplayImage(frame,m_pic);
    }
}
void CMobleMFCOpenCVDlg::DisplayImage(cv::Mat& origin, CStatic& m_pic) {
    CPaintDC dc(this);
    CRect rect;
    m_pic.GetClientRect(&rect); // 픽쳐 컨트롤의 크기를 얻습니다.

    CDC* pDC = m_pic.GetDC();
    CImage mfcImg;
    cv::Mat outImg;

    cv::flip(origin, outImg, 0); // 이미지를 뒤집습니다.

    // 흑백 이미지인 경우 채널을 3으로 변경합니다.
    if (outImg.channels() == 1) {
        cv::cvtColor(outImg, outImg, cv::COLOR_GRAY2BGR);
    }

    // 이미지의 크기를 조정합니다.
    cv::resize(outImg, outImg, cv::Size(rect.Width(), rect.Height()), 0, 0, cv::INTER_AREA);

    // 이미지 데이터를 CImage로 변환합니다.
    mfcImg.Create(outImg.cols, outImg.rows, 24);
    BITMAPINFO bitInfo = { {sizeof(BITMAPINFOHEADER), outImg.cols, outImg.rows, 1, 24}, 0 };

    pDC->SetStretchBltMode(HALFTONE);
    StretchDIBits(mfcImg.GetDC(), 0, 0, outImg.cols, outImg.rows, 0, 0, outImg.cols, outImg.rows, outImg.data, &bitInfo, DIB_RGB_COLORS, SRCCOPY);

    // 화면에 이미지를 출력합니다.
    mfcImg.BitBlt(*pDC, (rect.Width() - outImg.cols) / 2 + rect.left, (rect.Height() - outImg.rows) / 2 + rect.top);
    mfcImg.ReleaseDC();
    outImg.release();
}

void CMobleMFCOpenCVDlg::OnBnClickedButton1()
{
	if (Resultimg.empty())
		return;
	//블러링
	Resultimgs.push_back(Resultimg.clone()); // 현재 이미지를 벡터에 복사하여 저장
	Mat kernel = Mat(5, 5, CV_32F, Scalar(1 / 25.0));
	filter2D(Resultimg, Resultimg, -1, kernel);
	DisplayImage(Resultimg, m_pic_result);
	AddInfo(_T("블러링/"));
}


void CMobleMFCOpenCVDlg::OnBnClickedButton2()
{
	if (Resultimg.empty())
		return;
	// 저장할 이미지 파일의 필터 설정
	TCHAR szFilters[] = _T("JPEG (*.jpg)|*.jpg|Bitmap (*.bmp)|*.bmp|All Files (*.*)|*.*||");

	// 저장 대화상자 초기화
	CFileDialog dlg(FALSE, _T("jpg"), _T("*.jpg"), OFN_FILEMUSTEXIST | OFN_HIDEREADONLY, szFilters);

	// 대화상자를 표시하고 사용자가 파일을 선택하면
	if (dlg.DoModal() == IDOK)
	{
		CString pathName = dlg.GetPathName(); // 사용자가 선택한 경로와 파일 이름
		CT2CA pszConvertedAnsiString(pathName); // CString을 std::string으로 변환

		// OpenCV의 imwrite 함수를 사용하여 이미지 저장
		if (!cv::imwrite(std::string(pszConvertedAnsiString), Resultimg)) // Resultimg는 저장할 Mat 객체
		{
			MessageBox(_T("이미지 저장에 실패했습니다."), _T("오류"), MB_OK | MB_ICONERROR);
		}
		else
		{
			MessageBox(_T("이미지가 성공적으로 저장되었습니다."), _T("성공"), MB_OK | MB_ICONINFORMATION);
		}
	}
}



void CMobleMFCOpenCVDlg::OnBnClickedButton3()
{
	if (Resultimg.empty())
		return;
	//샤프닝
	Resultimgs.push_back(Resultimg.clone()); // 현재 이미지를 벡터에 복사하여 저장
	Mat blurred;
	GaussianBlur(Resultimg, blurred, Size(), sigma++);
	float alpha = 1.f;
	Resultimg = (1 + alpha) * Resultimg - alpha * blurred;
	DisplayImage(Resultimg, m_pic_result);
	AddInfo(_T("샤프닝/"));
}


void CMobleMFCOpenCVDlg::OnBnClickedButton4()
{
	if (Resultimg.empty())
		return;
	//양방향 필터
	Resultimgs.push_back(Resultimg.clone()); // 현재 이미지를 벡터에 복사하여 저장
	Mat result;
	bilateralFilter(Resultimg, result, 10, 50, 50);
	Resultimg = result;
	DisplayImage(result, m_pic_result);
	AddInfo(_T("양방향 필터/"));

}

void CMobleMFCOpenCVDlg::AddInfo(const CString& text)
{
	UpdateData();
	m_strInfo.Append(text);
	UpdateData(false);
}


void CMobleMFCOpenCVDlg::OnBnClickedButton5()
{
	// 결과 이미지 벡터가 비어 있는지 확인
	if (Resultimgs.empty())
		return;

	// 마지막으로 저장된 이미지를 가져와서 디스플레이
	Mat lastImage = Resultimgs.back();
	DisplayImage(lastImage, m_pic_result);

	// 벡터에서 마지막 이미지 삭제
	Resultimgs.pop_back();

	// 작업 정보 업데이트
	// 마지막 '/' 문자의 위치를 찾음
	int lastSlashPos = m_strInfo.ReverseFind(_T('/'));
	if (lastSlashPos != -1) // '/'가 존재하는 경우
	{
		// 마지막 '/' 문자 이전의 '/' 문자의 위치를 찾음
		int secondLastSlashPos = m_strInfo.Left(lastSlashPos).ReverseFind(_T('/'));
		if (secondLastSlashPos != -1)
		{
			// 두 번째로 마지막 '/' 문자 이전까지의 문자열을 새로운 작업 정보로 설정
			m_strInfo = m_strInfo.Left(secondLastSlashPos + 1);
		}
		else
		{
			// '/' 문자가 하나만 있는 경우, 모든 작업 정보를 초기화
			m_strInfo.Empty();
		}
	}

	// 작업 정보 업데이트
	UpdateData(FALSE);
}


