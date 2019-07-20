#pragma once
#ifndef IBROWSER_H
#define IBROWSER_H

#include <iostream>
#include <stdio.h>

class IBrowser {

public:
	virtual std::wstring getCurrentURLSafe() const = 0;
	virtual std::wstring getCurrentURLUnsafe() const = 0;
	virtual std::wstring getCurrentBrowserName() const = 0;

	virtual ~IBrowser() {}
};

#endif //IBROWSER_H
