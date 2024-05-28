#include "exeptionMatrixProc.h"


const char* exeptionMatrixProc::what() const noexcept
{
	return err.c_str();
}

exeptionMatrixProc::exeptionMatrixProc()
{
	err = nullptr;
	codeErr = 0;
}

exeptionMatrixProc::exeptionMatrixProc(const std::string& err, const int& codeErr)
{
	this->err = err;
	this->codeErr = codeErr;
}

exeptionMatrixProc::~exeptionMatrixProc()
{
	
}

int exeptionMatrixProc::getCodeError() const noexcept
{
	return codeErr;
}