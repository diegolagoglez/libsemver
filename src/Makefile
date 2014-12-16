
PROJECT_NAME	:= libsemver
VERSION			:= 0
LIBVERSION		:= $(VERSION).0.1
BASENAME		:= libsemver
SONAME			:= $(BASENAME).so.$(VERSION)
LIBNAME			:= $(BASENAME).so.$(LIBVERSION)
LINKERNAME		:= $(BASENAME).so
INSTALLDIR		:= /usr/local/lib

INCLUDEDIR		:= ../include
CXX_INCLUDE		:= -I$(INCLUDEDIR)
LIBNAMEFLAGS	:= -Wl,-soname,$(SONAME)
CXXFLAGS		:= -fPIC -Wall -lboost_regex
DEPS_FLAGS		:= -MMD -MP
LIBDIR			:= ../lib

SRCS 			:= semver.cpp

OBJS 			:= $(SRCS:%.cpp=%.o)
DEPS 			:= $(OBJS:%.o=%.d)

OBJS_WILDCARD	:= *.o
DEPS_WILDCARD	:= *.d

.PHONY: all debug release

all:
	@echo "$(PROJECT_NAME) library Makefile - Copyright © 2009-2014 Diego Lago <diego.lago.gonzalez@gmail.com>"
	@echo "Git repository at: https://github.com/diegolagoglez/libsemver"
	@echo "Please specify one of the following targets:"
	@echo " debug      : Generates the library in debug mode."
	@echo " release    : Generates an optimized library."
	@echo " install    : Installs generated library into '$(INSTALLDIR)'."
#	@echo " devinstall : Installs development files into '$(INCLUDEINSTALLDIR)'."
	@echo " clean      : Cleans generated object files."

%.o: %.cpp
	@echo "  CC $@"
	@$(CXX) -c $(VARS) $(CXXFLAGS) $(DEPS_FLAGS) $(INCLUDE) -o "$@" "$<"

debug: CXXFLAGS := $(CXXFLAGS) -g3 -O0 -DDEBUG
debug: $(OBJS)
	@echo "  GEN $(LIBDIR)/$(LIBNAME)"
	@mkdir -p $(LIBDIR)
	@$(CXX) -shared $(VARS) $(CXXFLAGS) $(LIBS) $(LIBNAMEFLAGS) -o $(LIBDIR)/$(LIBNAME) *.o
	@cd $(LIBDIR) && ln -sf $(LIBNAME) $(LINKERNAME) && ln -sf $(LIBNAME) $(SONAME)

release: CXXFLAGS := $(CXXFLAGS) -O3 -DRELEASE
release: $(OBJS)
	@echo "  GEN $(LIBDIR)/$(LIBNAME)"
	@mkdir -p $(LIBDIR)
	@$(CXX) -shared $(VARS) $(CXXFLAGS) $(LIBS) $(LIBNAMEFLAGS) -o $(LIBDIR)/$(LIBNAME) *.o
	@cd $(LIBDIR) && ln -sf $(LIBNAME) $(LINKERNAME) && ln -sf $(LIBNAME) $(SONAME)

.PHONY: clean

clean:
	@echo "  CLEAN"
	@rm -f $(LIBDIR)/$(LIBNAME) $(LIBDIR)/$(LINKERNAME) $(LIBDIR)/$(SONAME) $(OBJS_WILDCARD) $(DEPS_WILDCARD)
