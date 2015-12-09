CXXFLAGS+=-std=c++11
LDLIBS+=-lboost_filesystem
LDLIBS+=-lboost_system
LDLIBS+=-lpthread

.PHONY: default-target
default-target: linux_events-proxy
linux_events-proxy: linux_events

.PHONY: clean
clean:
	$(RM) linux_events
