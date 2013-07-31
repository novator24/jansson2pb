CPPFLAGS = -g -fPIC -I.
LDFLAGS = -Wl,-rpath -Wl,.
CURDIR = .

all: jansson2pb-util jansson2pb-test libjansson2pb.so 

test: jansson2pb-test
	./jansson2pb-test

clean:
	-rm -f test/test.pb.h test/test.pb.cc *.o *.so *.a libjansson2pb.so.* jansson2pb-util jansson2pb-test

libjansson2pb.a: jansson2pb.o dump.o error.o hashtable.o load.o memory.o pack_unpack.o strbuffer.o strconv.o utf.o value.o
	ar cr libjansson2pb.a $^

libjansson2pb.so: jansson2pb.o dump.o error.o hashtable.o load.o memory.o pack_unpack.o strbuffer.o strconv.o utf.o value.o
	$(CXX) $(LDFLAGS) -o $@ $^ -Wl,-soname=$@ -Wl,-h -Wl,$@ -shared -L. -lprotobuf -lstdc++

jansson2pb.o: 3party/jansson2pb.cpp
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR) -o $@ $^

dump.o: src/dump.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

error.o: src/error.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

hashtable.o: src/hashtable.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

load.o: src/load.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

memory.o: src/memory.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

pack_unpack.o: src/pack_unpack.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

strbuffer.o: src/strbuffer.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

strconv.o: src/strconv.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

utf.o: src/utf.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

value.o: src/value.c
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR)/src -o $@ $^

test/test.pb.cc: test/test.proto
	protoc -I$(CURDIR) --cpp_out=$(CURDIR) $(CURDIR)/$^

test.pb.o: test/test.pb.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $^

jansson2pb-util: util/main.cpp test.pb.o libjansson2pb.a
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR) -o main.o util/main.cpp
	$(CXX) $(LDFLAGS) -o jansson2pb-util main.o test.pb.o libjansson2pb.a -lprotobuf

jansson2pb-test: test/test.cpp test.pb.o libjansson2pb.a
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR) -o test.o test/test.cpp
	$(CXX) $(LDFLAGS) -o jansson2pb-test test.o test.pb.o libjansson2pb.a -lprotobuf

