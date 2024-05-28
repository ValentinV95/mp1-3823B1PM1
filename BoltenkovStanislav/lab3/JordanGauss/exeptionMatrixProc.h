#pragma once
#include <iostream>
#include <string>

//код ошибки 1 - попытка вычислить определитель не квадратной матрицы
//код ошибки 2 - количество строк в матрицах не совпадает
//код ошибки 3 - не возможно найти обратную матрицу т.к определитель равен 0
//код ошибки 4 - не возможно перемножить матрицы,т.к размерности не соотносятся

class exeptionMatrixProc : public std::exception
{
private:
	std::string err;
	int codeErr;
public:
	exeptionMatrixProc();
	exeptionMatrixProc(const std::string& err, const int& codeErr);
	~exeptionMatrixProc();

	virtual const char* what() const noexcept override;
	int getCodeError() const noexcept;

};