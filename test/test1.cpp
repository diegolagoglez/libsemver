#include <iostream>
#include <exception>

using namespace std;

#include <semver/semver.hpp>

int
main() {
	cout << "SemVer Class Test" << endl;

	semver::SemVer* s = new semver::SemVer();

	int SIZE = 17;
	string ss[] = {
		"",
		"1",
		"1.2",
		"1.2.3",
		"1.2.3.4",
		"1.2.3-alpha",
		"1.2.3-alpha+build",
		"0.0.0+build_metadata",
		"0.0.0+build-metadata",
		"1.2.3-alpha+build-metadata",
		"4.5.6+build-metadata",
		"6.7.8-beta1+g:16ebbdc",
		"1.111.6985",
		"0.0.666",
		"0.0.1-beta1587-metainfo",
		"99.0.0+a-long-string-of-metainformation-from-the-build",
		"0.0.2-some spaces"
	};

	for (int i = 0; i < SIZE; i++) {
		try {
			s->assign(ss[i]);
			cout << (ss[i] == s->toString() ? "  OK" : "FAIL") << ": " << ss[i] << " == " << s->toString() << endl;
		} catch(std::exception& e) {
			cerr << "ERROR: " << e.what() << endl;
		}
	}

	return 0;
}
