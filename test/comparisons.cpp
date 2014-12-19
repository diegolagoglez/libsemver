#include <iostream>
#include <exception>

using namespace std;

#include <semver/semver.hpp>

void
showComparisons(const semver::SemVer& a, const semver::SemVer& b) {
	cout << "'" << a << "' == '" << b << "' = " << (a == b ? "yes" : "no") << endl;
	cout << "'" << a << "' != '" << b << "' = " << (a != b ? "yes" : "no") << endl;
	cout << "'" << a << "' <  '" << b << "' = " << (a < b ? "yes" : "no") << endl;
	cout << "'" << a << "' >  '" << b << "' = " << (a > b ? "yes" : "no") << endl;
	cout << "'" << a << "' <= '" << b << "' = " << (a <= b ? "yes" : "no") << endl;
	cout << "'" << a << "' >= '" << b << "' = " << (a >= b ? "yes" : "no") << endl;
}

int
main() {
	cout << "SemVer Class Test" << endl;

	semver::SemVer* a = new semver::SemVer("0.0.1");
	semver::SemVer* b = new semver::SemVer("0.0.2");

	cout << "'" << *a << "' cmp '" << *b << "' = " << a->compare(b) << endl;

	a->assign("0.0.2");
	b->assign("0.0.1");
	cout << "'" << *a << "' cmp '" << *b << "' = " << a->compare(b) << endl;

	a->assign("1.2.3");
	b->assign("1.2.3");
	cout << "'" << *a << "' cmp '" << *b << "' = " << a->compare(b) << endl;

	showComparisons(*a, *b);

	showComparisons(semver::SemVer("0.0.1"), semver::SemVer("0.0.2"));

	return 0;
}
