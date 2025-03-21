/* Copyright (c) 2002,2003 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the 
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE-1.0 or http://www.boost.org/LICENSE-1.0)
 * Author: Jeff Garland, Bart Garst
 * $Date: 2003/11/23 03:37:47 $
 */



#ifndef BOOST_DATE_TIME_SOURCE
#define BOOST_DATE_TIME_SOURCE
#endif
#include "boost/date_time/gregorian/greg_weekday.hpp"

namespace boost {
namespace gregorian {

  const char* const short_weekday_names[]={"Sun", "Mon", "Tue", 
                                           "Wed", "Thu", "Fri", "Sat"};
  const char* const long_weekday_names[]= {"Sunday","Monday","Tuesday",
                                           "Wednesday", "Thursday",
                                           "Friday", "Saturday"};


  //! Return a 3 digit english string of the day of week (eg: Sun)
  const char*
  greg_weekday::as_short_string() const 
  {
    return short_weekday_names[value_];
  }
  //! Return a point to a long english string representing day of week
  const char*
  greg_weekday::as_long_string()  const 
  {
    return long_weekday_names[value_];
  }
  
} } //namespace gregorian

