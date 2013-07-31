jansson2pb
==========

jansson fork with google protobuf functionality
https://github.com/novator24/jansson2pb/wiki/

HOWTO

That is a fork of the jansson project (C-library for json). Source files of jansson project are saved in src folder. Extra files are saved in 3party folder.

To compile and test new C++ library do the following:

cd ~/jansson2pb

./configure --prefix=/usr/local

make

make test

make install

Email: novator24 [@] gmail dot com

What is protobuf?

Protocol buffers are Google's language-neutral, platform-neutral, extensible mechanism for serializing structured data – think XML, but smaller, faster, and simpler. You define how you want your data to be structured once, then you can use special generated source code to easily write and read your structured data to and from a variety of data streams and using a variety of languages – Java, C++, or Python.

Google protobuf home page.

What can you do with that library?

void json2pb(google::protobuf::Message &msg, const char *buf, size_t size);

That method allows you to convert json message to google::protobuf object.

std::string pb2json(const google::protobuf::Message &msg);

That method allows you to convert google::protobuf object to json message.

Exceptions.

First method json2pb(...) throws std::exception on errors.

Example.

There are some examples in the file test/test.cpp.

    Test 1: read binary PB from a file and convert it to JSON

    Test 2: convert PB to JSON directly

    Test 3: read valid json from a file and fill PB object

    Test 4: read invalid json from a file and catch j2pb_error

Credits.

Pavel Shramov is the author of json2pb library. Three header files are exported from that repository.

P.S.

Current Jansson version is 2.4.

