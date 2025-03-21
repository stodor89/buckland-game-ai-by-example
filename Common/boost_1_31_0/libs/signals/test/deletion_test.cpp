// Boost.Signals library

// Copyright Doug Gregor 2001-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#define BOOST_INCLUDE_MAIN
#include <boost/test/test_tools.hpp>
#include <boost/signal.hpp>
#include <iostream>
#include <string>

static boost::BOOST_SIGNALS_NAMESPACE::connection connections[5];

static std::string test_output;

struct remove_connection {
  explicit remove_connection(int v = 0, int i = -1) : value(v), idx(i) {}

  void operator()() const {
    if (idx >= 0)
      connections[idx].disconnect();

    //return value;
    std::cout << value << " ";

    test_output += static_cast<char>(value + '0');
  }

  int value;
  int idx;
};

static void
test_remove_self()
{
  boost::signal0<void> s0;

  connections[0] = s0.connect(remove_connection(0));
  connections[1] = s0.connect(remove_connection(1));
  connections[2] = s0.connect(remove_connection(2, 2));
  connections[3] = s0.connect(remove_connection(3));

  std::cout << "Deleting 2" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "0123");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "013");

  s0.disconnect_all_slots();
  BOOST_TEST(s0.empty());

  connections[0] = s0.connect(remove_connection(0));
  connections[1] = s0.connect(remove_connection(1));
  connections[2] = s0.connect(remove_connection(2));
  connections[3] = s0.connect(remove_connection(3, 3));

  std::cout << "Deleting 3" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "0123");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "012");

  s0.disconnect_all_slots();
  BOOST_TEST(s0.num_slots() == 0);

  connections[0] = s0.connect(remove_connection(0, 0));
  connections[1] = s0.connect(remove_connection(1));
  connections[2] = s0.connect(remove_connection(2));
  connections[3] = s0.connect(remove_connection(3));

  std::cout << "Deleting 0" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "0123");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "123");

  s0.disconnect_all_slots();
  BOOST_TEST(s0.empty());

  connections[0] = s0.connect(remove_connection(0, 0));
  connections[1] = s0.connect(remove_connection(1, 1));
  connections[2] = s0.connect(remove_connection(2, 2));
  connections[3] = s0.connect(remove_connection(3, 3));

  std::cout << "Mass suicide" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "0123");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "");
}

static void
test_remove_prior()
{
  boost::signal0<void> s0;

  connections[0] = s0.connect(remove_connection(0));
  connections[1] = s0.connect(remove_connection(1, 0));
  connections[2] = s0.connect(remove_connection(2));
  connections[3] = s0.connect(remove_connection(3));

  std::cout << "1 removes 0" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "0123");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "123");

  s0.disconnect_all_slots();
  BOOST_TEST(s0.empty());

  connections[0] = s0.connect(remove_connection(0));
  connections[1] = s0.connect(remove_connection(1));
  connections[2] = s0.connect(remove_connection(2));
  connections[3] = s0.connect(remove_connection(3, 2));

  std::cout << "3 removes 2" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "0123");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "013");
}

static void
test_remove_after()
{
  boost::signal0<void> s0;

  connections[0] = s0.connect(remove_connection(0, 1));
  connections[1] = s0.connect(remove_connection(1));
  connections[2] = s0.connect(remove_connection(2));
  connections[3] = s0.connect(remove_connection(3));

  std::cout << "0 removes 1" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "023");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "023");

  s0.disconnect_all_slots();
  BOOST_TEST(s0.empty());

  connections[0] = s0.connect(remove_connection(0));
  connections[1] = s0.connect(remove_connection(1, 3));
  connections[2] = s0.connect(remove_connection(2));
  connections[3] = s0.connect(remove_connection(3));

  std::cout << "1 removes 3" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "012");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "012");
}

static void
test_bloodbath()
{
  boost::signal0<void> s0;

  connections[0] = s0.connect(remove_connection(0, 1));
  connections[1] = s0.connect(remove_connection(1, 1));
  connections[2] = s0.connect(remove_connection(2, 0));
  connections[3] = s0.connect(remove_connection(3, 2));

  std::cout << "0 removes 1, 2 removes 0, 3 removes 2" << std::endl;

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "023");

  test_output = "";
  s0(); std::cout << std::endl;
  BOOST_TEST(test_output == "3");
}

int test_main(int, char* [])
{
  test_remove_self();
  test_remove_prior();
  test_remove_after();
  test_bloodbath();
  return 0;
}
