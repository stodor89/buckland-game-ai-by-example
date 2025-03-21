//  crfl_check header  --------------------------------------------------------//

//  Copyright Beman Dawes 2002.
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  Contributed by Joerg Walter

#ifndef BOOST_CRLF_CHECK_HPP
#define BOOST_CRLF_CHECK_HPP

#include "inspector.hpp"

namespace boost
{
  namespace inspect
  {
    class crlf_check : public inspector
    {
      long m_files_with_errors;
    public:

      crlf_check();
      virtual const char * name() const { return "crlf-check"; }
      virtual const char * desc() const { return "invalid (cr only) line-ending"; }

      virtual void inspect(
        const std::string & library_name,
        const path & full_path,
        const std::string & contents );

      virtual ~crlf_check()
        { std::cout << "  " << m_files_with_errors << " files with invalid line endings\n"; }
    };
  }
}

#endif // BOOST_CRLF_CHECK_HPP
