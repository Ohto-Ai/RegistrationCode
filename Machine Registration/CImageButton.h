#pragma once

#ifndef _IMAGEBUTTON_H_
#define _IMAGEBUTTON_H_

#include "CPng.hpp"

namespace thatboy
{
	namespace mfc {

		// CImageButton

		class CImageButton : public CButton
		{
			DECLARE_DYNAMIC(CImageButton)

		public:
			CImageButton();
			virtual ~CImageButton();
		protected:
			DECLARE_MESSAGE_MAP()
			CPng m_bnImageU;
			CPng m_bnImageD;
			CPng m_bnImageF;
			CPng m_bnImageX;

			BOOL m_bOver;
			BOOL m_bTracking;

		public:
			/*
				����PNGͼ���ļ�
				pszFileName �ļ���
				size2cont ��С��������
				nImageNum ͼ������
				cAlphaThreshold ͸��ɫ��ֵ
			*/
			void LoadImagesFromFile(LPCTSTR pszFileName, bool bSizeToCont = true, int nImageNum = 4, BYTE cAlphaThreshold = 1);

			/*
				����PNGͼ����Դ
				pszResourceName ��Դ����
				size2cont ��С��������
				nImageNum ͼ������
				cAlphaThreshold ͸��ɫ��ֵ
				lpImageResType ��Դ����
			*/
			void LoadImagesFromResource(LPCTSTR pszResourceName, bool bSizeToCont = true, int nImageNum = 4, BYTE cAlphaThreshold = 1, LPCTSTR lpImageResType = TEXT("PNG"));

			/*
				����PNGͼ����Դ
				nReourceID ��ԴID
				size2cont ��С��������
				nImageNum ͼ������
				cAlphaThreshold ͸��ɫ��ֵ
				lpImageResType ��Դ����
			*/
			void LoadImagesFromResource(UINT nReourceID, bool bSizeToCont = true, int nImageNum = 4, BYTE cAlphaThreshold = 1, LPCTSTR lpImageResType = TEXT("PNG"));

			/*
				Ӧ��PNGͼ��
				wholeImage Pngͼ��
				size2cont ��С��������
				nImageNum ͼ������
				cAlphaThreshold ͸��ɫ��ֵ
			*/
			void ApplyPngImages(const CPng& wholeImage, CRect usedRect = CRect(), bool bSizeToCont = true, int nImageNum = 4, BYTE cAlphaThreshold = 1);

			BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, UINT nImageID = NULL);
			virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
			afx_msg void OnMouseMove(UINT nFlags, CPoint point);
			afx_msg void OnMouseLeave();
			afx_msg void OnMouseHover(UINT nFlags, CPoint point);
			afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
		};
	}
}

#endif // !_IMAGEBUTTON_H_