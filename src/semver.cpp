#include "../include/semver/semver.hpp"

#include <sstream>

using std::stringstream;

namespace semver {

const string SemVer::SEPARATOR	= ".";

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
	parseVersionString(version);
}

SemVer::~SemVer() {
}

void
SemVer::parseVersionString(const string version) {
	// TODO: Implement this.
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
	out << fMajor << SEPARATOR << fMinor << SEPARATOR << fPatch;
	return out.str();
}

}	// namespace semver
