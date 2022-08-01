#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include <plf_hive.h>

int main() {
	constexpr auto elementsCount{ 1000000 };

	std::random_device rd;
	std::mt19937 mt(rd());
	const std::uniform_real_distribution<double> dist(1, 1000000);

	std::vector<double> vector;
	plf::hive<double> hive;

	auto start = std::chrono::high_resolution_clock::now();
	for (auto i{ 0 }; i < elementsCount; i++)
		vector.push_back(dist(mt));
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Vector insert time: " << end - start << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (auto i{ 0 }; i < elementsCount; i++)
		hive.insert(dist(mt));
	end = std::chrono::high_resolution_clock::now();

	std::cout << "Hive insert time: " << end - start << std::endl;

	return 0;
}