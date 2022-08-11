#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include <plf_hive.h>

int main() {
	constexpr auto elementsCount{ 10000000 };

	std::random_device rd;
	std::mt19937 mt(rd());

	std::vector<double> vector;
	plf::hive<double> hive;

	for (auto i{ 0 }; i < elementsCount; i++) {
		vector.push_back(i);
		hive.insert(i);
	}

	auto start = std::chrono::high_resolution_clock::now();
	for(auto i{ 0 }; i < 10000; i++) {
		std::uniform_int dist(0, elementsCount - i);
		const auto random = dist(mt);
		const auto temp = std::next(vector.begin(), random);
		vector.erase(temp);
	}
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "Vector erase time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (auto i{ 0 }; i < 100000; i++) {
		std::uniform_int dist(0, elementsCount - i);
		const auto random = dist(mt);
		const auto temp= std::next(hive.begin(), random);
		hive.erase(temp);
	}
	end = std::chrono::high_resolution_clock::now();

	std::cout << "Hive erase time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (auto& el : vector)
		el++;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Vector modify time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (auto& el : hive)
		el++;
	end = std::chrono::high_resolution_clock::now();
	std::cout << "Hive modify time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;


	start = std::chrono::high_resolution_clock::now();
	for (auto i{ 0 }; i < 100000; i++) {
		vector.push_back(1);
	}
	end = std::chrono::high_resolution_clock::now();

	std::cout << "Vector insert time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

	start = std::chrono::high_resolution_clock::now();
	for (auto i{ 0 }; i < 100000; i++) {
		hive.insert(1);
	}
	end = std::chrono::high_resolution_clock::now();

	std::cout << "Hive insert time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start) << std::endl;

	return 0;
}