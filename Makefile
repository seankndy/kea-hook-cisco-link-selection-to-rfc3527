KEA_INCLUDE ?= /usr/include/kea
KEA_LIB ?= /usr/lib

OBJECTS = src/load_unload.o src/callouts.o src/version.o
MODULES = libdhcp_cisco_link_selection_to_rfc3527.so
DEPS = $(OBJECTS:.o=.d)
CXXFLAGS = -I $(KEA_INCLUDE) -fPIC -Wno-deprecated -std=c++11
LDFLAGS = -L $(KEA_LIB) -shared -lkea-dhcpsrv -lkea-dhcp++ -lkea-hooks -lkea-log -lkea-util -lkea-exceptions

all: $(OBJECTS) $(MODULES)

libdhcp_cisco_link_selection_to_rfc3527.so: $(OBJECTS)
	$(CXX) -o $@ $(CXXFLAGS) $(LDFLAGS) $(OBJECTS)

%.o: %.cc
	$(CXX) -MMD -MP -c $(CXXFLAGS) -o $@ $<

clean:
	rm -f src/*.o
	rm -f src/*.d
	rm -f libdhcp_cisco_link_selection_to_rfc3527.so

install:
	mkdir -p $(DESTDIR)
	/usr/bin/install -c -m 644 libdhcp_cisco_link_selection_to_rfc3527.so $(DESTDIR)/libdhcp_cisco_link_selection_to_rfc3527.so

-include $(DEPS)
