﻿
// imageProView.cpp: CimageProView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "imagePro.h"
#endif

#include "imageProDoc.h"
#include "imageProView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CimageProView

IMPLEMENT_DYNCREATE(CimageProView, CScrollView)

BEGIN_MESSAGE_MAP(CimageProView, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CimageProView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_PIXEL_ADD, &CimageProView::OnPixelAdd)
	ON_COMMAND(ID_Pixel_Sub, &CimageProView::OnPixelSub)
	ON_COMMAND(ID_PIXEL_MUL, &CimageProView::OnPixelMul)
	ON_COMMAND(ID_PIXEL_DIV, &CimageProView::OnPixelDiv)
	ON_COMMAND(ID_BINARY, &CimageProView::OnBinary)
	ON_COMMAND(ID_EXAM1, &CimageProView::OnExam1)
	ON_COMMAND(ID_EXAM2, &CimageProView::OnExam2)
	ON_COMMAND(ID_Exam3, &CimageProView::OnExam3)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CimageProView::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_MINUS, &CimageProView::OnPixelTwoImageMinus)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_Multiple, &CimageProView::OnPixelTwoImageMultiple)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_DIV, &CimageProView::OnPixelTwoImageDiv)
	ON_COMMAND(ID_HISTO_VIEW, &CimageProView::OnHistoView)
	ON_COMMAND(ID_HISTO_STRECH, &CimageProView::OnHistoStrech)
	ON_COMMAND(ID_HISTO_EQ, &CimageProView::OnHistoEq)
	ON_COMMAND(ID_MIRROR_IMAGE, &CimageProView::OnMirrorImage)
	ON_COMMAND(ID_FLIP_IMAGE, &CimageProView::OnFlipImage)
	ON_COMMAND(ID_ZOOMIN_1, &CimageProView::OnZoomin1)
	ON_COMMAND(ID_COPY_INTER, &CimageProView::OnCopyInter)
	ON_COMMAND(ID_ZOOMIN_3, &CimageProView::OnZoomin3)
	ON_COMMAND(ID_ZOOMOUT, &CimageProView::OnZoomout)
	ON_COMMAND(ID_ROTATE, &CimageProView::OnRotate)
	ON_COMMAND(ID_BLURRING, &CimageProView::OnBlurring)
	ON_COMMAND(ID_SHARPNING, &CimageProView::OnSharpning)
	ON_COMMAND(ID_PREWITT, &CimageProView::OnPrewitt)
	ON_COMMAND(ID_ROBERTS, &CimageProView::OnRoberts)
	ON_COMMAND(ID_SOBEL, &CimageProView::OnSobel)
	ON_COMMAND(ID_LAPLACIAN, &CimageProView::OnLaplacian)
END_MESSAGE_MAP()

// CimageProView 생성/소멸

CimageProView::CimageProView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CimageProView::~CimageProView()
{
}

BOOL CimageProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CimageProView 그리기

void CimageProView::OnDraw(CDC* pDC)
{
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	for (int y = 0; y < 256; y++)
		for (int x = 0; x < 256; x++)
			pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][x],
				pDoc->InputImg[y][x],
				pDoc->InputImg[y][x]));

	for (int y = 0; y < 512; y++)
		for (int x = 0; x < 512; x++)
			pDC->SetPixel(x+300, y, RGB(pDoc->ResultImg[y][x],
				pDoc->ResultImg[y][x],
				pDoc->ResultImg[y][x]));

	for (int y = 0; y < 256; y++)
		for (int x = 0; x < 256; x++)
			pDC->SetPixel(x, y+300, RGB(pDoc->InputImg2[y][x],
				pDoc->InputImg2[y][x],
				pDoc->InputImg2[y][x]));
}

void CimageProView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = 1024;
	sizeTotal.cy = 768;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CimageProView 인쇄


void CimageProView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CimageProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CimageProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CimageProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CimageProView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CimageProView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CimageProView 진단

#ifdef _DEBUG
void CimageProView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CimageProView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CimageProDoc* CimageProView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CimageProDoc)));
	return (CimageProDoc*)m_pDocument;
}
#endif //_DEBUG


// CimageProView 메시지 처리기

void CimageProView::OnPixelAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelAdd();

	Invalidate(FALSE);
}

void CimageProView::OnPixelSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelSub();

	Invalidate(FALSE);
}

void CimageProView::OnPixelMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelMul();

	Invalidate(FALSE);
}

void CimageProView::OnPixelDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->PixelDiv();

	Invalidate(FALSE);
}

void CimageProView::OnBinary()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Binary();

	Invalidate(FALSE);
}

void CimageProView::OnExam1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Exam1();

	Invalidate(FALSE);
}

void CimageProView::OnExam2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Exam2();

	Invalidate(FALSE);
}

void CimageProView::OnExam3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Exam3();

	Invalidate(FALSE);
}

void CimageProView::OnPixelTwoImageAdd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Two_Image_Add();

	Invalidate(FALSE);
}

void CimageProView::OnPixelTwoImageMinus()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Two_Image_Minus();

	Invalidate(FALSE);
}

void CimageProView::OnPixelTwoImageMultiple()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Two_Image_Multiple();

	Invalidate(FALSE);
}


void CimageProView::OnPixelTwoImageDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Two_Image_Div();

	Invalidate(FALSE);
}

void CimageProView::OnHistoView()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Histogram();

	Invalidate(FALSE);
}

void CimageProView::OnHistoStrech()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Histo_Strech();

	Invalidate(FALSE);
}

void CimageProView::OnHistoEq()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Histo_EQ();

	Invalidate(FALSE);
}

void CimageProView::OnMirrorImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Mirror();

	Invalidate(FALSE);
}

void CimageProView::OnFlipImage()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Flip();

	Invalidate(FALSE);
}

void CimageProView::OnZoomin1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->ZoomIn_1();

	Invalidate(FALSE);
}

void CimageProView::OnCopyInter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->ZoomIn_2();

	Invalidate(FALSE);
}

void CimageProView::OnZoomin3()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->ZoomIn_3();

	Invalidate(FALSE);
}

void CimageProView::OnZoomout()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->ZoomOut();

	Invalidate(FALSE);
}

void CimageProView::OnRotate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Rotate();

	Invalidate(FALSE);
}

void CimageProView::OnBlurring()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Blurring();

	Invalidate(FALSE);
}

void CimageProView::OnSharpning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Sharpning();

	Invalidate(FALSE);
}

void CimageProView::OnPrewitt()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Prewitt();

	Invalidate(FALSE);
}

void CimageProView::OnRoberts()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Roberts();

	Invalidate(FALSE);
}

void CimageProView::OnSobel()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Sobel();

	Invalidate(FALSE);
}

void CimageProView::OnLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CimageProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->Laplacian();

	Invalidate(FALSE);
}
