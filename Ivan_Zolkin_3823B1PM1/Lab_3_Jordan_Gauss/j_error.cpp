#include "j_error.hpp"

j_error::j_error() = default;
j_error::j_error(const std::string& str) noexcept{		//������� ������ j_error � ���������� � ����� ������
	this->str = new char[str.length()+1];
	std::copy(str.begin(), str.end(), this->str);
	this->str[str.length()] = '\0';		//��� ����� ������� �� ���������� ��� ��� ���� � ��������� ��� �������
	}
j_error::~j_error() {
	delete[] str;
}
const char* j_error::what() const noexcept {	//������������ ����� ������
	return str;
}
