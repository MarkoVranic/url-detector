#pragma once
#ifndef BROWSER_BUILDER_H
#define BROWSER_BUILDER_H

#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>

#include "IBrowser.h"

class BrowserBuilder {
public:
	static IBrowser* createBrowser(HWND hwnd, CComQIPtr<IUIAutomation> uia);
};

#endif //BROWSER_BUILDER_H
