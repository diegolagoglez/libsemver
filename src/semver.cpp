#include "../include/semver/semver.hpp"

#include <sstream>
#include <exception>

#include <boost/regex.hpp>

using std::stringstream;

namespace semver {

static unsigned
string_to_int(const string value) {
	stringstream ss(value);
	unsigned result;
	ss >> result;
	return result;
}

/*
 * Methods names 'major' and 'minor' conflicts with sys/sysmacros.h, but POSIX
 * says they must be available, so with the next lines, those macros are
 * undefined. See more information at:
 * http://stackoverflow.com/questions/22240973/major-and-minor-macros-defined-in-sys-sysmacros-h-pulled-in-by-iterator
*/
#undef major
#undef minor

static const string NUMBER_SEPARATOR	= ".";
static const string LABEL_SEPARATOR		= "-";
static const string BUILD_SEPARATOR		= "+";

SemVer::SemVer()
	: fMajor(0),
	  fMinor(0),
	  fPatch(0),
	  fLabel(),
	  fBuild()
{
}

SemVer::SemVer(const SemVer& s)
	: fMajor(s.fMajor),
	  fMinor(s.fMinor),
	  fPatch(s.fPatch),
	  fLabel(s.fLabel),
	  fBuild(s.fBuild)
{
}

SemVer::SemVer(unsigned major, unsigned minor, unsigned patch, const string label, const string build)
	: fMajor(major),
	  fMinor(minor),
	  fPatch(patch),
	  fLabel(label),
	  fBuild(build)
{
}

SemVer::SemVer(const string version)
	: fMajor(0),
	  fMinor(0),
	  fPatch(0),
	  fLabel(),
	  fBuild()
{
	assign(version);
}

SemVer::~SemVer() {
}

void
SemVer::check(const string version) const {
	if (version != toString()) {
		throw std::invalid_argument("Invalid semantic version string: " + version);
	}
}

int
SemVer::intCompare(unsigned a, unsigned b) const {
	return (a < b) ? -1 : (a > b);
}

int
SemVer::stringCompare(string a, string b) const {
	// TODO: Implement this with element precedence rules.
	return a.compare(b);
}

void
SemVer::assign(const string version) {
	// Examples: 1.2.3, 1.2.3-beta, 1.2.3-beta+build, 1.2.3-beta.1+B, 1.2.3+build
	// RegEx: ([0-9]+)\.([0-9]+)\.([0-9]+)(?:-(\w+(\.\w*))(\+(.*))?|\+(.*))?
	// Matches: 1, 2 and 3: version parts. 4 is always de label part (alpha,
	// beta, etc.); 6 or 7 are the build metainformation part.

	static const boost::regex expression("([0-9]+)\\.([0-9]+)\\.([0-9]+)(?:-(\\w+(\\.\\w*)?)(\\+(.*))?|\\+(.*))?");

	// Other example: ([0-9]+)\.([0-9]+)\.([0-9]+)(?:-((?!\+)[\w\.-]+))?(?:\+([\w\.-]+))?

	boost::match_results<string::const_iterator> results;

	if (boost::regex_search(version, results, expression)) {
		fMajor = string_to_int(results[1]);
		fMinor = string_to_int(results[2]);
		fPatch = string_to_int(results[3]);
		fLabel = results[4];
		fBuild = results[7] != "" ? results[7] : results[8];
		check(version);
	} else {
		throw std::invalid_argument("Invalid semantic version string: " + version);
	}
}

unsigned
SemVer::major() const {
	return fMajor;
}

unsigned
SemVer::minor() const {
	return fMinor;
}

unsigned
SemVer::patch() const {
	return fPatch;
}

const string
SemVer::label() const {
	return fLabel;
}

const string
SemVer::build() const {
	return fBuild;
}

int
SemVer::compare(const SemVer& semver) const {
	if (fMajor == semver.fMajor) {
		if (fMinor == semver.fMinor) {
			if (fPatch == semver.fPatch) {
				if (fLabel == semver.fLabel) {
					return stringCompare(fBuild, semver.fBuild);
				} else {
					return stringCompare(fLabel, semver.fLabel);
				}
			} else {
				return intCompare(fPatch, semver.fPatch);
			}
		} else {
			return intCompare(fMinor, semver.fMinor);
		}
	} else {
		return intCompare(fMajor, semver.fMajor);
	}
	return 0;
}

int
SemVer::compare(const SemVer* semver) const {
	return compare(*semver);
}

bool
SemVer::operator == (const SemVer& semver) const {
	return compare(semver) == 0;
}

bool
SemVer::operator != (const SemVer& semver) const {
	return !operator==(semver);
}

bool
SemVer::operator <	(const SemVer& semver) const {
	return compare(semver) < 0;
}

bool
SemVer::operator >	(const SemVer& semver) const {
	return compare(semver) > 0;
}

bool
SemVer::operator <=	(const SemVer& semver) const {
	return compare(semver) <= 0;
}

bool
SemVer::operator >=	(const SemVer& semver) const {
	return compare(semver) >= 0;
}

const string
SemVer::toString(bool expanded) const {
	stringstream out;
	if (expanded) {
		out << "Major: " << fMajor << "\n";
		out << "Minor: " << fMinor << "\n";
		out << "Patch: " << fPatch << "\n";
		out << "Label: " << fLabel << "\n";
		out << "Build: " << fBuild << "\n";
	} else {
		out << fMajor << NUMBER_SEPARATOR << fMinor << NUMBER_SEPARATOR << fPatch << (fLabel != "" ? LABEL_SEPARATOR + fLabel : "") << (fBuild != "" ? BUILD_SEPARATOR + fBuild : "");
	}
	return out.str();
}

std::ostream&
operator << (std::ostream& out, const SemVer& semver) {
	out << semver.toString();
	return out;
}

}	// namespace semver
