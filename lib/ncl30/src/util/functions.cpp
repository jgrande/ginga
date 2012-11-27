#include "functions.h"
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <util/log.h>

namespace ncl_util {

#define CHECK_RANGE(var,min,max)				\
	{ if (var < min) var = min; else if (var > max) var = max; }

double NaN() {
	return -1.0;
}

double infinity() {
	return std::numeric_limits<double>().infinity();
}

bool isNaN( double value ) {
	return value < 0;
}

bool isInfinity( double value ) {
	return value == std::numeric_limits<double>().infinity();
}

int getPixelValue( const std::string &value, bool throwException ) {

	int pValue = 0;

	std::string actualValue = value;
	boost::trim( actualValue );
	boost::trim_right_if( actualValue, boost::is_any_of( "px" ) );

	try {
		pValue = boost::lexical_cast<int>( boost::trim_copy( actualValue ) );
	} catch (boost::bad_lexical_cast &) {
		if (throwException) {
			throw;
		}
	}

	return pValue;
}

float getPercentualValue( const std::string &value, bool throwException ) {

	float pValue = 0.0;

	std::string actualValue = value;
	boost::trim( actualValue );
	boost::trim_right_if( actualValue, boost::is_any_of( "%" ) );
	try {
		pValue = boost::lexical_cast<float>( actualValue ) / 100;
		if (!throwException) {
			CHECK_RANGE( pValue, 0, 1 );
		}
	} catch (boost::bad_lexical_cast &) {
		if (throwException) {
			throw;
		}
	}

	return pValue;
}

bool isPercentualValue( const std::string &value ) {
	std::string v = value;
	boost::trim( v );
	return v.find( "%" ) == v.size() - 1;
}

bool isValidNumericValue( const std::string &value ) {
	bool result = true;
	try {
		if (isPercentualValue( value )) {
			float percentualValue = getPercentualValue( value, true );
			if ((percentualValue > 1) || (percentualValue < 0)) {
				LERROR("ncl30", "The value %s must be between 0 and 100", value.c_str());
				result = false;
			}
		} else {
			int pxValue = getPixelValue( value, true );
			if (pxValue < 0) {
				LERROR("ncl30", "The value %s is invalid", value.c_str());
				result = false;
			}
		}
	} catch (boost::bad_lexical_cast &) {
		LERROR("ncl30", "The value %s is invalid", value.c_str());
		result = false;
	}
	return result;
}
}
