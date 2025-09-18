
// imageProView.h: CimageProView 클래스의 인터페이스
//

#pragma once


class CimageProView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CimageProView() noexcept;
	DECLARE_DYNCREATE(CimageProView)

// 특성입니다.
public:
	CimageProDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CimageProView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelDiv();
	afx_msg void OnBinary();
	afx_msg void OnExam1();
	afx_msg void OnExam2();
	afx_msg void OnExam3();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageMinus();
	afx_msg void OnPixelTwoImageMultiple();
	afx_msg void OnPixelTwoImageDiv();
	afx_msg void OnHistoView();
	afx_msg void OnHistoStrech();
	afx_msg void OnHistoEq();
	afx_msg void OnMirrorImage();
	afx_msg void OnFlipImage();
	afx_msg void OnZoomin1();
	afx_msg void OnCopyInter();
	afx_msg void OnZoomin3();
	afx_msg void OnZoomout();
	afx_msg void OnRotate();
};

#ifndef _DEBUG  // imageProView.cpp의 디버그 버전
inline CimageProDoc* CimageProView::GetDocument() const
   { return reinterpret_cast<CimageProDoc*>(m_pDocument); }
#endif

