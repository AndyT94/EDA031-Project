#include <string>

#ifndef PROTOCOL_VIOLATION_EXCEPTION_H
#define PROTOCOL_VIOLATION_EXCEPTION_H

struct ProtocolViolationException {
	std::string message;
	std::string error;
	int prot_id;
	int code;
	ProtocolViolationException(const std::string& m, int p, int c) :
    message(m), prot_id(p), code(c) {}

	ProtocolViolationException(const std::string& m, const std::string& e) : message(m), error(e) {}
};
#endif
