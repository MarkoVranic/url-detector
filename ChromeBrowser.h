#pragma once
#ifndef CHROME_BROWSER_H
#define CHROME_BROWSER_H

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>

#include "IBrowser.h"

class ChromeBrowser : public IBrowser {
public:
	ChromeBrowser(HWND hwnd, CComQIPtr<IUIAutomation> uia);

	std::wstring getCurrentURLUnsafe() const;
	std::wstring getCurrentURLSafe() const;
	std::wstring getCurrentBrowserName() const;

private:
	HWND my_hwnd;
	CComQIPtr<IUIAutomation> my_uia;
};

#endif //CHROME_BROWSER_H