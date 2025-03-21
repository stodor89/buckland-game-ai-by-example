//  license_check header  ----------------------------------------------------//

//  Copyright Beman Dawes 2002, 2003.
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LICENSE_CHECK_HPP
#define BOOST_LICENSE_CHECK_HPP

#include "inspector.hpp"

namespace boost
{
  namespace inspect
  {
    class license_check : public inspector
    {
      long m_files_with_errors;
    public:

      license_check();
      virtual const char * name() const { return "license-check"; }
      virtual const char * desc() const { return "missing Boost license info"; }

      virtual void inspect(
        const std::string & library_name,
        const path & full_path,
        const std::string & contents );

      virtual ~license_check()
        { std::cout << "  "
            << m_files_with_errors << " files missing Boost license info\n"; }
    };
  }
}

#endif // BOOST_LICENSE_CHECK_HPP
