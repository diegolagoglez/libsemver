#include <iostream>

using namespace std;

#include <semver/semver.hpp>

int
main() {
	cout << "SemVer Class Test" << endl;

	semver::SemVer* s = new semver::SemVer();

	cout << s->toString() << endl;

	return 0;
}
