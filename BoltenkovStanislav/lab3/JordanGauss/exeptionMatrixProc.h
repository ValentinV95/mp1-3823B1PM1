#pragma once
#include <iostream>
#include <string>

//��� ������ 1 - ������� ��������� ������������ �� ���������� �������
//��� ������ 2 - ���������� ����� � �������� �� ���������
//��� ������ 3 - �� �������� ����� �������� ������� �.� ������������ ����� 0
//��� ������ 4 - �� �������� ����������� �������,�.� ����������� �� �����������

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