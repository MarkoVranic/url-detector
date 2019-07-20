#pragma once
#ifndef MOZILLA_BROWSER_H
#define MOZILLA_BROWSER_H

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>

#include "IBrowser.h"

class MozillaBrowser : public IBrowser {
public:
	MozillaBrowser(HWND hwnd, CComQIPtr<IUIAutomation> uia);

	std::wstring getCurrentURLUnsafe() const;
	std::wstring getCurrentURLSafe() const;
	std::wstring getCurrentBrowserName() const;

private:
	HWND my_hwnd;
	CComQIPtr<IUIAutomation> my_uia;
};

#endif //MOZILLA_BROWSER_H
