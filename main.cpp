#include <Windows.h>
#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <memory>
#include <time.h>
#include "Common.h"
#include "BrowserBuilder.h"

class InputArgs
{
	bool m_isSafe;
	bool m_isDebug;
	int  m_sliceInterval;
public:
	InputArgs(int argc, char** argv)
		:m_isSafe(false),
		m_isDebug(false),
		m_sliceInterval(1)
	{
		std::vector<std::string> argStr;

		for (int i = 0; i < argc; ++i)
		{
			argStr.push_back(std::string(argv[i]));
		}

		for (auto& arg : argStr)
		{
			if (arg == "-safe")
			{
				m_isSafe = true;
			}
			if (arg == "-debug")
			{
				m_isDebug = true;
			}
			else if (arg.find("-slice=") == 0)
			{
				m_sliceInterval = std::stoi(arg.substr(std::string("-slice=").size()));
			}
		}

		return;
	}

	bool isSafe() const
	{
		return m_isSafe;
	}

	bool isDebug() const
	{
		return m_isDebug;
	}

	int sliceInterval() const
	{
		return m_sliceInterval;
	}

};


int main(int argc, char** argv)
{
	if (FAILED(CoInitialize(NULL)))
	{
		std::wcout << L"CoInitialize FAILED!" << std::endl;
		return -1;
	}

	InputArgs inputParams(argc, argv);

	CComQIPtr<IUIAutomation> uia;
	if (FAILED(uia.CoCreateInstance(CLSID_CUIAutomation)) || !uia)
	{
		std::wcout << L"UI Automation not created!" << std::endl;
		return -1;
	}

	while (true)
	{
		try {
				int start, end;

				HWND hwnd = NULL;
				std::unique_ptr<IBrowser> browserHandle(BrowserBuilder::createBrowser(hwnd, uia));

				start = clock();

				std::wstring url = inputParams.isSafe() ? browserHandle->getCurrentURLSafe() : browserHandle->getCurrentURLUnsafe();

				end = clock();
				double diffms = (end - start) / (CLOCKS_PER_SEC / 1000);
				std::wcout << browserHandle->getCurrentBrowserName() << " - " << url << " - " << diffms << std::endl;
		}
		catch (Err& err)
		{
			if (inputParams.isDebug())
			{
				std::wcout << "Error: " << err.message() << " on: " << err.file() << " " << err.function() << " " << err.line() << std::endl;
			}
		}
		catch(...)
		{
			if (inputParams.isDebug())
			{
				std::wcout << "Unknown Error!" << std::endl;
			}
		}
		Sleep(inputParams.sliceInterval() * 1000);
	}
	CoUninitialize();
	return 0;
}