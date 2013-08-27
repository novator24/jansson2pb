PREFIX = /usr
PROTODIR = /usr
CPPFLAGS = -g -fPIC -I. -I$(PROTODIR)/include
LDFLAGS = -Wl,-rpath,$(PROTODIR)/lib -Wl,-rpath,. -L$(PROTODIR)/lib
CURDIR = .

all: jansson2pb-util jansson2pb-test libjansson2pb.so 

test: jansson2pb-test
	./jansson2pb-test

clean:
	-rm -f test/test.pb.h test/test.pb.cc *.o *.so *.a libjansson2pb.so.* jansson2pb-util jansson2pb-test

install: libjansson2pb.a libjansson2pb.so
	mkdir -p ${PREFIX}/include/3party
	mkdir -p ${PREFIX}/lib
	rm -f ${PREFIX}/lib/libjansson2pb.a
	rm -f ${PREFIX}/lib/libjansson2pb.so
	cp libjansson2pb.a ${PREFIX}/lib/libjansson2pb-0.2-4.a
	ln -s ${PREFIX}/lib/libjansson2pb-0.2-4.a ${PREFIX}/lib/libjansson2pb.a
	cp libjansson2pb.so ${PREFIX}/lib/libjansson2pb-0.2-4.so
	ln -s ${PREFIX}/lib/libjansson2pb-0.2-4.so ${PREFIX}/lib/libjansson2pb.so
	cp 3party/*.h ${PREFIX}/include/3party
	cp src/*.h ${PREFIX}/include

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
	$(PROTODIR)/bin/protoc -I$(CURDIR) --cpp_out=$(CURDIR) $(CURDIR)/$^

test.pb.o: test/test.pb.cc
	$(CXX) $(CPPFLAGS) -c -o $@ $^

jansson2pb-util: util/main.cpp test.pb.o libjansson2pb.a
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR) -o main.o util/main.cpp
	$(CXX) $(LDFLAGS) -o jansson2pb-util main.o test.pb.o libjansson2pb.a -lprotobuf

jansson2pb-test: test/test.cpp test.pb.o libjansson2pb.a
	$(CXX) $(CPPFLAGS) -c -I$(CURDIR) -o test.o test/test.cpp
	$(CXX) $(LDFLAGS) -o jansson2pb-test test.o test.pb.o libjansson2pb.a -lprotobuf

