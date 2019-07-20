#include "ChromeBrowser.h"
#include "Common.h"


ChromeBrowser::ChromeBrowser(HWND hwnd, CComQIPtr<IUIAutomation> uia)
	:my_hwnd(hwnd), 
	my_uia(uia)	
{
}

std::wstring ChromeBrowser::getCurrentURLSafe() const
{
	CComPtr<IUIAutomationElement> root;
	if (FAILED(my_uia->ElementFromHandle(my_hwnd, &root)) || !root)
	THROW_MESSAGE(ERR_NULL_ROOT, L"ROOT node is null!");

	CComPtr<IUIAutomationCondition> editCondition;

	my_uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(0xC354), &editCondition);

	CComPtr<IUIAutomationElement> edit;

	if (FAILED(root->FindFirst(TreeScope_Descendants, editCondition, &edit)) || !edit )
			THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComVariant url;
	edit->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &url);
	std::wstring ws(url.bstrVal, SysStringLen(url.bstrVal));

	return ws;
}

std::wstring ChromeBrowser::getCurrentURLUnsafe() const
{
	CComPtr<IUIAutomationElement> root;
	if (FAILED(my_uia->ElementFromHandle(my_hwnd, &root)) || !root)
		THROW_MESSAGE(ERR_NULL_ROOT, L"ROOT node is null!");

	IUIAutomationTreeWalker* pControlWalker = nullptr;
	IUIAutomationElement* pNode = nullptr;

	my_uia->get_ControlViewWalker(&pControlWalker);
	if (pControlWalker == nullptr)
		THROW_MESSAGE(ERR_NULL_PTR, L"Control View Walker is null!");

	pControlWalker->GetLastChildElement(root, &pNode);

	pControlWalker->GetLastChildElement(pNode, &pNode);
	pControlWalker->GetFirstChildElement(pNode, &pNode);
	pControlWalker->GetFirstChildElement(pNode, &pNode);
	pControlWalker->GetNextSiblingElement(pNode, &pNode);
	if (pNode == nullptr)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComPtr<IUIAutomationCondition> groupCondition;

	my_uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(0xC36A), &groupCondition);

	if (FAILED(pNode->FindFirst(TreeScope_Children, groupCondition, &pNode)) || !pNode)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComPtr<IUIAutomationCondition> editCondition;
	my_uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(0xC354), &editCondition);

	if (FAILED(pNode->FindFirst(TreeScope_Children, editCondition, &pNode)) || !pNode)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComVariant url;
	if (pNode == nullptr)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	pNode->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &url);
	std::wstring ws(url.bstrVal, SysStringLen(url.bstrVal));
	
	return ws;
}

std::wstring ChromeBrowser::getCurrentBrowserName() const
{
	return L"Google Chrome";
}