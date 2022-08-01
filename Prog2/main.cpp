#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include <plf_hive.h>

int main() {
	constexpr auto elementsCount{ 1000000 };

	std::random_device rd;
	std::mt19937 mt(rd());

	std::vector<double> vector;
	plf::hive<double> hive;

	for (auto i{ 0 }; i < elementsCount; i++) {
		vector.push_back(i);
		hive.insert(i);
	}

	auto start = std::chrono::high_resolution_clock::now();
	for(auto i{ 0 }; i < 100000; i++) {
		const std::uniform_int dist(0, elementsCount - i);
		const auto random = dist(mt);
		vector.erase(vector.begin() + random);
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Vector erase time: " << end - start << std::endl;

	auto start = std::chrono::high_resolution_clock::now();
	for (auto i{ 0 }; i < 100000; i++) {
		const std::uniform_int dist(0, elementsCount - i);
		const auto random = dist(mt);
		hive.erase(hive.begin() + random);
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Vector erase time: " << end - start << std::endl;

	return 0;
}