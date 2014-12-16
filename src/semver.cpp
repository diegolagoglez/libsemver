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

SemVer::SemVer() {

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
SemVer::assign(const string version) {
	// Examples: 1.2.3, 1.2.3-beta, 1.2.3-beta+build, 1.2.3+build
	// RegEx: ([0-9]+)\.([0-9]+)\.([0-9]+)(?:-(\w+)\+(\w+)|-(\w+)|\+(\w+))?
	// Matches: 1, 2 and 3: version parts. 4: beta when beta+build; 5: build
	// when beta+build; 6: beta when only beta; 7: build when only build.

	// FIX: 0.0.0+build-metadata

	static const boost::regex expression("([0-9]+)\\.([0-9]+)\\.([0-9]+)(?:-(\\w+)\\+(\\w+)|-(\\w+)|\\+(\\w+))?");

	boost::match_results<string::const_iterator> results;

	if (boost::regex_search(version, results, expression)) {
		fMajor = string_to_int(results[1]);
		fMinor = string_to_int(results[2]);
		fPatch = string_to_int(results[3]);
		fLabel = results[4] != "" ? results[4] : results[6];
		fBuild = results[5] != "" ? results[5] : results[7];
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
	// TODO: Implement this.
	return 0;
}

const string
SemVer::toString() const {
	stringstream out;
	out << fMajor << NUMBER_SEPARATOR << fMinor << NUMBER_SEPARATOR << fPatch << (fLabel != "" ? LABEL_SEPARATOR + fLabel : "") << (fBuild != "" ? BUILD_SEPARATOR + fBuild : "");
	return out.str();
}

}	// namespace semver
