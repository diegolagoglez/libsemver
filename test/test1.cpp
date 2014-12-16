#include <iostream>
#include <exception>

using namespace std;

#include <semver/semver.hpp>

int
main() {
	cout << "SemVer Class Test" << endl;

	semver::SemVer* s = new semver::SemVer("1.2.3");

	int SIZE = 8;
	string ss[] = {
		"",
		"1",
		"1.2",
		"1.2.3",
		"1.2.3-alpha",
		"1.2.3-alpha+build",
		"0.0.0+build_metadata",
		"0.0.0+build-metadata"	// does not work
	};

	for (int i = 0; i < SIZE; i++) {
		try {
			s->assign(ss[i]);
			cout << (ss[i] == s->toString() ? "  OK" : "FAIL") << ": " << ss[i] << " =? " << s->toString() << endl;
		} catch(std::exception& e) {
			cerr << "ERROR: " << e.what() << endl;
		}
	}

	return 0;
}
