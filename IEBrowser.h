#pragma once
#ifndef IE_BROWSER_H
#define IE_BROWSER_H

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>

#include "IBrowser.h"

class IEBrowser : public IBrowser {
public:
	IEBrowser(HWND hwnd, CComQIPtr<IUIAutomation> uia);

	std::wstring getCurrentURLUnsafe() const;
	std::wstring getCurrentURLSafe() const;
	std::wstring getCurrentBrowserName() const;

private:
	HWND my_hwnd;
	CComQIPtr<IUIAutomation> my_uia;
};

#endif //IE_BROWSER_H
