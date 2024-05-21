#include "j_error.hpp"

j_error::j_error() = default;
j_error::j_error(const std::string& str) noexcept{		//Создаем обьект j_error с сообщением о нашей ошибке
	this->str = new char[str.length()+1];
	std::copy(str.begin(), str.end(), this->str);
	this->str[str.length()] = '\0';		//Без этого строчка не закончится там где надо и выведутся еще символы
	}
j_error::~j_error() {
	delete[] str;
}
const char* j_error::what() const noexcept {	//переписываем показ ошибки
	return str;
}
