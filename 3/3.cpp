#include <iostream>
#include <vector>

template<typename T1, typename T2>
struct Pair {
	T1 key;
	T2 value;
	Pair(T1 inKey, T2 inVal) : key(inKey), value(inVal) {}
};

template<typename T1, typename T2>
class Registry {
	std::vector<Pair<T1, T2>> list;

public:
	void add(T1 k, T2 v) {
		list.push_back(Pair<T1,T2>(k,v));
	}

	void remove(T1 k) {
		std::vector<Pair<T1, T2>> list_removed;
		for (int i = 0; i < list.size(); ++i) {
			if (list[i].key != k) {
				list_removed.push_back(list[i]);
			}
		}
		list = list_removed;
		print();
	}

	void print() {
		for (int i = 0; i < list.size(); ++i) {
			std::cout << list[i].key << " - " << list[i].value << std::endl;
		}
	}

	std::vector<Pair<T1, T2>> get_list() {
		return list;
	}

	std::vector<int> find(T1 k) {
		std::vector<int> pos;
		for (int i = 0; i < list.size(); ++i) {
			if (list[i].key == k) {
				pos.push_back(i);
			}
		}
		return pos;
	}
};

template<typename T1,typename T2>
void operation(Registry<T1,T2> reg) {
	std::string command;
	T1 key;
	T2 value;
	do {
		std::cout << "Command: ";
		std::cin >> command;
		if (command == "add") {
			std::cout << "KEY: ";
			std::cin >> key;
			std::cout << "VALUE:";
			std::cin >> value;
			reg.add(key, value);
		}
		else if (command == "remove") {
			std::cout << "KEY: ";
			std::cin >> key;
			reg.remove(key);
		}
		else if (command == "print") {
			reg.print();
		}
		else if (command == "find") {
			std::vector<int> pos;
			std::vector<Pair<T1, T2>> list = reg.get_list();
			std::cout << "KEY: ";
			std::cin >> key;
			pos = reg.find(key);
			for (int i = 0; i < pos.size(); ++i) {
				