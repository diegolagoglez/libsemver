#include "../include/semver/semver.hpp"

namespace semver {

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

int
SemVer::compare(const SemVer& semver) const {
	// TODO: Implement this.
	return 0;
}

}	// namespace semver
