.. Copyright David Abrahams 2004. Use, modification and distribution is
.. subject to the Boost Software License, Version 1.0. (See accompanying
.. file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

In this section we'll walk through the implementation of a few
iterators using ``iterator_facade``, based around the simple
example of a linked list of polymorphic objects.  This example was
inspired by a `posting`__ by Keith Macdonald on the `Boost-Users`_
mailing list.

.. _`Boost-Users`: ../../../more/mailing_lists.htm#users

__ http://thread.gmane.org/gmane.comp.lib.boost.user/5100

The Problem
-----------

Say we've written a polymorphic linked list node base class::

  # include <iostream>

  struct node_base
  {
      node_base() : m_next(0) {}

      // Each node manages all of its tail nodes
      virtual ~node_base() { delete m_next; }

      // Access the rest of the list
      node_base* next() const { return m_next; }

      // print to the stream
      virtual void print(std::ostream& s) const = 0;
      
      // double the value
      virtual void double_me() = 0;

      void append(node_base* p)
      {
          if (m_next) 
              m_next->append(p); 
          else
              m_next = p; 
      }

   private:
      node_base* m_next;
  };

Lists can hold objects of different types by linking together
specializations of the following template::

  template <class T>
  struct node : node_base
  {
      node(T x)
        : m_value(x)
      {}

      void print(std::ostream& s) const { s << this->m_value; }
      void double_me() { m_value += m_value; }

   private:
      T m_value;
  };

And we can print any node using the following streaming operator::

  inline std::ostream& operator<<(std::ostream& s, node_base const& n)
  {
      n.print(s);
      return s;
  }

Our first challenge is to build an appropriate iterator over these
lists.

A Basic Iterator Using ``iterator_facade``
------------------------------------------

We will construct a ``node_iterator`` class using inheritance from
``iterator_facade`` to implement most of the iterator's operations.

::

  # include "node.hpp"
  # include <boost/iterator/iterator_facade.hpp>

  class node_iterator
    : public boost::iterator_facade<...>
  {
     ...
  };



Template Arguments for ``iterator_facade``
..........................................

``iterator_facade`` has several template parameters, so we must decide
what types to use for the arguments. The parameters are ``Derived``,
``Value``, ``CategoryOrTraversal``, ``Reference``, and ``Difference``.


``Derived``
'''''''''''

Because ``iterator_facade`` is meant to be used with the CRTP
[Cop95]_ the first parameter is the iterator class name itself,
``node_iterator``.

``Value``
'''''''''

The ``Value`` parameter determines the ``node_iterator``\ 's
``value_type``.  In this case, we are iterating over ``node_base``
objects, so ``Value`` will be ``node_base``.


``CategoryOrTraversal``
'''''''''''''''''''''''

Now we have to determine which `iterator traversal concept`_ our
``node_iterator`` is going to model.  Singly-linked lists only have
forward links, so our iterator can't can't be a `bidirectional
traversal iterator`_.  Our iterator should be able to make multiple
passes over the same linked list (unlike, say, an
``istream_iterator`` which consumes the stream it traverses), so it
must be a `forward traversal iterator`_.  Therefore, we'll pass
``boost::forward_traversal_tag`` in this position [#category]_.

.. [#category] ``iterator_facade`` also supports old-style category
   tags, so we could have passed ``std::forward_iterator_tag`` here;
   either way, the resulting iterator's ``iterator_category`` will
   end up being ``std::forward_iterator_tag``.

``Reference``
'''''''''''''

The ``Reference`` argument becomes the type returned by
``node_iterator``\ 's dereference operation, and will also be the
same as ``std::iterator_traits<node_iterator>::reference``.  The
library's default for this parameter is ``Value&``; since
``node_base&`` is a good choice for the iterator's ``reference``
type, we can omit this argument, or pass ``use_default``.

``Difference``
''''''''''''''

The ``Difference`` argument determines how the distance between
two ``node_iterator``\ s will be measured and will also be the
same as ``std::iterator_traits<node_iterator>::difference_type``.
The library's default for ``Difference`` is ``std::ptrdiff_t``, an
appropriate type for measuring the distance between any two
addresses in memory, and one that works for almost any iterator,
so we can omit this argument, too.

The declaration of ``node_iterator`` will therefore look something
like::

  # include "node.hpp"
  # include <boost/iterator/iterator_facade.hpp>

  class node_iterator
    : public boost::iterator_facade<
          node_iterator
        , node_base
        , boost::forward_traversal_tag
      >
  {
     ...
  };

Constructors and Data Members
.............................

Next we need to decide how to represent the iterator's position.
This representation will take the form of data members, so we'll
also need to write constructors to initialize them.  The
``node_iterator``\ 's position is quite naturally represented using
a pointer to a ``node_base``.  We'll need a constructor to build an
iterator from a ``node_base*``, and a default constructor to
satisfy the `forward traversal iterator`_ requirements [#default]_.
Our ``node_iterator`` then becomes::

  # include "node.hpp"
  # include <boost/iterator/iterator_facade.hpp>

  class node_iterator
    : public boost::iterator_facade<
          node_iterator
        , node_base
        , boost::forward_traversal_tag
      >
  {
   public:
      node_iterator()
        : m_node(0)
      {}

      explicit node_iterator(node_base* p)
        : m_node(p)
      {}

   private:
      ...
      node_base* m_node;
  };

.. [#default] Technically, the C++ standard places almost no
   requirements on a default-constructed iterator, so if we were
   really concerned with efficiency, we could've written the
   default constructor to leave ``m_node`` uninitialized.

Implementing the Core Operations
................................

The last step is to implement the `core operations`_ required by
the concepts we want our iterator to model.  Referring to the
table__, we can see that the first three rows are applicable
because ``node_iterator`` needs to satisfy the requirements for
`readable iterator`_, `single pass iterator`_, and `incrementable
iterator`_.  

__ `core operations`_

We therefore need to supply ``dereference``,
``equal``, and ``increment`` members.  We don't want these members
to become part of ``node_iterator``\ 's public interface, so we can
make them private and grant friendship to
``boost::iterator_core_access``, a "back-door" that
``iterator_facade`` uses to get access to the core operations::

  # include "node.hpp"
  # include <boost/iterator/iterator_facade.hpp>

  class node_iterator
    : public boost::iterator_facade<
          node_iterator
        , node_base
        , boost::forward_traversal_tag
      >
  {
   public:
      node_iterator()
        : m_node(0) {}

      explicit node_iterator(node_base* p)
        : m_node(p) {}

   private:
      friend class boost::iterator_core_access;

      void increment() { m_node = m_node->next(); }

      bool equal(node_iterator const& other) const
      {
          return this->m_node == other.m_node;
      }

      node_base& dereference() const { return *m_node; }

      node_base* m_node;
  };

Voil�; a complete and conforming readable, forward-traversal
iterator!  For a working example of its use, see `this program`__.

__ ../example/node_iterator1.cpp

A constant ``node_iterator``
----------------------------

.. Sidebar:: Constant and Mutable iterators

   The term **mutable iterator** means an iterator through which
   the object it references (its "referent") can be modified.  A
   **constant iterator** is one which doesn't allow modification of
   its referent.  

   The words *constant* and *mutable* don't refer to the ability to
   modify the iterator itself.  For example, an ``int const*`` is a
   non-\ ``const`` *constant iterator*, which can be incremented
   but doesn't allow modification of its referent, and ``int*
   const`` is a ``const`` *mutable iterator*, which cannot be
   modified but which allows modification of its referent.

   Confusing?  We agree, but those are the standard terms.  It
   probably doesn't help much that a container's constant iterator
   is called ``const_iterator``.

Now, our ``node_iterator`` gives clients access to both ``node``\
's ``print(std::ostream&) const`` member function, but also its
mutating ``double_me()`` member.  If we wanted to build a
*constant* ``node_iterator``, we'd only have to make three
changes:

.. parsed-literal::

  class const_node_iterator
    : public boost::iterator_facade<
          node_iterator
        , node_base **const**
        , boost::forward_traversal_tag
      >
  {
   public:
      const_node_iterator()
        : m_node(0) {}

      explicit const_node_iterator(node_base* p)
        : m_node(p) {}

   private:
      friend class boost::iterator_core_access;

      void increment() { m_node = m_node->next(); }

      bool equal(const_node_iterator const& other) const
      {
          return this->m_node == other.m_node;
      }

      node_base **const**\ & dereference() const { return \*m_node; }

      node_base **const**\ * m_node;
  };

.. Sidebar:: ``const`` and an iterator's ``value_type``

   The C++ standard requires an iterator's ``value_type`` *not* be
   ``const``\ -qualified, so ``iterator_facade`` strips the
   ``const`` from its ``Value`` parameter in order to produce the
   iterator's ``value_type``.  Making the ``Value`` argument
   ``const`` provides a useful hint to ``iterator_facade`` that the
   iterator is a *constant iterator*, and the default ``Reference``
   argument will be correct for all lvalue iterators.

As a matter of fact, ``node_iterator`` and ``const_node_iterator``
are so similar that it makes sense to factor the common code out
into a template as follows::

  template <class Value>
  class node_iter
    : public boost::iterator_facade<
          node_iter<Value>
        , Value
        , boost::forward_traversal_tag
      >
  {
   public:
      node_iter()
        : m_node(0) {}

      explicit node_iter(Value* p)
        : m_node(p) {}

   private:
      friend class boost::iterator_core_access;

      bool equal(node_iter<Value> const& other) const
      {
          return this->m_node == other.m_node;
      }

      void increment()
      { m_node = m_node->next(); }

      Value& dereference() const
      { return *m_node; }

      Value* m_node;
  };
  typedef node_iter<node_base> node_iterator;
  typedef node_iter<node_base const> node_const_iterator;


Interoperability
----------------

Our ``const_node_iterator`` works perfectly well on its own, but
taken together with ``node_iterator`` it doesn't quite meet
expectations.  For example, we'd like to be able to pass a
``node_iterator`` where a ``node_const_iterator`` was expected,
just as you can with ``std::list<int>``\ 's ``iterator`` and
``const_iterator``.  Furthermore, given a ``node_iterator`` and a
``node_const_iterator`` into the same list, we should be able to
compare them for equality.

This expected ability to use two different iterator types together
is known as |interoperability|_.  Achieving interoperability in
our case is as simple as templatizing the ``equal`` function and
adding a templatized converting constructor [#broken]_ [#random]_::

  template <class Value>
  class node_iter
    : public boost::iterator_facade<
          node_iter<Value>
        , Value
        , boost::forward_traversal_tag
      >
  {
   public:
      node_iter()
        : m_node(0) {}

      explicit node_iter(Value* p)
        : m_node(p) {}

      template <class OtherValue>
      node_iter(node_iter<OtherValue> const& other)
        : m_node(other.m_node) {}

   private:
      friend class boost::iterator_core_access;
      template <class> friend class node_iter;

      template <class OtherValue>
      bool equal(node_iter<OtherValue> const& other) const
      { 
          return this->m_node == other.m_node;
      }

      void increment()
      { m_node = m_node->next(); }

      Value& dereference() const
      { return *m_node; }

      Value* m_node;
  };
  typedef impl::node_iterator<node_base> node_iterator;
  typedef impl::node_iterator<node_base const> node_const_iterator;

.. |interoperability| replace:: **interoperability**
.. _interoperability: new-iter-concepts.html#interoperable-iterators-lib-interoperable-iterators

.. [#broken] If you're using an older compiler and it can't handle
   this example, see the `example code`__ for workarounds.

.. [#random] If ``node_iterator`` had been a `random access
   traversal iterator`_, we'd have had to templatize its
   ``distance_to`` function as well.


__ ../example/node_iterator2.hpp

You can see an example program which exercises our interoperable
iterators `here`__.

__ ../example/node_iterator2.cpp

Telling the Truth
-----------------

Now ``node_iterator`` and ``node_const_iterator`` behave exactly as
you'd expect... almost.  We can compare them and we can convert in
one direction: from ``node_iterator`` to ``node_const_iterator``.
If we try to convert from ``node_const_iterator`` to
``node_iterator``, we'll get an error when the converting
constructor tries to initialize ``node_iterator``\ 's ``m_node``, a
``node*`` with a ``node const*``.  So what's the problem?

The problem is that
``boost::``\ |is_convertible|_\ ``<node_const_iterator,node_iterator>::value``
will be ``true``, but it should be ``false``.  |is_convertible|_
lies because it can only see as far as the *declaration* of
``node_iter``\ 's converting constructor, but can't look inside at
the *definition* to make sure it will compile.  A perfect solution
would make ``node_iter``\ 's converting constructor disappear when
the ``m_node`` conversion would fail.

.. |is_convertible| replace:: ``is_convertible``
.. _is_convertible:  ../../type_traits/index.html#relationships

In fact, that sort of magic is possible using
|enable_if|__.  By rewriting the converting constructor as
follows, we can remove it from the overload set when it's not
appropriate::

  #include <boost/type_traits/is_convertible.hpp>
  #include <boost/utility/enable_if.hpp>

    ...

    template <class OtherValue>
    node_iter(
        node_iter<OtherValue> const& other
      , typename boost::enable_if<
            boost::is_convertible<OtherValue*,Value*>
          , enabler
        >::type = enabler()
    )
      : m_node(other.m_node) {}

.. |enable_if| replace:: ``boost::enable_if``
__ ../../utility/enable_if.html


Wrap Up
-------

This concludes our ``iterator_facade`` tutorial, but before you
stop reading we urge you to take a look at |iterator_adaptor|__.
There's another way to approach writing these iterators which might
even be superior.

.. |iterator_adaptor| replace:: ``iterator_adaptor``
__ iterator_adaptor.html

.. _`iterator traversal concept`: new-iter-concepts.html#iterator-traversal-concepts-lib-iterator-traversal
.. _`readable iterator`: new-iter-concepts.html#readable-iterators-lib-readable-iterators
.. _`lvalue iterator`: new-iter-concepts.html#lvalue-iterators-lib-lvalue-iterators
.. _`single pass iterator`: new-iter-concepts.html#single-pass-iterators-lib-single-pass-iterators
.. _`incrementable iterator`: new-iter-concepts.html#incrementable-iterators-lib-incrementable-iterators
.. _`forward traversal iterator`: new-iter-concepts.html#forward-traversal-iterators-lib-forward-traversal-iterators
.. _`bidirectional traversal iterator`: new-iter-concepts.html#bidirectional-traversal-iterators-lib-bidirectional-traversal-iterators
.. _`random access traversal iterator`: new-iter-concepts.html#random-access-traversal-iterators-lib-random-access-traversal-iterators

