#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <iostream>
#include <stdio.h>
#include <Windows.h>
#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>

#define MOZILLA_WINDOW_ID				L"MozillaWindowClass"
#define CHROME_WINDOW_ID				L"Chrome_WidgetWin_1"
#define IE_WINDOW_ID				    L"IEFrame"


enum ErrCode : int
{
	//----------------------------------------------------
	// General return codes
	ERR_OK = 0,									
	ERR_UNKNOWN = 100,
	ERR_UIA_INIT,
	ERR_NULL_ROOT,
	ERR_NULL_PTR,
	ERR_NOT_IMPLEMENTED
};

class Err
{
	ErrCode			m_ErrCode;					// error code
	const char*		m_Function;					// name of function
	const char*		m_File;						// file name
	int				m_Line;						// line number
	long			m_Arg;						// optional int argument related to cause of error
	std::wstring    m_Message;					// optional text message
public:
	Err(ErrCode errCode, const char* file, const char* function, int line, long arg, const std::wstring& message = L"")
		:m_Function(function),
		m_Line(line),
		m_Arg(arg),
		m_ErrCode(errCode),
		m_File(file),
		m_Message(message)
	{
	}

	Err(const Err& err)
		:m_Function(err.m_Function),
		m_Line(err.m_Line),
		m_Arg(err.m_Arg),
		m_ErrCode(err.m_ErrCode),
		m_File(err.m_File),
		m_Message(err.m_Message)
	{
	}

	inline int line() const throw()
	{
		return this->m_Line;
	}

	inline const char* function() const throw()
	{
		return this->m_Function;
	}

	inline const char* file() const throw()
	{
		return this->m_File;
	}

	inline ErrCode code() const throw()
	{
		return this->m_ErrCode;
	}

	inline const std::wstring& message() const throw()
	{
		return this->m_Message;
	}
};

	
#define THROW_ARG(errCode, argument) throw Err(errCode, __FILE__, __FUNCTION__, __LINE__, argument)
#define THROW(errCode) throw Err(errCode, __FILE__, __FUNCTION__, __LINE__, 0)
#define THROW_MESSAGE(errCode, message) throw Err(errCode, __FILE__, __FUNCTION__, __LINE__, 0, message)

#endif //COMMON_H
