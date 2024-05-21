#pragma once
#include <iostream>

class j_error : public std::exception {
public:
	j_error();
	j_error(const std::string& str) noexcept;
	~j_error();
	virtual const char* what() const noexcept;
	
private:
	char* str;
};

