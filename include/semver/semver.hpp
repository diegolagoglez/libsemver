#ifndef __SEMVER_HPP__
#define __SEMVER_HPP__

#include <string>

namespace semver {

using std::string;

class SemVer {
	private:

		unsigned 	fMajor;
		unsigned	fMinor;
		unsigned	fPatch;
		string		fLabel;
		string		fBuild;

	public:
		SemVer();

		SemVer(const SemVer& s);

		SemVer(unsigned major, unsigned minor, unsigned patch, const string label = string(), const string build = string());

		SemVer(string version);

		virtual ~SemVer();

		virtual void			assign(const string version);

		virtual unsigned		major() const;
		virtual unsigned		minor() const;
		virtual unsigned		patch() const;
		virtual const string	label() const;
		virtual const string	build() const;

		virtual int				compare(const SemVer& semver) const;

		virtual const string	toString() const;
};

}	// namespace semver

#endif
