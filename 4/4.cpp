#include <iostream>

template<typename T> void input(T array[8]) {
	std::cout << "Enter numbers:" << std::endl;
	for (int i = 0; i < 8; ++i) {
		std::cin >> array[i];
	}
}

template<typename T> T average(T array[8]) {
	std::cout << "Simple average:" << std::endl;
	T summ = 0;
	T average = 0;
	for (int i = 0; i < 8; ++i) {
		summ += array[i];
	}
	return average = summ / 8;

}

int main() {
	int iarr[8];
	double darr[8];
	float farr[8];

	std::cout << "int" << std::endl;
	input(iarr);
	std::cout << average(iarr) << std::endl;

	std::cout << "double" << std::endl;
	input(darr);
	std::cout << average(darr) << std::endl;

	std::cout << "float" << std::endl;
	input(farr);
	std::cout << average(farr) << std::endl;

	return 0;
}