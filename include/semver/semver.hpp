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

		void		check(const string version) const;

		int			intCompare(unsigned a, unsigned b) const;
		int			stringCompare(string a, string b) const;

	public:
		SemVer();

		SemVer(const SemVer& s);

		SemVer(unsigned major, unsigned minor, unsigned patch, const string label = string(), const string build = string());

		SemVer(const string version);

		virtual ~SemVer();

		virtual void			assign(const string version);

		virtual unsigned		major() const;
		virtual unsigned		minor() const;
		virtual unsigned		patch() const;
		virtual const string	label() const;
		virtual const string	build() const;

		virtual int				compare(const SemVer& semver) const;
		virtual int				compare(const SemVer* semver) const;

		virtual const string	toString() const;
};

std::ostream&
operator << (std::ostream& out, const SemVer& semver);

}	// namespace semver

#endif
