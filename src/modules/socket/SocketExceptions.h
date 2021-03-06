/**
 * Copyright (c) 2012 - 2014 TideSDK contributors
 * http://www.tidesdk.org
 * Refer to LICENSE for details of distribution and use.
 **/

#ifndef _SOCKET_EXCEPTIONS_H_
#define _SOCKET_EXCEPTIONS_H_

#include <exception>

class SocketException : public std::exception
{
public:
	virtual const char * what() const throw()
	{ return "Socket Exception"; }
};

class TCPSocketException : public SocketException
{
public:
	virtual const char * what() const throw()
	{ return "TCPSocket: Exception"; }
};

class TCPSocketConnectedException : public TCPSocketException
{
public:
	virtual const char * what() const throw()
	{ return "TCPSocket: either socket is connected or connecting."; }
};

class TCPSocketWriteException : public TCPSocketException
{
public:
	virtual const char * what() const throw()
	{ return "TCPSocket: socket is not open for write."; }
};

class TCPSocketReadNotOpenException : public TCPSocketException
{
public:
	virtual const char * what() const throw()
	{ return "TCPSocket: socket is not open for read."; }
};

class TCPSocketReadException : public TCPSocketException
{
public:
	virtual const char * what() const throw()
	{ return "TCPSocket: socket error while reading from socket."; }
};

#endif
