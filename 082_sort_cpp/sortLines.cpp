#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static bool read_all_lines(std::istream &in, std::vector<std::string> &lines) {
	lines.clear();
	std::string s;
	while (std::getline(in, s)) {
		lines.push_back(std::move(s));
	}

	return !in.bad();
}

static int process_stream(std::istream &in) {
	std::vector<std::string> lines;
	if (!read_all_lines(in, lines)) {
		std::cerr << "Something wrong with reading input\n";
		return EXIT_FAILURE;
	}
	std::sort(lines.begin(), lines.end());
	for (const auto &line : lines) {
		std::cout << line << '\n';
	}
	return EXIT_SUCCESS;
}

static int process_file(const char *path) {
	std::ifstream fin(path);
	if (!fin) {
		std::cerr << "cannot open file\n";
		return EXIT_FAILURE;
	}

	int rc = process_stream(fin);

	return rc;
}

int main(int argc, char **argv) {
	if (argc == 1) {
		return process_stream(std::cin);
	}

	for (int i = 1; i < argc; i++) {
		int rc = process_file(argv[i]);
		if (rc != EXIT_SUCCESS) {
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}
