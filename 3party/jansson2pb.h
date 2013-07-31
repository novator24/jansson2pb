/*
 * Copyright (c) 2013 Anonymous <novator24@gmail.com>
 * *
 * * It is a fork of json2pb project (author Pavel Shramov)
 *
 * jansson2pb is free software; you can redistribute it and/or modify
 * it under the terms of the MIT license. See LICENSE for details.
 */

#ifndef __JANSSON2PB_H__
#define __JANSSON2PB_H__

#include <string>
#include <google/protobuf/descriptor.h>

namespace google {
namespace protobuf {
class Message;
}
}

class j2pb_error : public std::exception {
	std::string _error;
public:
	j2pb_error(const std::string &e) : _error(e) {}
	j2pb_error(const google::protobuf::FieldDescriptor *field, const std::string &e) : _error(field->name() + ": " + e) {}
	virtual ~j2pb_error() throw() {};

	virtual const char *what() const throw () { return _error.c_str(); };
};

void json2pb(google::protobuf::Message &msg, const char *buf, size_t size);
std::string pb2json(const google::protobuf::Message &msg);

#endif//__JANSSON2PB_H__
