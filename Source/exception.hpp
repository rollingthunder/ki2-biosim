/**
 *************************************************************************
 *
 * @file exception.hpp
 *
 * Exception classes.
 *
 ************************************************************************/


#if !defined(INCLUDED_EXCEPTION_HPP)
#define INCLUDED_EXCEPTION_HPP


#include "build_config.hpp"


namespace biosim
{


/**
 *************************************************************************
 * Thrown whenever some input parameter had an invalid value.
 ************************************************************************/
class invalid_parameter : public std::exception
{
	public:
		virtual const char* what() const NOTHROW
			{ return "Invalid parameter."; }
};


/**
 *************************************************************************
 * Thrown whenever a file could not be opened.
 ************************************************************************/
class file_operation_failed : public std::exception
{
	public:
		virtual const char* what() const NOTHROW
			{ return "File operation failed."; }
};


/**
 *************************************************************************
 * Thrown whenever maximum bounds of some array or object are exceeded.
 ************************************************************************/
class bounds_exceeded : public std::exception
{
	public:
		virtual const char* what() const NOTHROW
			{ return "Boundaries exceeded."; }
};


/**
 *************************************************************************
 * Thrown whenever a runtime assertion failed.
 ************************************************************************/
class assert_failed : public std::exception
{
	public:
		virtual const char* what() const NOTHROW
			{ return "Runtime assertion failed."; }
};


/**
 *************************************************************************
 * Thrown whenever corrupt file data was encountered.
 ************************************************************************/
class corrupt_data : public std::exception
{
	public:
		virtual const char* what() const NOTHROW
			{ return "Corrupt file encountered."; }
};


/**
 *************************************************************************
 * Thrown whenever a certain feature was not supported by the application.
 ************************************************************************/
class unsupported_feature : public std::exception
{
	public:
		virtual const char* what() const NOTHROW
			{ return "An unsupported feature was used."; }
};


/**
 *************************************************************************
 * Thrown whenever compression or decompression failed.
 ************************************************************************/
class compression_failed : public std::exception
{
	public:
		virtual const char* what() const NOTHROW
			{ return "Compression or decompression failed."; }
};




} /* namespace biosim */


#endif /* !defined(INCLUDED_EXCEPTION_HPP) */