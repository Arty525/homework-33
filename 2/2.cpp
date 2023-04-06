#include <iostream>
#include <vector>
#include <ctime>

class FishException : public std::exception {
	const char* what() const noexcept override {
		return "fish";
	}
};

class BootException : public std::exception {
	const char* what() const noexcept override {
		return "boot";
	}
};

int main() {
	srand(time(nullptr));
	std::vector <std::string> field = { "0", "0", "0", "0", "0", "0", "0", "0", "0" };
	int s;

	field[std::rand() % 9] = "fish";

	for (int i = 3; i != 0;) {
		int n = std::rand() % 9;
		if (field[n] == "0") {
			field[n] = "boot";
			i -= 1;
		}
	}

	for (int i = 1;; ++i) {
		std::cout << "Sector: ";
		try {
			std::cin >> s;
			if (field[s] == "fish"){
				throw FishException();
			}
			else if (field[s] == "boot") {
				throw BootException();
			}
			else {
				std::cout << "Nothing, try again" << std::endl;
			}
		}
		catch (const std::exception& x) {
			std::cerr << "You catch " << x.what() << std::endl;
			std::cout << "Attempts: " << i << std::endl;
			break;
		}
	}
}