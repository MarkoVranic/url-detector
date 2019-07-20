#include "BrowserBuilder.h"
#include "ChromeBrowser.h"
#include "IEBrowser.h"
#include "MozillaBrowser.h"
#include "Common.h"


IBrowser* BrowserBuilder::createBrowser(HWND hwnd, CComQIPtr<IUIAutomation> uia)
{
	// Check for Firefox browser
	hwnd = FindWindowEx(0, hwnd, MOZILLA_WINDOW_ID, NULL);

	if (hwnd && IsWindowVisible(hwnd))
		return new MozillaBrowser(hwnd, uia);

	// Check for IE browser
	hwnd = FindWindowEx(0, hwnd, IE_WINDOW_ID, NULL);

	if (hwnd && IsWindowVisible(hwnd))
		return new IEBrowser(hwnd, uia);

	// Check for Chrome browser
	hwnd = FindWindowEx(0, hwnd, CHROME_WINDOW_ID, NULL);

	if (hwnd && IsWindowVisible(hwnd))
		return new ChromeBrowser(hwnd, uia);

	THROW_MESSAGE(ERR_NOT_IMPLEMENTED, L"Non known Browser detected");
}

