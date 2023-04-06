#include <iostream>
#include <map>
#include <exception>

class DataBase {
public:
	std::map <std::string, int> dataBase;
	std::map<std::string, int>::iterator it;

	void add(std::string article, int count) {
		if (count < 0) {
			throw std::invalid_argument("count below zero");
		}
		else {
			dataBase.insert(std::pair<std::string, int>(article, count));
		}
	}

	void remove(std::string article, int count) {
		it = dataBase.find(article);
		it->second = it->second - count;
		std::cout << "Available " << article << ":" << it->second << std::endl;
	}

	void display() {
		std::cout << "Database:" << std::endl;
		for (it = dataBase.begin(); it != dataBase.end(); ++it) {
			std::cout << it->first << ": " << it->second << std::endl;
		}
	}
};

class Cart {
	std::map <std::string, int> cart;
public:
	void add(std::string a, int c, DataBase* db) {
		if (c < 0) {
			throw std::invalid_argument("count below zero");
		}
		bool found = false;
		std::map<std::string, int>::iterator it = db->dataBase.find(a);
		found = it != db->dataBase.end();
		if (found) {
			if (it->second < c) {
				throw std::invalid_argument("count out of range");
			}
			else {
				cart.insert(std::pair<std::string, int>(a,c));
				std::cout << a << " " << c << " add to cart" << std::endl;
				db->remove(a, c);
			}
		}
		if (!found) {
			throw std::invalid_argument("article not found");
		}
	}

	void remove(std::string a, int c) {
		std::map<std::string, int>::iterator it = cart.find(a);
		it->second = it->second - c;
		std::cout << "Available " << a << ": " << it->second << std::endl;
	}

	void display() {
		std::cout << "Cart:" << std::endl;
		std::map<std::string, int>::iterator it;
		for (it = cart.begin(); it != cart.end(); ++it) {
			std::cout << it->first << ": " << it->second << std::endl;
		}
	}
};

int main() {
	DataBase db;
	Cart crt;

	std::string article;
	int count;

	//Добавление товара в базу
	std::cout << "Add articles to database" << std::endl;
	do {
		std::cout << "Article: ";
		std::cin >> article;
		std::cout << "Count: ";
		std::cin >> count;
		try {
			db.add(article, count);
		}
		catch (const std::exception& x) {
			std::cerr << "Caught exception: " << x.what() << std::endl;
		}
		catch (...) {
			std::runtime_error("Something happen");
		}
	} while (db.dataBase.size() < 5);

	db.display();

	do {
		std::cout << "Command: ";
		std::cin >> article;
		if (article == "add") {
			std::cout << "Add articles to cart" << std::endl;
			std::cout << "Article: ";
			std::cin >> article;
			std::cout << "Count: ";
			std::cin >> count;
			try {
				crt.add(article, count, &db);
			}
			catch (const std::exception& x) {
				std::cerr << "Caught exception: " << x.what() << std::endl;
			}
			catch (...) {
				std::runtime_error("Something happen");
			}
		}
		if (article == "remove") {
			std::cout << "Remove articles from cart" << std::endl;
			std::cout << "Article: ";
			std::cin >> article;
			std::cout << "Count: ";
			std::cin >> count;
			crt.remove(article, count);
		}
		if (article == "display") {
			crt.display();
		}
	} while (article != "stop");

	/*try {
		db.add("milk", 100);
	}
	catch (const std::exception& x) {
		std::cerr << " Caught exception: " << x.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Something happen..." << std::endl;
	}

	try {
		db.add("potato", 500);
	}
	catch (const std::exception& x) {
		std::cerr << "Caught exception: " << x.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Something happen..." << std::endl;
	}

	try {
		db.add("salamon", 3);
	}
	catch (const std::exception& x) {
		std::cerr << "Caught exception: " << x.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Something happen..." << std::endl;
	}

	try {
		db.add("bread", 10);
	}
	catch (const std::exception& x) {
		std::cerr << "Caught exception: " << x.what() << std::endl;
	}
	catch (...) {
		std::cerr << "Something happen..." << std::endl;
	}*/

	
	//db.display();
	//std::cout << std::endl << "================" << std::endl << std::endl;

	////Добавление товара в корзину
	//try {
	//	crt.add("milk", 2, &db);
	//}
	//catch (const std::exception& x) {
	//	std::cerr << "Caught exception: " << x.what() << std::endl;
	//}
	//catch (...) {
	//	std::cerr << "Something happen..." << std::endl;
	//}

	//try {
	//	crt.add("potato", 50, &db);
	//}
	//catch (const std::exception& x) {
	//	std::cerr << "Caught exception: " << x.what() << std::endl;
	//}
	//catch (...) {
	//	std::cerr << "Something happen..." << std::endl;
	//}

	//try {
	//	crt.add("salamon", 4, &db);
	//}
	//catch (const std::exception& x) {
	//	std::cerr << "Caught exception: " << x.what() << std::endl;
	//}
	//catch (...) {
	//	std::cerr << "Something happen..." << std::endl;
	//}

	//try {
	//	crt.add("bread", -1, &db);
	//}
	//catch (const std::exception& x) {
	//	std::cerr << "Caught exception: " << x.what() << std::endl;
	//}
	//catch (...) {
	//	std::cerr << "Something happen..." << std::endl;
	//}

	/*std::cout << std::endl << "================" << std::endl << std::endl;
	crt.display();

	std::cout << std::endl << "================" << std::endl << std::endl;
	db.display();*/
}
