//  copyright_check header  --------------------------------------------------//

//  Copyright Beman Dawes 2002, 2003.
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COPYRIGHT_CHECK_HPP
#define BOOST_COPYRIGHT_CHECK_HPP

#include "inspector.hpp"

namespace boost
{
  namespace inspect
  {
    class copyright_check : public inspector
    {
      long m_files_with_errors;
    public:

      copyright_check();
      virtual const char * name() const { return "copyright-check"; }
      virtual const char * desc() const { return "missing copyright"; }

      virtual void inspect(
        const std::string & library_name,
        const path & full_path,
        const std::string & contents );

      virtual ~copyright_check()
        { std::cout << "  " << m_files_with_errors << " files missing copyrights\n"; }
    };
  }
}

#endif // BOOST_COPYRIGHT_CHECK_HPP
