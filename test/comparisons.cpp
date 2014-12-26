#include <iostream>
#include <exception>

using namespace std;

#include <semver/semver.hpp>

typedef struct {
	string a;
	string b;
	int comparison;
} TestVersion;

static TestVersion versions[] = {
	{ "", "", 0 },
	{ "0", "0", 0 },
	{ "0.0", "0.0", 0 },
	{ "0.0.0", "0.0.0", 0 },
	{ "0.0.1", "0.0.1", 0 },
	{ "0.0.1", "0.0.2", -1 },
	{ "0.0.2", "0.0.1", 1 },
	{ "1.2.3", "1.2.4", -1 },
	{ "1.2.3", "1.3.3", -1 },
	{ "1.2.3", "1.3.2", -1 },
	{ "2.5.6", "1.9.9", 1 },
	{ "5.0.0", "4.0.0", 1 },
	{ "0.98.0", "0.97.0", 1 },
	{ "6.0.254", "6.0.255", -1 },
	{ "0.0.1-alpha", "0.0.1-alpha1", -1 },
	{ "0.0.1-alpha", "0.0.1-beta", -1 },
	{ "0.0.1-alpha-3", "0.0.1-alpha-2", 1 },
};

void
showComparisons(const semver::SemVer& a, const semver::SemVer& b, int shouldBe) {
	cout << "'" << a << "' cmp '" << b << "' = " << a.compare(b) << " (should be: " << shouldBe << ")" << endl;
	cout << "'" << a << "' == '" << b << "' = " << (a == b ? "yes" : "no") << endl;
	cout << "'" << a << "' != '" << b << "' = " << (a != b ? "yes" : "no") << endl;
	cout << "'" << a << "' <  '" << b << "' = " << (a < b ? "yes" : "no") << endl;
	cout << "'" << a << "' >  '" << b << "' = " << (a > b ? "yes" : "no") << endl;
	cout << "'" << a << "' <= '" << b << "' = " << (a <= b ? "yes" : "no") << endl;
	cout << "'" << a << "' >= '" << b << "' = " << (a >= b ? "yes" : "no") << endl;
	cout << "---------------------------------------" << endl;
}

int
main() {
	cout << "SemVer Class Test" << endl;

	semver::SemVer* a = new semver::SemVer();
	semver::SemVer* b = new semver::SemVer();

	for (int i = 0; i < sizeof(versions) / sizeof(TestVersion); i++) {
		cout << "Testing: '" << versions[i].a << "' -- '" << versions[i].b << "'" << endl;
		try {
			a->assign(versions[i].a);
			b->assign(versions[i].b);

			showComparisons(*a, *b, versions[i].comparison);
		} catch(exception& e) {
			cout << "   ERROR: " << e.what() << endl;
		}
	}

	return 0;
}
