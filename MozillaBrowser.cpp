#include "MozillaBrowser.h"
#include "Common.h"

MozillaBrowser::MozillaBrowser(HWND hwnd, CComQIPtr<IUIAutomation> uia)
	:my_hwnd(hwnd),
	my_uia(uia)
{
}

std::wstring MozillaBrowser::getCurrentURLSafe() const
{
	CComPtr<IUIAutomationElement> root;
	if (FAILED(my_uia->ElementFromHandle(my_hwnd, &root)) || !root)
		THROW_MESSAGE(ERR_NULL_ROOT, L"ROOT node is null!");

	CComPtr<IUIAutomationCondition> editCondition;

	my_uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(UIA_DocumentControlTypeId), &editCondition);

	CComPtr<IUIAutomationElement> edit;

	if (FAILED(root->FindFirst(TreeScope_Subtree, editCondition, &edit)) || !edit)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComVariant url;
	edit->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &url);
	std::wstring ws(url.bstrVal, SysStringLen(url.bstrVal));

	return ws;
}

std::wstring MozillaBrowser::getCurrentURLUnsafe() const
{
	CComPtr<IUIAutomationElement> root;
	if (FAILED(my_uia->ElementFromHandle(my_hwnd, &root)) || !root)
		THROW_MESSAGE(ERR_NULL_ROOT, L"ROOT node is null!");

	IUIAutomationTreeWalker* pControlWalker = nullptr;
	IUIAutomationElement* pNode = nullptr;

	my_uia->get_ControlViewWalker(&pControlWalker);
	if (pControlWalker == nullptr)
		THROW_MESSAGE(ERR_NULL_PTR, L"Control View Walker is null!");

	CComPtr<IUIAutomationCondition> toolBarCondition;

	my_uia->CreatePropertyCondition(UIA_NamePropertyId,
		CComVariant("Navigation Toolbar"), &toolBarCondition);

	if (FAILED(root->FindFirst(TreeScope_Children, toolBarCondition, &pNode)) || !pNode)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComPtr<IUIAutomationCondition> conditionComboBox;
	my_uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(0xC353), &conditionComboBox);

	if(pNode == nullptr)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	if (FAILED(pNode->FindFirst(TreeScope_Children, conditionComboBox, &pNode)) || !pNode)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");
	
	CComPtr<IUIAutomationCondition> conditionEdit;
	my_uia->CreatePropertyCondition(UIA_ControlTypePropertyId,
		CComVariant(0xC354), &conditionEdit);

	if (FAILED(pNode->FindFirst(TreeScope_Children, conditionEdit, &pNode)) || !pNode)
		THROW_MESSAGE(ERR_NULL_PTR, L"Node is null!");

	CComVariant url;
	pNode->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &url);
	std::wstring ws(url.bstrVal, SysStringLen(url.bstrVal));

	return ws;
}

std::wstring MozillaBrowser::getCurrentBrowserName() const
{
	return L"Mozilla Firefox";
}