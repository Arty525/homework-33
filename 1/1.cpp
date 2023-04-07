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
		std::cout << "Available at storage" << article << ":" << it->second << std::endl;
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
				if (cart.find(a) == cart.end()) {
					cart.insert(std::pair<std::string, int>(a, c));
					std::cout << a << " " << c << " add to cart" << std::endl;
					db->remove(a, c);
					it = cart.find(a);
					std::cout << "Avalable " << it->first << " at cart: " << it->second << std::endl;
				}
				else {
					it = cart.find(a);
					it->second += c;
					std::cout << a << " " << c << " add to cart" << std::endl;
					db->remove(a, c);
					std::cout << "Avalable " << it->first << " at cart: " << it->second << std::endl;
				}
			}
		}
		else {
			throw std::invalid_argument("article not found");
		}
	}

	void remove(std::string a, int c, DataBase* db) {\
		if (c < 0) {
			throw std::invalid_argument("count below zero");
		}
		else {
			std::map<std::string, int>::iterator it = cart.find(a);
			bool found = false;
			found = it != cart.end();
			if (found) {
				if (c > it->second) {
					throw std::invalid_argument("count out of range");
				}
				else {
					it->second = it->second - c;
					std::cout << "Available " << a << " at cart: " << it->second << std::endl;
					it = db->dataBase.find(a);
					it->second += c;
					std::cout << "Available at storage: " << it->second << std::endl;
				}
			}
			else {
				throw std::invalid_argument("article not found");
			}
		}
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
	int count, n;

	//Добавление товара в базу
	std::cout << "Add articles to database" << std::endl;
	std::cout << "How many articles do you want to add?: " << std::endl;
	std::cin >> n;
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
	} while (db.dataBase.size() < n);

	db.display(); //Вывод содержимого базы данных
	
	do {
		std::cout << "Command: ";
		std::cin >> article;
		if (article == "add") {//Добавление товаров в корзину
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
		if (article == "remove") {//Удаление из корзины
			std::cout << "Remove articles from cart" << std::endl;
			std::cout << "Article: ";
			std::cin >> article;
			std::cout << "Count: ";
			std::cin >> count;
			try{
				crt.remove(article, count, &db);
			}
			catch (const std::exception& x) {
				std::cerr << "Caught exception: " << x.what() << std::endl;
			}
			catch (...) {
				std::runtime_error("Something happen");
			}
		}
		if (article == "display") {//Вывод содержимого корзины
			crt.display();
		}
	} while (article != "stop");
	return 0;
}
