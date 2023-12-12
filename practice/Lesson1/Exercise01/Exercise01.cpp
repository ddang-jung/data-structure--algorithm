#include <algorithm>
#include <iostream>
#include <sstream>

template <typename T>
class dynamic_array {
	T		*_data;
	size_t	_n;

	public:
		// constructor
		dynamic_array(int n) {
			this->_n = n;
			this->_data = new T[n];
		}
		
		// copy constructor
		dynamic_array(const dynamic_array<T> &other) {
			this->_n = other._n;
			this->_data = new T[_n];

			for (int i = 0; i < _n; i++)
				this->_data[i] = other._data[i];
		}

		// destructor
		~dynamic_array() {
			delete [] this->_data;
		}

		// overload operator[] and at()
		T		&operator[](int index) {
			return this->_data[index];
		}
		const T	&operator[](int index) const {
			return this->_data[index];
		}
		T		&at(int index) {
			if (index < this->_n)
				return this->_data[index];
			throw "Index out of range";
		}

		// implement size()
		size_t	size() const {
			return this->_n;
		}

		// overload begin() end()
		T		*begin() { return this->_data; }
		const T	*begin() const { return this->_data; }
		T		*end() { return this->_data + _n; }
		const T	*end() const { return this->_data + _n; }

		// overload operator+
		friend dynamic_array<T>	operator+(const dynamic_array<T> &lhs, dynamic_array<T> &rhs) {
			dynamic_array<T> result(lhs.size() + rhs.size());
			std::copy(lhs.begin(), lhs.end(), result.begin());
			std::copy(rhs.begin(), rhs.end(), result.begin() + lhs.size());

			return result;
		}

		// convert elements in _data to string
		std::string	to_string(const std::string &sep = ", ") {
			if (this->_n == 0)
				return "";

			std::ostringstream	os;
			os << this->_data[0];

			for (int i = 1; i < this->_n; i++)
				os << sep << this->_data[i];

			return os.str();
		}
};

// implement student structure and operator<<
struct student {
	std::string	name;
	int			standard;
};

std::ostream	&operator<<(std::ostream &os, const student &s) {
	return (os << "[" << s.name << ", " << s.standard << "]");
}

int main()
{
	int nStudents;
	std::cout << "1반 학생 수를 입력하세요: ";
	std::cin >> nStudents;

	dynamic_array<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++)
	{
		std::string name;
		int standard;
		std::cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
		std::cin >> name >> standard;
		student tmp = {name, standard};
		class1[i] = tmp;
	}

	// 배열 크기보다 큰 인덱스의 학생에 접근
	try
	{
		// 아래 주석을 해제하면 프로그램이 비정상 종료합니다.
		// class1[nStudents] = student {"John", 8}; // 예상할 수 없는 동작

		student	tmp = {"John", 8};
		class1.at(nStudents) = tmp; // 예외 발생
	}
	catch (...)
	{
		std::cout << "예외 발생!" << std::endl;
	}

	// 깊은 복사
	auto class2 = class1;
	std::cout << "1반을 복사하여 2반 생성: " << class2.to_string() << std::endl;

	// 두 학급을 합쳐서 새로운 큰 학급을 생성
	auto class3 = class1 + class2;
	std::cout << "1반과 2반을 합쳐 3반 생성 : " << class3.to_string() << std::endl;

	return 0;
}
