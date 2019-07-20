#include "IEBrowser.h"
#include "Common.h"


IEBrowser::IEBrowser(HWND hwnd, CComQIPtr<IUIAutomation> uia)
	:my_hwnd(hwnd),
	my_uia(uia)
{
}


std::wstring IEBrowser::getCurrentURLSafe() const
{
	CComPtr<IUIAutomationElement> root;
	if (FAILED(my_uia->ElementFromHandle(my_hwnd, &root)) || !root)
		THROW_MESSAGE(ERR_NULL_ROOT, L"ROOT node is null!");

	CComPtr<IUIAutomationCondition> editCondition;

	my_uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(0xC354), &editCondition);

	CComPtr<IUIAutomationElement> edit;

	if (FAILED(root->FindFirst(TreeScope_Subtree, editCondition, &edit)) || !edit)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComVariant url;
	edit->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &url);
	std::wstring ws(url.bstrVal, SysStringLen(url.bstrVal));

	return ws;
}

std::wstring IEBrowser::getCurrentURLUnsafe() const
{
	CComPtr<IUIAutomationElement> root;
	if (FAILED(my_uia->ElementFromHandle(my_hwnd, &root)) || !root)
		THROW_MESSAGE(ERR_NULL_ROOT, L"ROOT node is null!");

	IUIAutomationTreeWalker* pControlWalker = nullptr;
	IUIAutomationElement* pNode = nullptr;

	my_uia->get_ControlViewWalker(&pControlWalker);
	if (pControlWalker == nullptr)
		THROW_MESSAGE(ERR_NULL_PTR, L"Control View Walker is null!");

	pControlWalker->GetFirstChildElement(root, &pNode);
	pControlWalker->GetNextSiblingElement(pNode, &pNode);
	pControlWalker->GetFirstChildElement(pNode, &pNode);
	pControlWalker->GetNextSiblingElement(pNode, &pNode);
	pControlWalker->GetFirstChildElement(pNode, &pNode);
	pControlWalker->GetFirstChildElement(pNode, &pNode);

	if (pNode == nullptr)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComVariant url;
	pNode->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &url);
	std::wstring ws(url.bstrVal, SysStringLen(url.bstrVal));

	return ws;
}

std::wstring IEBrowser::getCurrentBrowserName() const
{
	return L"Internet Explorer";
}