//  Boost config.hpp configuration test program file  -----------------------//

//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Jens Maurer 2001. 
//  (C) Copyright Peter Dimov 2001. 
//  (C) Copyright Darin Adler 2001. 
//  (C) Copyright Beman Dawes 2002. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/config for most recent version.

#include <boost/config.hpp>
#include <boost/version.hpp>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <limits.h>

#ifdef BOOST_HAS_UNISTD_H
#include <unistd.h>
#endif

static unsigned int indent = 4;
static unsigned int width = 40;

using std::cout;
using std::istream;

void print_macro(const char* name, const char* value)
{
   // if name == value+1 then then macro is not defined,
   // in which case we don't print anything:
   if(0 != strcmp(name, value+1))
   {
      for(unsigned i = 0; i < indent; ++i) std::cout.put(' ');
      std::cout << std::setw(width);
      cout.setf(istream::left, istream::adjustfield);
      std::cout << name;
      if(value[1])
      {
         // macro has a value:
         std::cout << value << "\n";
      }
      else
      {
         // macro is defined but has no value:
         std::cout << " [no value]\n";
      }
   }
}

#define PRINT_MACRO(X) print_macro(#X, BOOST_STRINGIZE(=X))

template <class T>
void print_expression(const char* expression, T val)
{
   for(unsigned i = 0; i < indent; ++i) std::cout.put(' ');
   std::cout << std::setw(width);
   std::cout.setf(istream::left, istream::adjustfield);
   std::cout << expression << "=" << val << std::endl;
}

#define PRINT_EXPRESSION(E) print_expression(#E, E);

template <class T>
void print_byte_order(const char* what, T /* t */ )
{
   T val = 0;
   unsigned i;
   for(i = 1; i < sizeof(T); ++i)
   {
      val |= (CHAR_BIT * i) << (CHAR_BIT * i);
   }
   const char* p = reinterpret_cast<const char*>(&val);

   for(i = 0; i < indent; ++i) std::cout.put(' ');
   std::cout << std::setw(width);
   std::cout.setf(istream::left, istream::adjustfield);
   std::cout << what << "=";
   for(i = 0; i < sizeof(T); ++i)
   {
      std::cout << (int)p[i] << " ";
   }
   std::cout << std::endl;
}

#define PRINT_ORDER(T) print_byte_order(BOOST_STRINGIZE(byte order for type T), T())

template <class T>
void print_sign(const char* what, T t)
{
   t = static_cast<T>(-1);  // cast suppresses warnings
   for(unsigned i = 0; i < indent; ++i) std::cout.put(' ');
   std::cout << "Type " << what << " is " << ((t > 0) ? "unsigned" : "signed") << std::endl;
}

#define PRINT_SIGN(T) print_sign(#T, T())


void print_compiler_macros()
{
   std::cout << BOOST_COMPILER << "\n";
   // Borland options:
  PRINT_MACRO(__BORLANDC__);
  PRINT_MACRO(__CDECL__);
  PRINT_MACRO(_CHAR_UNSIGNED);
  PRINT_MACRO(__CODEGUARD__);
  PRINT_MACRO(__CONSOLE__);
  PRINT_MACRO(_CPPUNWIND);
  PRINT_MACRO(__cplusplus);
  PRINT_MACRO(__FLAT__);
  PRINT_MACRO(__FUNC__);
  PRINT_MACRO(_M_IX86);
  PRINT_MACRO(__MSDOS__);
  PRINT_MACRO(__MT__ );
  PRINT_MACRO(__PASCAL__);
  PRINT_MACRO(__STDC__);
  PRINT_MACRO(__TLS__);
  PRINT_MACRO(_WCHAR_T);
  PRINT_MACRO(_Windows);
  PRINT_MACRO(__WIN32__);
  PRINT_MACRO(_WIN32);
  PRINT_MACRO(WIN32);
  PRINT_MACRO(_RTLDLL);
  PRINT_MACRO(__DEBUG);

// Internal MSVC 7 error workaround (Peter Dimov)

#ifndef _NATIVE_WCHAR_T_DEFINED
  PRINT_MACRO(_WCHAR_T_DEFINED);
#endif
  // MSVC macros:
  PRINT_MACRO(_CPPRTTI);
  PRINT_MACRO(_DLL);
  PRINT_MACRO(_M_ALPHA);
  PRINT_MACRO(_M_MPPC);
  PRINT_MACRO(_M_MRX000);
  PRINT_MACRO(_M_PPC);
  PRINT_MACRO(_MFC_VER);
  PRINT_MACRO(_MSC_EXTENSIONS);
  PRINT_MACRO(_MSC_VER);
  PRINT_MACRO(_MT);
  PRINT_MACRO(_NATIVE_WCHAR_T_DEFINED);
  // GNUC options:
  PRINT_MACRO(__GNUC__);
  PRINT_MACRO(__GNUC_MINOR__);
  PRINT_MACRO(__STDC_VERSION__);
  PRINT_MACRO(__GNUG__);
  PRINT_MACRO(__STRICT_ANSI__);
  PRINT_MACRO(__VERSION__);
  PRINT_MACRO(__OPTIMIZE__);
  PRINT_MACRO(__CHAR_UNSIGNED__);
  PRINT_MACRO(__REGISTER_PREFIX__);
  PRINT_MACRO(__USER_LABEL_PREFIX__);
  PRINT_MACRO(__INTEL__);
  PRINT_MACRO(__GNUPRO__);
  PRINT_MACRO(__EXCEPTIONS);
  PRINT_MACRO(__FreeBSD__);
  PRINT_MACRO(__FreeBSD_cc_version);
  PRINT_MACRO(__ELF__);
  PRINT_MACRO(__GNUPRO__);
  PRINT_MACRO(unix);
  PRINT_MACRO(bsd);
  PRINT_MACRO(vax);
  PRINT_MACRO(mc68000);
  PRINT_MACRO(m68k);
  PRINT_MACRO(M68020);
  PRINT_MACRO(_AM29K);
  PRINT_MACRO(ns32000);
  PRINT_MACRO(sun);
  PRINT_MACRO(pyr);
  PRINT_MACRO(sequent);
  PRINT_MACRO(__i386__);
  PRINT_MACRO(__sparc);
  PRINT_MACRO(__sparc__);
  PRINT_MACRO(__powerpc__);
  PRINT_MACRO(__hppa);
  // HP aCC:
  PRINT_MACRO(__HP_aCC);
  PRINT_MACRO(_HPACC_);
  PRINT_MACRO(__LP64__);
  PRINT_MACRO(__RISC2_0__);
  PRINT_MACRO(__STDCPP__);
  PRINT_MACRO(__hppa);
  PRINT_MACRO(__hpux);
  PRINT_MACRO(__hp9000s800);
  PRINT_MACRO(__hp9000s700);
  PRINT_MACRO(_PA_RISC1_1);
  PRINT_MACRO(__HPUX_SOURCE);
  // SGI IRIX:
  PRINT_MACRO(__sgi);
  PRINT_MACRO(_COMPILER_VERSION);
  // Sunpro:
  PRINT_MACRO(__SUNPRO_CC);
  PRINT_MACRO(__SUNPRO_CC_COMPAT);
  PRINT_MACRO(__BUILTIN_VA_ARG_INCR);
  PRINT_MACRO(__sun);
  PRINT_MACRO(__SVR4);
  PRINT_MACRO(__unix);
  PRINT_MACRO(__sparcv9);
  PRINT_MACRO(__i386);
  PRINT_MACRO(i386);
  // Metrowerks
  PRINT_MACRO(__MWERKS__);
  PRINT_MACRO(__MSL__);
  PRINT_MACRO(__MSL_CPP__);
  PRINT_MACRO(__A5__);
  PRINT_MACRO(__embedded_cplusplus);
  PRINT_MACRO(__fourbyteints__);
  PRINT_MACRO(__IEEEdoubles__);
  PRINT_MACRO(__MC68K__);
  PRINT_MACRO(__MC68020__);
  PRINT_MACRO(__MC68881__);
  PRINT_MACRO(__MIPS__);
  PRINT_MACRO(__MIPS_ISA2__);
  PRINT_MACRO(__MIPS_ISA3__);
  PRINT_MACRO(__MIPS_ISA4__);
  PRINT_MACRO(__MWBROWSER__);
  PRINT_MACRO(__profile__);
  PRINT_MACRO(__powerc);
  PRINT_MACRO(_powerc);
  PRINT_MACRO(__POWERPC__);
  PRINT_MACRO(macintosh);
  PRINT_MACRO(__MACH__);
  PRINT_MACRO(__APPLE__);
  PRINT_MACRO(__APPLE_CC__);
  // MPW (MrCpp and SCpp)
  PRINT_MACRO(__MRC__);
  PRINT_MACRO(__SC__);
  PRINT_MACRO(__FPCE__);
  PRINT_MACRO(__FPCE_IEEE__);
  PRINT_MACRO(MPW_CPLUS);
  PRINT_MACRO(MPW_C);
  PRINT_MACRO(__MC601);
  PRINT_MACRO(__POWERPC);
  PRINT_MACRO(__useAppleExts__);
  PRINT_MACRO(powerc);
  PRINT_MACRO(MC68000);
  PRINT_MACRO(THINK_PLUS);
  PRINT_MACRO(mc68881);
  PRINT_MACRO(__FAR_CODE__);
  PRINT_MACRO(__FAR_DATA__);
  PRINT_MACRO(__CFM68K__);
  // EDG
  PRINT_MACRO(__EDG__);
  PRINT_MACRO(__EDG_VERSION__);
  PRINT_MACRO(c_plusplus);       // indication for strict mode
  PRINT_MACRO(_BOOL);
  PRINT_MACRO(_EXPLICIT);
  PRINT_MACRO(__SIGNED_CHARS__);
  PRINT_MACRO(_TYPENAME);
  PRINT_MACRO(_WCHAR_T);
  PRINT_MACRO(__ARRAY_OPERATORS);
  PRINT_MACRO(__EDG_ABI_COMPATIBILITY_VERSION);
  PRINT_MACRO(__EDG_IMPLICIT_USING_STD);
  PRINT_MACRO(__EDG_RUNTIME_USES_NAMESPACES);
  PRINT_MACRO(__BOOL_DEFINED);
  PRINT_MACRO(__RTTI);
  PRINT_MACRO(__PLACEMENT_DELETE);
  PRINT_MACRO(__NO_LONG_LONG);
  
  // misc compilers not covered so far:
  PRINT_MACRO(__ICC);
  PRINT_MACRO(__ICL);
  PRINT_MACRO(__ECC);
  PRINT_MACRO(__INTEL_COMPILER);
  PRINT_MACRO(__USLC__);
  PRINT_MACRO(__DECCXX);
  PRINT_MACRO(__IBMCPP__);
  PRINT_MACRO(_REENTRANT);
  PRINT_MACRO(_PTHREADS);
  PRINT_MACRO(__STDC_HOSTED__);
  PRINT_MACRO(__COMO__);
  PRINT_MACRO(__COMO_VERSION__);
}

void print_stdlib_macros()
{
   std::cout << BOOST_STDLIB << std::endl;
   #ifdef _RWSTD_VER
   // Rogue Wave 2.x config options:
   PRINT_MACRO(__NO_EDG_EXCEPTION_CLASSES);
   PRINT_MACRO(_RWSTD_ALLOCATOR);
   PRINT_MACRO(_RWSTD_BAD_ALLOC_DEFINED);
   PRINT_MACRO(_RWSTD_BAD_EXCEPTION_DEFINED);
   PRINT_MACRO(_RWSTD_BOUNDS_CHECKING);
   PRINT_MACRO(_RWSTD_COMPILE_INSTANTIATE);
   PRINT_MACRO(_RWSTD_DEFAULT_PRECISION);
   PRINT_MACRO(_RWSTD_EXCEPTION_DEFINED);
   PRINT_MACRO(_RWSTD_EXCEPTION_HANDLER_IN_STD);
   PRINT_MACRO(_RWSTD_EXCEPTION_PREDEFINED);
   PRINT_MACRO(_RWSTD_FLT_ROUNDS_IS_CONSTANT);
   PRINT_MACRO(_RWSTD_LOCALIZED_ERRORS);
   PRINT_MACRO(_RWSTD_MESSAGE);
   PRINT_MACRO(_RWSTD_MUTEXATTR_DEFAULT);
   PRINT_MACRO(_RWSTD_NO_ANSI_SPRINTF);
   PRINT_MACRO(_RWSTD_NO_ARG_MATCH);
   PRINT_MACRO(_RWSTD_NO_BAD_CAST);
   PRINT_MACRO(_RWSTD_NO_BASE_CLASS_MATCH);
   PRINT_MACRO(_RWSTD_NO_BOOL);
   PRINT_MACRO(_RWSTD_NO_BUILTIN_CTOR);
   PRINT_MACRO(_RWSTD_NO_CATOPEN_CATGETS);
   PRINT_MACRO(_RWSTD_NO_CLASS_PARTIAL_SPEC);
   PRINT_MACRO(_RWSTD_NO_COMPLEX_DEFAULT_TEMPLATES);
   PRINT_MACRO(_RWSTD_NO_COMPLICATED_EXCEPTIONS);
   PRINT_MACRO(_RWSTD_NO_COMPLICATED_TYPEDEF);
   PRINT_MACRO(_RWSTD_NO_CONST_INST);
   PRINT_MACRO(_RWSTD_NO_CTOR_RETURN);
   PRINT_MACRO(_RWSTD_NO_DEFAULT_FOR_TPARAM);
   PRINT_MACRO(_RWSTD_NO_DEFAULT_TEMPLATE_ARGS);
   PRINT_MACRO(_RWSTD_NO_DESTROY_BUILTIN);
   PRINT_MACRO(_RWSTD_NO_DESTROY_NONBUILTIN);
   PRINT_MACRO(_RWSTD_NO_EMBEDDED_TYPEDEF);
   PRINT_MACRO(_RWSTD_NO_EX_SPEC);
   PRINT_MACRO(_RWSTD_NO_EXCEPTIONS);
   PRINT_MACRO(_RWSTD_NO_EXPLICIT);
   PRINT_MACRO(_RWSTD_NO_EXPLICIT_ARG);
   PRINT_MACRO(_RWSTD_NO_EXPLICIT_FUNC_INSTANTIATION);
   PRINT_MACRO(_RWSTD_NO_EXPLICIT_INSTANTIATION);
   PRINT_MACRO(_RWSTD_NO_EXTENSION);
   PRINT_MACRO(_RWSTD_NO_FORWARD_SPECIALIZATIONS);
   PRINT_MACRO(_RWSTD_NO_FPOS_T);
   PRINT_MACRO(_RWSTD_NO_FRIEND_TEMPLATES);
   PRINT_MACRO(_RWSTD_NO_FUNC_PARTIAL_SPEC);
   PRINT_MACRO(_RWSTD_NO_GETTIMEOFDAY);
   PRINT_MACRO(_RWSTD_NO_GLOBAL_TZ);
   PRINT_MACRO(_RWSTD_NO_INHERITED_TYPEDEFS);
   PRINT_MACRO(_RWSTD_NO_INIT_CONST_TEMPLATE_REF_ARG);
   PRINT_MACRO(_RWSTD_NO_INT_TYPEDEF);
   PRINT_MACRO(_RWSTD_NO_LDIV);
   PRINT_MACRO(_RWSTD_NO_LEADING_UNDERSCORE);
   PRINT_MACRO(_RWSTD_NO_LOCALE);
   PRINT_MACRO(_RWSTD_NO_LONG_NAME);
   PRINT_MACRO(_RWSTD_NO_LONGDOUBLE);
   PRINT_MACRO(_RWSTD_NO_MBSTATE_T);
   PRINT_MACRO(_RWSTD_NO_MEM_CLASS_TEMPLATES);
   PRINT_MACRO(_RWSTD_NO_MEMBER_TEMPLATES);
   PRINT_MACRO(_RWSTD_NO_MEMBER_TYPE_TPARAM);
   PRINT_MACRO(_RWSTD_NO_MEMBER_WO_DEF_CTOR);
   PRINT_MACRO(_RWSTD_NO_MEMMOVE);
   PRINT_MACRO(_RWSTD_NO_MULTI_DIM_ARRAY);
   PRINT_MACRO(_RWSTD_NO_MUTABLE);
   PRINT_MACRO(_RWSTD_NO_NAME_INJECTION);
   PRINT_MACRO(_RWSTD_NO_NAMESPACE);
   PRINT_MACRO(_RWSTD_NO_NESTING_TEMPLATES);
   PRINT_MACRO(_RWSTD_NO_NEW_BRACKETS);
   PRINT_MACRO(_RWSTD_NO_NEW_DECL);
   PRINT_MACRO(_RWSTD_NO_NEW_HEADER);
   PRINT_MACRO(_RWSTD_NO_NEW_TEMPLATE_SYNTAX);
   PRINT_MACRO(_RWSTD_NO_NONCLASS_ARROW_RETURN);
   PRINT_MACRO(_RWSTD_NO_NONTYPE_ARGS);
   PRINT_MACRO(_RWSTD_NO_ONLY_NEEDED_INSTANTIATION);
   PRINT_MACRO(_RWSTD_NO_OVERLOAD_C_POW);
   PRINT_MACRO(_RWSTD_NO_OVERLOAD_OF_TEMPLATE_FUNCTION);
   PRINT_MACRO(_RWSTD_NO_OVERLOAD_WCHAR);
   PRINT_MACRO(_RWSTD_NO_PART_SPEC_OVERLOAD);
   PRINT_MACRO(_RWSTD_NO_RET_TEMPLATE);
   PRINT_MACRO(_RWSTD_NO_SIMPLE_DEFAULT_TEMPLATES);
   PRINT_MACRO(_RWSTD_NO_STATIC_CAST);
   PRINT_MACRO(_RWSTD_NO_STATIC_DEF);
   PRINT_MACRO(_RWSTD_NO_STATIC_DEF2);
   PRINT_MACRO(_RWSTD_NO_STATIC_DEF3);
   PRINT_MACRO(_RWSTD_NO_STATIC_MEM_DEF);
   PRINT_MACRO(_RWSTD_NO_STI_SIMPLE);
   PRINT_MACRO(_RWSTD_NO_STI_TEMPLATE);
   PRINT_MACRO(_RWSTD_NO_STREAM_LONG_DOUBLE);
   PRINT_MACRO(_RWSTD_NO_STRFTIME_CAPC);
   PRINT_MACRO(_RWSTD_NO_STRICT_TEMPLATE_INSTANTIATE);
   PRINT_MACRO(_RWSTD_NO_SWPRINTF);
   PRINT_MACRO(_RWSTD_NO_TEMPLATE_ON_RETURN_TYPE);
   PRINT_MACRO(_RWSTD_NO_TEMPLATE_TEMPLATE);
   PRINT_MACRO(_RWSTD_NO_THREADS);
   PRINT_MACRO(_RWSTD_NO_THROW_SPEC_ON_NEW);
   PRINT_MACRO(_RWSTD_NO_THROW_WITH_SHARED);
   PRINT_MACRO(_RWSTD_NO_TYPEDEF_INST);
   PRINT_MACRO(_RWSTD_NO_TYPEDEF_OVERLOAD);
   PRINT_MACRO(_RWSTD_NO_TYPENAME);
   PRINT_MACRO(_RWSTD_NO_UNDEFINED_FRIEND);
   PRINT_MACRO(_RWSTD_NO_UNINITIALIZED_STATIC_DEF);
   PRINT_MACRO(_RWSTD_NO_WCHAR_H);
   PRINT_MACRO(_RWSTD_NO_WCTYPE_H);
   PRINT_MACRO(_RWSTD_NO_WIDE_CHAR);
   PRINT_MACRO(_RWSTD_NO_WINT_TYPE);
   PRINT_MACRO(_RWSTD_NO_WSTR);
   PRINT_MACRO(_RWSTD_NOT_ALL_WSTR_CFUNCTIONS);
   PRINT_MACRO(_RWSTD_POSIX_D10_THREADS);
   PRINT_MACRO(_RWSTD_POSIX_THREADS);
   PRINT_MACRO(_RWSTD_REQUIRES_IEEEFP);
   PRINT_MACRO(_RWSTD_SOLARIS_THREADS);
   PRINT_MACRO(_RWSTD_STRUCT_TM_TZ);
   PRINT_MACRO(_RWSTD_WIDE_STRING_NULL_PROBLEM);
   #elif defined(__STD_RWCOMPILER_H__)
   // Rogue Wave 1.x std lib:
   PRINT_MACRO(__NO_EDG_EXCEPTION_CLASSES);
   PRINT_MACRO(RWSTD_ALLOCATOR);
   PRINT_MACRO(RWSTD_BAD_ALLOC_DEFINED);
   PRINT_MACRO(RWSTD_BAD_EXCEPTION_DEFINED);
   PRINT_MACRO(RWSTD_BOUNDS_CHECKING);
   PRINT_MACRO(RWSTD_COMPILE_INSTANTIATE);
   PRINT_MACRO(RWSTD_DEFAULT_PRECISION);
   PRINT_MACRO(RWSTD_EXCEPTION_DEFINED);
   PRINT_MACRO(RWSTD_EXCEPTION_HANDLER_IN_STD);
   PRINT_MACRO(RWSTD_EXCEPTION_PREDEFINED);
   PRINT_MACRO(RWSTD_FLT_ROUNDS_IS_CONSTANT);
   PRINT_MACRO(RWSTD_LOCALIZED_ERRORS);
   PRINT_MACRO(RWSTD_MESSAGE);
   PRINT_MACRO(RWSTD_MUTEXATTR_DEFAULT);
   PRINT_MACRO(RWSTD_NO_ANSI_SPRINTF);
   PRINT_MACRO(RWSTD_NO_ARG_MATCH);
   PRINT_MACRO(RWSTD_NO_BAD_CAST);
   PRINT_MACRO(RWSTD_NO_BASE_CLASS_MATCH);
   PRINT_MACRO(RWSTD_NO_BOOL);
   PRINT_MACRO(RWSTD_NO_BUILTIN_CTOR);
   PRINT_MACRO(RWSTD_NO_CATOPEN_CATGETS);
   PRINT_MACRO(RWSTD_NO_CLASS_PARTIAL_SPEC);
   PRINT_MACRO(RWSTD_NO_COMPLEX_DEFAULT_TEMPLATES);
   PRINT_MACRO(RWSTD_NO_COMPLICATED_EXCEPTIONS);
   PRINT_MACRO(RWSTD_NO_COMPLICATED_TYPEDEF);
   PRINT_MACRO(RWSTD_NO_CONST_INST);
   PRINT_MACRO(RWSTD_NO_CTOR_RETURN);
   PRINT_MACRO(RWSTD_NO_DEFAULT_FOR_TPARAM);
   PRINT_MACRO(RWSTD_NO_DEFAULT_TEMPLATE_ARGS);
   PRINT_MACRO(RWSTD_NO_DESTROY_BUILTIN);
   PRINT_MACRO(RWSTD_NO_DESTROY_NONBUILTIN);
   PRINT_MACRO(RWSTD_NO_EMBEDDED_TYPEDEF);
   PRINT_MACRO(RWSTD_NO_EX_SPEC);
   PRINT_MACRO(RWSTD_NO_EXCEPTIONS);
   PRINT_MACRO(RWSTD_NO_EXPLICIT);
   PRINT_MACRO(RWSTD_NO_EXPLICIT_ARG);
   PRINT_MACRO(RWSTD_NO_EXPLICIT_FUNC_INSTANTIATION);
   PRINT_MACRO(RWSTD_NO_EXPLICIT_INSTANTIATION);
   PRINT_MACRO(RWSTD_NO_EXTENSION);
   PRINT_MACRO(RWSTD_NO_FORWARD_SPECIALIZATIONS);
   PRINT_MACRO(RWSTD_NO_FPOS_T);
   PRINT_MACRO(RWSTD_NO_FRIEND_TEMPLATES);
   PRINT_MACRO(RWSTD_NO_FUNC_PARTIAL_SPEC);
   PRINT_MACRO(RWSTD_NO_GETTIMEOFDAY);
   PRINT_MACRO(RWSTD_NO_GLOBAL_TZ);
   PRINT_MACRO(RWSTD_NO_INHERITED_TYPEDEFS);
   PRINT_MACRO(RWSTD_NO_INIT_CONST_TEMPLATE_REF_ARG);
   PRINT_MACRO(RWSTD_NO_INT_TYPEDEF);
   PRINT_MACRO(RWSTD_NO_LDIV);
   PRINT_MACRO(RWSTD_NO_LEADING_UNDERSCORE);
   PRINT_MACRO(RWSTD_NO_LOCALE);
   PRINT_MACRO(RWSTD_NO_LONG_NAME);
   PRINT_MACRO(RWSTD_NO_LONGDOUBLE);
   PRINT_MACRO(RWSTD_NO_MBSTATE_T);
   PRINT_MACRO(RWSTD_NO_MEM_CLASS_TEMPLATES);
   PRINT_MACRO(RWSTD_NO_MEMBER_TEMPLATES);
   PRINT_MACRO(RWSTD_NO_MEMBER_TYPE_TPARAM);
   PRINT_MACRO(RWSTD_NO_MEMBER_WO_DEF_CTOR);
   PRINT_MACRO(RWSTD_NO_MEMMOVE);
   PRINT_MACRO(RWSTD_NO_MULTI_DIM_ARRAY);
   PRINT_MACRO(RWSTD_NO_MUTABLE);
   PRINT_MACRO(RWSTD_NO_NAME_INJECTION);
   PRINT_MACRO(RWSTD_NO_NAMESPACE);
   PRINT_MACRO(RWSTD_NO_NESTING_TEMPLATES);
   PRINT_MACRO(RWSTD_NO_NEW_BRACKETS);
   PRINT_MACRO(RWSTD_NO_NEW_DECL);
   PRINT_MACRO(RWSTD_NO_NEW_HEADER);
   PRINT_MACRO(RWSTD_NO_NEW_TEMPLATE_SYNTAX);
   PRINT_MACRO(RWSTD_NO_NONCLASS_ARROW_RETURN);
   PRINT_MACRO(RWSTD_NO_NONTYPE_ARGS);
   PRINT_MACRO(RWSTD_NO_ONLY_NEEDED_INSTANTIATION);
   PRINT_MACRO(RWSTD_NO_OVERLOAD_C_POW);
   PRINT_MACRO(RWSTD_NO_OVERLOAD_OF_TEMPLATE_FUNCTION);
   PRINT_MACRO(RWSTD_NO_OVERLOAD_WCHAR);
   PRINT_MACRO(RWSTD_NO_PART_SPEC_OVERLOAD);
   PRINT_MACRO(RWSTD_NO_RET_TEMPLATE);
   PRINT_MACRO(RWSTD_NO_SIMPLE_DEFAULT_TEMPLATES);
   PRINT_MACRO(RWSTD_NO_STATIC_CAST);
   PRINT_MACRO(RWSTD_NO_STATIC_DEF);
   PRINT_MACRO(RWSTD_NO_STATIC_DEF2);
   PRINT_MACRO(RWSTD_NO_STATIC_DEF3);
   PRINT_MACRO(RWSTD_NO_STATIC_MEM_DEF);
   PRINT_MACRO(RWSTD_NO_STI_SIMPLE);
   PRINT_MACRO(RWSTD_NO_STI_TEMPLATE);
   PRINT_MACRO(RWSTD_NO_STREAM_LONG_DOUBLE);
   PRINT_MACRO(RWSTD_NO_STRFTIME_CAPC);
   PRINT_MACRO(RWSTD_NO_STRICT_TEMPLATE_INSTANTIATE);
   PRINT_MACRO(RWSTD_NO_SWPRINTF);
   PRINT_MACRO(RWSTD_NO_TEMPLATE_ON_RETURN_TYPE);
   PRINT_MACRO(RWSTD_NO_TEMPLATE_TEMPLATE);
   PRINT_MACRO(RWSTD_NO_THREADS);
   PRINT_MACRO(RWSTD_NO_THROW_SPEC_ON_NEW);
   PRINT_MACRO(RWSTD_NO_THROW_WITH_SHARED);
   PRINT_MACRO(RWSTD_NO_TYPEDEF_INST);
   PRINT_MACRO(RWSTD_NO_TYPEDEF_OVERLOAD);
   PRINT_MACRO(RWSTD_NO_TYPENAME);
   PRINT_MACRO(RWSTD_NO_UNDEFINED_FRIEND);
   PRINT_MACRO(RWSTD_NO_UNINITIALIZED_STATIC_DEF);
   PRINT_MACRO(RWSTD_NO_WCHAR_H);
   PRINT_MACRO(RWSTD_NO_WCTYPE_H);
   PRINT_MACRO(RWSTD_NO_WIDE_CHAR);
   PRINT_MACRO(RWSTD_NO_WINT_TYPE);
   PRINT_MACRO(RWSTD_NO_WSTR);
   PRINT_MACRO(RWSTD_NOT_ALL_WSTR_CFUNCTIONS);
   PRINT_MACRO(RWSTD_POSIX_D10_THREADS);
   PRINT_MACRO(RWSTD_POSIX_THREADS);
   PRINT_MACRO(RWSTD_REQUIRES_IEEEFP);
   PRINT_MACRO(RWSTD_SOLARIS_THREADS);
   PRINT_MACRO(RWSTD_STRUCT_TM_TZ);
   PRINT_MACRO(RWSTD_WIDE_STRING_NULL_PROBLEM);
   #endif
   // Dinkumware options:
   PRINT_MACRO(_CPPLIB_VER);
   PRINT_MACRO(_GLOBAL_USING);
   PRINT_MACRO(_HAS_EXCEPTIONS);
   PRINT_MACRO(_HAS_MEMBER_TEMPLATES_REBIND);
   PRINT_MACRO(_HAS_TEMPLATE_PARTIAL_ORDERING);
   // STLPort and generic SGI STL options:
   PRINT_MACRO(__SGI_STL_NO_ARROW_OPERATOR);
   PRINT_MACRO(__SGI_STL_OWN_IOSTREAMS);
   PRINT_MACRO(__SGI_STL_PORT);
   PRINT_MACRO(__STL_AUTOMATIC_TYPE_TRAITS);
   PRINT_MACRO(__STL_BASE_MATCH_BUG);
   PRINT_MACRO(__STL_BASE_TYPEDEF_BUG);
   PRINT_MACRO(__STL_BASE_TYPEDEF_OUTSIDE_BUG);
   PRINT_MACRO(__STL_BROKEN_USING_DIRECTIVE);
   PRINT_MACRO(__STL_CONST_CONSTRUCTOR_BUG);
   PRINT_MACRO(__STL_DEBUG);
   PRINT_MACRO(__STL_DEBUG_ALLOC);
   PRINT_MACRO(__STL_DEFAULT_CONSTRUCTOR_BUG);
   PRINT_MACRO(__STL_DEFAULT_TYPE_PARAM);
   PRINT_MACRO(__STL_DONT_REDEFINE_STD);
   PRINT_MACRO(__STL_DONT_USE_BOOL_TYPEDEF);
   PRINT_MACRO(__STL_HAS_NO_EXCEPTIONS);
   PRINT_MACRO(__STL_HAS_NO_NAMESPACES);
   PRINT_MACRO(__STL_HAS_NO_NEW_C_HEADERS);
   PRINT_MACRO(__STL_HAS_NO_NEW_IOSTREAMS);
   PRINT_MACRO(__STL_IMPORT_VENDOR_CSTD);
   PRINT_MACRO(__STL_LIMITED_DEFAULT_TEMPLATES);
   PRINT_MACRO(__STL_LINK_TIME_INSTANTIATION);
   PRINT_MACRO(__STL_LONG_LONG);
   PRINT_MACRO(__STL_LOOP_INLINE_PROBLEMS);
   PRINT_MACRO(__STL_MEMBER_POINTER_PARAM_BUG);
   PRINT_MACRO(__STL_NEED_EXPLICIT);
   PRINT_MACRO(__STL_NEED_MUTABLE);
   PRINT_MACRO(__STL_NEED_TYPENAME);
   PRINT_MACRO(__STL_NESTED_TYPE_PARAM_BUG);
   PRINT_MACRO(__STL_NO_BAD_ALLOC);
   PRINT_MACRO(__STL_NO_BOOL);
   PRINT_MACRO(__STL_NO_CLASS_PARTIAL_SPECIALIZATION);
   PRINT_MACRO(__STL_NO_CSTD_FUNCTION_IMPORTS);
   PRINT_MACRO(__STL_NO_DEFAULT_NON_TYPE_PARAM);
   PRINT_MACRO(__STL_NO_EXCEPTION_HEADER);
   PRINT_MACRO(__STL_NO_EXCEPTION_SPEC);
   PRINT_MACRO(__STL_NO_EXCEPTIONS);
   PRINT_MACRO(__STL_NO_EXPLICIT_FUNCTION_TMPL_ARGS);
   PRINT_MACRO(__STL_NO_FRIEND_TEMPLATES);
   PRINT_MACRO(__STL_NO_FUNCTION_TMPL_PARTIAL_ORDER);
   PRINT_MACRO(__STL_NO_IOSTREAMS);
   PRINT_MACRO(__STL_NO_LONG_DOUBLE);
   PRINT_MACRO(__STL_NO_MEMBER_TEMPLATE_CLASSES);
   PRINT_MACRO(__STL_NO_MEMBER_TEMPLATE_KEYWORD);
   PRINT_MACRO(__STL_NO_MEMBER_TEMPLATES);
   PRINT_MACRO(__STL_NO_METHOD_SPECIALIZATION);
   PRINT_MACRO(__STL_NO_NAMESPACES);
   PRINT_MACRO(__STL_NO_NEW_IOSTREAMS);
   PRINT_MACRO(__STL_NO_NEW_NEW_HEADER);
   PRINT_MACRO(__STL_NO_NEW_STYLE_CASTS);
   PRINT_MACRO(__STL_NO_PARTIAL_SPECIALIZATION_SYNTAX);
   PRINT_MACRO(__STL_NO_QUALIFIED_FRIENDS);
   PRINT_MACRO(__STL_NO_RELOPS_NAMESPACE);
   PRINT_MACRO(__STL_NO_SGI_IOSTREAMS);
   PRINT_MACRO(__STL_NO_STATIC_TEMPLATE_DATA);
   PRINT_MACRO(__STL_NO_TEMPLATE_CONVERSIONS);
   PRINT_MACRO(__STL_NO_WCHAR_T);
   PRINT_MACRO(__STL_NON_TYPE_TMPL_PARAM_BUG);
   PRINT_MACRO(__STL_NONTEMPL_BASE_MATCH_BUG);
   PRINT_MACRO(__STL_PARTIAL_SPEC_NEEDS_TEMPLATE_ARGS);
   PRINT_MACRO(__STL_RAND48);
   PRINT_MACRO(__STL_STATIC_ARRAY_BUG);
   PRINT_MACRO(__STL_STATIC_CONST_INIT_BUG);
   PRINT_MACRO(__STL_STATIC_CONST_INIT_BUG);
   PRINT_MACRO(__STL_THROW_RETURN_BUG);
   PRINT_MACRO(__STL_TRIVIAL_CONSTRUCTOR_BUG);
   PRINT_MACRO(__STL_TRIVIAL_DESTRUCTOR_BUG);
   PRINT_MACRO(__STL_UNINITIALIZABLE_PRIVATE);
   PRINT_MACRO(__STL_USE_ABBREVS);
   PRINT_MACRO(__STL_USE_DEFALLOC);
   PRINT_MACRO(__STL_USE_MALLOC);
   PRINT_MACRO(__STL_USE_NEW_C_HEADERS);
   PRINT_MACRO(__STL_USE_NEW_IOSTREAMS);
   PRINT_MACRO(__STL_USE_NEWALLOC);
   PRINT_MACRO(__STL_USE_OWN_NAMESPACE);
   PRINT_MACRO(__STL_USE_SGI_ALLOCATORS);
   PRINT_MACRO(__STL_WCHAR_T_IS_USHORT);
   PRINT_MACRO(__STL_WEAK_ATTRIBUTE);
   PRINT_MACRO(__STL_YVALS_H);
   PRINT_MACRO(_NOTHREADS);
   PRINT_MACRO(_PTHREADS);
#if defined(__SGI_STL_PORT) && (__SGI_STL_PORT > 0x0400)
   PRINT_MACRO(_STLP_AUTOMATIC_TYPE_TRAITS);
   PRINT_MACRO(_STLP_BASE_MATCH_BUG);
   PRINT_MACRO(_STLP_BASE_TYPEDEF_BUG);
   PRINT_MACRO(_STLP_BASE_TYPEDEF_OUTSIDE_BUG);
   PRINT_MACRO(_STLP_BROKEN_USING_DIRECTIVE);
   PRINT_MACRO(_STLP_CONST_CONSTRUCTOR_BUG);
   PRINT_MACRO(_STLP_DEBUG);
   PRINT_MACRO(_STLP_DEBUG_ALLOC);
   PRINT_MACRO(_STLP_DEFAULT_CONSTRUCTOR_BUG);
   PRINT_MACRO(_STLP_DEFAULT_TYPE_PARAM);
   PRINT_MACRO(_STLP_DONT_REDEFINE_STD);
   PRINT_MACRO(_STLP_DONT_USE_BOOL_TYPEDEF);
   PRINT_MACRO(_STLP_HAS_NO_EXCEPTIONS);
   PRINT_MACRO(_STLP_HAS_NO_NAMESPACES);
   PRINT_MACRO(_STLP_HAS_NO_NEW_C_HEADERS);
   PRINT_MACRO(_STLP_HAS_NO_NEW_IOSTREAMS);
   PRINT_MACRO(_STLP_IMPORT_VENDOR_CSTD);
   PRINT_MACRO(_STLP_LIMITED_DEFAULT_TEMPLATES);
   PRINT_MACRO(_STLP_LINK_TIME_INSTANTIATION);
   PRINT_MACRO(_STLP_LONG_LONG);
   PRINT_MACRO(_STLP_LOOP_INLINE_PROBLEMS);
   PRINT_MACRO(_STLP_MEMBER_POINTER_PARAM_BUG);
   PRINT_MACRO(_STLP_NEED_EXPLICIT);
   PRINT_MACRO(_STLP_NEED_MUTABLE);
   PRINT_MACRO(_STLP_NEED_TYPENAME);
   PRINT_MACRO(_STLP_NESTED_TYPE_PARAM_BUG);
   PRINT_MACRO(_STLP_NO_ARROW_OPERATOR);
   PRINT_MACRO(_STLP_NO_BAD_ALLOC);
   PRINT_MACRO(_STLP_NO_BOOL);
   PRINT_MACRO(_STLP_NO_CLASS_PARTIAL_SPECIALIZATION);
   PRINT_MACRO(_STLP_NO_CSTD_FUNCTION_IMPORTS);
   PRINT_MACRO(_STLP_NO_DEFAULT_NON_TYPE_PARAM);
   PRINT_MACRO(_STLP_NO_EXCEPTION_HEADER);
   PRINT_MACRO(_STLP_NO_EXCEPTION_SPEC);
   PRINT_MACRO(_STLP_NO_EXCEPTIONS);
   PRINT_MACRO(_STLP_NO_EXPLICIT_FUNCTION_TMPL_ARGS);
   PRINT_MACRO(_STLP_NO_FRIEND_TEMPLATES);
   PRINT_MACRO(_STLP_NO_FUNCTION_TMPL_PARTIAL_ORDER);
   PRINT_MACRO(_STLP_NO_IOSTREAMS);
   PRINT_MACRO(_STLP_NO_LONG_DOUBLE);
   PRINT_MACRO(_STLP_NO_MEMBER_TEMPLATE_CLASSES);
   PRINT_MACRO(_STLP_NO_MEMBER_TEMPLATE_KEYWORD);
   PRINT_MACRO(_STLP_NO_MEMBER_TEMPLATES);
   PRINT_MACRO(_STLP_NO_METHOD_SPECIALIZATION);
   PRINT_MACRO(_STLP_NO_NAMESPACES);
   PRINT_MACRO(_STLP_NO_NEW_IOSTREAMS);
   PRINT_MACRO(_STLP_NO_NEW_NEW_HEADER);
   PRINT_MACRO(_STLP_NO_NEW_STYLE_CASTS);
   PRINT_MACRO(_STLP_NO_PARTIAL_SPECIALIZATION_SYNTAX);
   PRINT_MACRO(_STLP_NO_QUALIFIED_FRIENDS);
   PRINT_MACRO(_STLP_NO_RELOPS_NAMESPACE);
   PRINT_MACRO(_STLP_NO_SGI_IOSTREAMS);
   PRINT_MACRO(_STLP_NO_STATIC_TEMPLATE_DATA);
   PRINT_MACRO(_STLP_NO_TEMPLATE_CONVERSIONS);
   PRINT_MACRO(_STLP_NO_WCHAR_T);
   PRINT_MACRO(_STLP_NON_TYPE_TMPL_PARAM_BUG);
   PRINT_MACRO(_STLP_NONTEMPL_BASE_MATCH_BUG);
   PRINT_MACRO(_STLP_OWN_IOSTREAMS);
   PRINT_MACRO(_STLP_PARTIAL_SPEC_NEEDS_TEMPLATE_ARGS);
   PRINT_MACRO(_STLP_RAND48);
   PRINT_MACRO(_STLP_STATIC_ARRAY_BUG);
   PRINT_MACRO(_STLP_STATIC_CONST_INIT_BUG);
   PRINT_MACRO(_STLP_STATIC_CONST_INIT_BUG);
   PRINT_MACRO(_STLP_THROW_RETURN_BUG);
   PRINT_MACRO(_STLP_TRIVIAL_CONSTRUCTOR_BUG);
   PRINT_MACRO(_STLP_TRIVIAL_DESTRUCTOR_BUG);
   PRINT_MACRO(_STLP_UNINITIALIZABLE_PRIVATE);
   PRINT_MACRO(_STLP_USE_ABBREVS);
   PRINT_MACRO(_STLP_USE_DEFALLOC);
   PRINT_MACRO(_STLP_USE_MALLOC);
   PRINT_MACRO(_STLP_USE_NEW_C_HEADERS);
   PRINT_MACRO(_STLP_USE_NEWALLOC);
   PRINT_MACRO(_STLP_USE_OWN_NAMESPACE);
   PRINT_MACRO(_STLP_USE_SGI_ALLOCATORS);
   PRINT_MACRO(_STLP_WCHAR_T_IS_USHORT);
   PRINT_MACRO(_STLP_WEAK_ATTRIBUTE);
   PRINT_MACRO(_STLP_YVALS_H);
#endif
   PRINT_MACRO(__GLIBCPP__);
   PRINT_MACRO(_GLIBCPP_USE_WCHAR_T);
   PRINT_MACRO(_GLIBCPP_VERSION);
   // Modena C++ standard library
   PRINT_MACRO(MSIPL_ANSI_HEADER);
   PRINT_MACRO(MSIPL_BOOL_BUILTIN);
   PRINT_MACRO(MSIPL_DEF_EXPLICIT);
   PRINT_MACRO(MSIPL_DEF_TEMPARG);
   PRINT_MACRO(MSIPL_EXPINST_ALLOWED);
   PRINT_MACRO(MSIPL_EXPLICIT_FUNC_TEMPLATE_ARG);
   PRINT_MACRO(MISPL_EXPLICIT_TEMPLATE_ARGUMENT);
   PRINT_MACRO(MSIPL_FUNC_TEMPLATE_DEFARG);
   PRINT_MACRO(MSIPL_MEMBER_TEMPLATE);
   PRINT_MACRO(MSIPL_MULTITHREAD);
   PRINT_MACRO(MSIPL_NON_TYPE_TEMPARG);
   PRINT_MACRO(MSIPL_PARTIAL_TEMPL);
   PRINT_MACRO(MSIPL_STATIC_CONST_INIT);
   PRINT_MACRO(MSIPL_TEMPL_NEWSPEC);
   PRINT_MACRO(MSIPL_TYPENAME);
   PRINT_MACRO(MSIPL_USING_NAMESPACE);
   PRINT_MACRO(MSIPL_WCHART);
}

void print_platform_macros()
{
   std::cout << "Detected Platform: " << BOOST_PLATFORM << std::endl;
   // signedness:
   PRINT_SIGN(char);
   PRINT_SIGN(wchar_t);
   // byte ordering:
   PRINT_ORDER(short);
   PRINT_ORDER(int);
   PRINT_ORDER(long);
   // sizes:
   PRINT_EXPRESSION(sizeof(wchar_t));
   PRINT_EXPRESSION(sizeof(short));
   PRINT_EXPRESSION(sizeof(int));
   PRINT_EXPRESSION(sizeof(long));
   PRINT_EXPRESSION(sizeof(float));
   PRINT_EXPRESSION(sizeof(double));
   PRINT_EXPRESSION(sizeof(long double));
   // limits:
   PRINT_MACRO(CHAR_BIT);
   PRINT_MACRO(CHAR_MAX);
   PRINT_MACRO(WCHAR_MAX);
   PRINT_MACRO(SHRT_MAX);
   PRINT_MACRO(INT_MAX);
   PRINT_MACRO(LONG_MAX);
   PRINT_MACRO(LLONG_MAX);
   PRINT_MACRO(LONG_LONG_MAX);
   PRINT_MACRO(LONGLONG_MAX);
   PRINT_MACRO(ULLONG_MAX); // <boost/cstdint.hpp> uses these, so we need to know them
   PRINT_MACRO(ULONG_LONG_MAX);
   PRINT_MACRO(ULONGLONG_MAX);
   // general C99:
   PRINT_MACRO(__STDC_IEC_559__);
   PRINT_MACRO(__STDC_IEC_559_COMPLEX__);
   PRINT_MACRO(__STDC_ISO_10646__);
   // GNU:
   PRINT_MACRO(__GLIBC__);
   PRINT_MACRO(__GLIBC_MINOR__);
   PRINT_MACRO(__GNU_LIBRARY__);
   PRINT_MACRO(_BSD_SOURCE);
   PRINT_MACRO(_FILE_OFFSET_BITS);
   PRINT_MACRO(_GNU_SOURCE);
   PRINT_MACRO(_ISOC99_SOURCE);
   PRINT_MACRO(_ISOC9X_SOURCE);
   PRINT_MACRO(_LARGEFILE_SOURCE);
   PRINT_MACRO(_LARGEFILE64_SOURCE);
   PRINT_MACRO(_SVID_SOURCE);
   PRINT_MACRO(_THREAD_SAFE);
   PRINT_MACRO(_XOPEN_SOURCE_EXTENDED);
   PRINT_MACRO(XPG);
   // POSIX:
   PRINT_MACRO(_POSIX_ADVISORY_INFO);
   PRINT_MACRO(_POSIX_ASYNCHRONOUS_IO);
   PRINT_MACRO(_POSIX_BARRIERS);
   PRINT_MACRO(_POSIX_C_SOURCE);
   PRINT_MACRO(_POSIX_CHOWN_RESTRICTED);
   PRINT_MACRO(_POSIX_CLOCK_SELECTION);
   PRINT_MACRO(_POSIX_CPUTIME);
   PRINT_MACRO(_POSIX_FSYNC);
   PRINT_MACRO(_POSIX_JOB_CONTROL);
   PRINT_MACRO(_POSIX_MAPPED_FILES);
   PRINT_MACRO(_POSIX_MEMLOCK);
   PRINT_MACRO(_POSIX_MEMLOCK_RANGE);
   PRINT_MACRO(_POSIX_MEMORY_PROTECTION);
   PRINT_MACRO(_POSIX_MESSAGE_PASSING);
   PRINT_MACRO(_POSIX_MONOTONIC_CLOCK);
   PRINT_MACRO(_POSIX_NO_TRUNC);
   PRINT_MACRO(_POSIX_PRIORITIZED_IO);
   PRINT_MACRO(_POSIX_PRIORITY_SCHEDULING);
   PRINT_MACRO(_POSIX_RAW_SOCKETS);
   PRINT_MACRO(_POSIX_READER_WRITER_LOCKS);
   PRINT_MACRO(_POSIX_REALTIME_SIGNALS);
   PRINT_MACRO(_POSIX_REGEXP);
   PRINT_MACRO(_POSIX_SAVED_IDS);
   PRINT_MACRO(_POSIX_SEMAPHORES);
   PRINT_MACRO(_POSIX_SHARED_MEMORY_OBJECTS);
   PRINT_MACRO(_POSIX_SHELL);
   PRINT_MACRO(_POSIX_SOURCE);
   PRINT_MACRO(_POSIX_SPAWN);
   PRINT_MACRO(_POSIX_SPIN_LOCKS);
   PRINT_MACRO(_POSIX_SPORADIC_SERVER);
   PRINT_MACRO(_POSIX_SYNCHRONIZED_IO);
   PRINT_MACRO(_POSIX_THREAD_ATTR_STACKADDR);
   PRINT_MACRO(_POSIX_THREAD_ATTR_STACKSIZE);
   PRINT_MACRO(_POSIX_THREAD_CPUTIME);
   PRINT_MACRO(_POSIX_THREAD_PRIO_INHERIT);
   PRINT_MACRO(_POSIX_THREAD_PRIO_PROTECT);
   PRINT_MACRO(_POSIX_THREAD_PRIORITY_SCHEDULING);
   PRINT_MACRO(_POSIX_THREAD_PROCESS_SHARED);
   PRINT_MACRO(_POSIX_THREAD_SAFE_FUNCTIONS);
   PRINT_MACRO(_POSIX_THREAD_SPORADIC_SERVER);
   PRINT_MACRO(_POSIX_THREADS);
   PRINT_MACRO(_POSIX_TIMEOUTS);
   PRINT_MACRO(_POSIX_TIMERS);
   PRINT_MACRO(_POSIX_TRACE);
   PRINT_MACRO(_POSIX_TRACE_EVENT_FILTER);
   PRINT_MACRO(_POSIX_TRACE_INHERIT);
   PRINT_MACRO(_POSIX_TRACE_LOG);
   PRINT_MACRO(_POSIX_TYPED_MEMORY_OBJECTS);
   PRINT_MACRO(_POSIX_VDISABLE);
   PRINT_MACRO(_POSIX_VERSION);
   PRINT_MACRO(_POSIX2_C_BIND);
   PRINT_MACRO(_POSIX2_C_DEV);
   PRINT_MACRO(_POSIX2_CHAR_TERM);
   PRINT_MACRO(_POSIX2_FORT_DEV);
   PRINT_MACRO(_POSIX2_FORT_RUN);
   PRINT_MACRO(_POSIX2_LOCALEDEF);
   PRINT_MACRO(_POSIX2_PBS);
   PRINT_MACRO(_POSIX2_PBS_ACCOUNTING);
   PRINT_MACRO(_POSIX2_PBS_CHECKPOINT);
   PRINT_MACRO(_POSIX2_PBS_LOCATE);
   PRINT_MACRO(_POSIX2_PBS_MESSAGE);
   PRINT_MACRO(_POSIX2_PBS_TRACK);
   PRINT_MACRO(_POSIX2_SW_DEV);
   PRINT_MACRO(_POSIX2_UPE);
   PRINT_MACRO(_POSIX2_VERSION);
   PRINT_MACRO(_V6_ILP32_OFF32);
   PRINT_MACRO(_V6_ILP32_OFFBIG);
   PRINT_MACRO(_V6_LP64_OFF64);
   PRINT_MACRO(_V6_LPBIG_OFFBIG);
   PRINT_MACRO(_XBS5_ILP32_OFF32);
   PRINT_MACRO(_XBS5_ILP32_OFFBIG);
   PRINT_MACRO(_XBS5_LP64_OFF64);
   PRINT_MACRO(_XBS5_LPBIG_OFFBIG);
   PRINT_MACRO(_XOPEN_CRYPT);
   PRINT_MACRO(_XOPEN_ENH_I18N);
   PRINT_MACRO(_XOPEN_LEGACY);
   PRINT_MACRO(_XOPEN_REALTIME);
   PRINT_MACRO(_XOPEN_REALTIME_THREADS);
   PRINT_MACRO(_XOPEN_SHM);
   PRINT_MACRO(_XOPEN_SOURCE);
   PRINT_MACRO(_XOPEN_STREAMS);
   PRINT_MACRO(_XOPEN_UNIX);
   PRINT_MACRO(_XOPEN_VERSION);
}

void print_boost_macros()
{
   std::cout << "Boost version " << BOOST_STRINGIZE(BOOST_VERSION) << std::endl;
   // config setup macros first:
   PRINT_MACRO(BOOST_USER_CONFIG);
   PRINT_MACRO(BOOST_COMPILER_CONFIG);
   PRINT_MACRO(BOOST_STDLIB_CONFIG);
   PRINT_MACRO(BOOST_PLATFORM_CONFIG);
   PRINT_MACRO(BOOST_NO_CONFIG);
   PRINT_MACRO(BOOST_NO_USER_CONFIG);
   PRINT_MACRO(BOOST_NO_COMPILER_CONFIG);
   PRINT_MACRO(BOOST_NO_STDLIB_CONFIG);
   PRINT_MACRO(BOOST_NO_PLATFORM_CONFIG);
   // then defect and feature macros:
   PRINT_MACRO(BOOST_BCB_PARTIAL_SPECIALIZATION_BUG);
   PRINT_MACRO(BOOST_DEDUCED_TYPENAME);
   PRINT_MACRO(BOOST_DISABLE_THREADS);
   PRINT_MACRO(BOOST_DISABLE_WIN32);
   PRINT_MACRO(BOOST_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL);
   PRINT_MACRO(BOOST_HAS_BETHREADS);
   PRINT_MACRO(BOOST_HAS_CLOCK_GETTIME);
   PRINT_MACRO(BOOST_HAS_DECLSPEC);
   PRINT_MACRO(BOOST_HAS_DIRENT_H);
   PRINT_MACRO(BOOST_HAS_FTIME);
   PRINT_MACRO(BOOST_HAS_GETTIMEOFDAY);
   PRINT_MACRO(BOOST_HAS_HASH);
   PRINT_MACRO(BOOST_HAS_LONG_LONG);
   PRINT_MACRO(BOOST_HAS_MACRO_USE_FACET);
   PRINT_MACRO(BOOST_HAS_MS_INT64);
   PRINT_MACRO(BOOST_HAS_NANOSLEEP);
   PRINT_MACRO(BOOST_HAS_NL_TYPES_H);
   PRINT_MACRO(BOOST_HAS_NRVO);
   PRINT_MACRO(BOOST_HAS_PARTIAL_STD_ALLOCATOR);
   PRINT_MACRO(BOOST_HAS_PTHREAD_DELAY_NP);
   PRINT_MACRO(BOOST_HAS_PTHREAD_MUTEXATTR_SETTYPE);
   PRINT_MACRO(BOOST_HAS_PTHREAD_YIELD);
   PRINT_MACRO(BOOST_HAS_PTHREADS);
   PRINT_MACRO(BOOST_HAS_SCHED_YIELD);
   PRINT_MACRO(BOOST_HAS_SIGACTION);
   PRINT_MACRO(BOOST_HAS_SGI_TYPE_TRAITS);
   PRINT_MACRO(BOOST_HAS_STDINT_H);
   PRINT_MACRO(BOOST_HAS_SLIST);
   PRINT_MACRO(BOOST_HAS_STLP_USE_FACET);
   PRINT_MACRO(BOOST_HAS_THREADS);
   PRINT_MACRO(BOOST_HAS_TWO_ARG_USE_FACET);
   PRINT_MACRO(BOOST_HAS_UNISTD_H);
   PRINT_MACRO(BOOST_HAS_WINTHREADS);
   PRINT_MACRO(BOOST_INTEL);
   PRINT_MACRO(BOOST_MSVC);
   PRINT_MACRO(BOOST_MSVC_STD_ITERATOR);
   PRINT_MACRO(BOOST_MSVC6_MEMBER_TEMPLATES);
   PRINT_MACRO(BOOST_NESTED_TEMPLATE);
   PRINT_MACRO(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP);
   PRINT_MACRO(BOOST_NO_ARRAY_TYPE_SPECIALIZATIONS);
   PRINT_MACRO(BOOST_NO_AUTO_PTR);
   PRINT_MACRO(BOOST_NO_CTYPE_FUNCTIONS);
   PRINT_MACRO(BOOST_NO_CV_SPECIALIZATIONS);
   PRINT_MACRO(BOOST_NO_CV_VOID_SPECIALIZATIONS);
   PRINT_MACRO(BOOST_NO_CWCHAR);
   PRINT_MACRO(BOOST_NO_CWCTYPE);
   PRINT_MACRO(BOOST_NO_DEDUCED_TYPENAME);
   PRINT_MACRO(BOOST_NO_DEPENDENT_NESTED_DERIVATIONS);
   PRINT_MACRO(BOOST_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS);
   PRINT_MACRO(BOOST_NO_EXCEPTIONS);
   PRINT_MACRO(BOOST_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS);
   PRINT_MACRO(BOOST_NO_FUNCTION_TEMPLATE_ORDERING);
   PRINT_MACRO(BOOST_NO_HASH);
   PRINT_MACRO(BOOST_NO_INCLASS_MEMBER_INITIALIZATION);
   PRINT_MACRO(BOOST_NO_INT64_T);
   PRINT_MACRO(BOOST_NO_INTEGRAL_INT64_T);
   PRINT_MACRO(BOOST_NO_INTRINSIC_WCHAR_T);
   PRINT_MACRO(BOOST_NO_LIMITS);
   PRINT_MACRO(BOOST_NO_LIMITS_COMPILE_TIME_CONSTANTS);
   PRINT_MACRO(BOOST_NO_LONG_LONG_NUMERIC_LIMITS);
   PRINT_MACRO(BOOST_NO_MEMBER_FUNCTION_SPECIALIZATIONS);
   PRINT_MACRO(BOOST_NO_MEMBER_TEMPLATE_KEYWORD);
   PRINT_MACRO(BOOST_NO_MEMBER_TEMPLATE_FRIENDS);
   PRINT_MACRO(BOOST_NO_MEMBER_TEMPLATES);
   PRINT_MACRO(BOOST_NO_MS_INT64_NUMERIC_LIMITS);
   PRINT_MACRO(BOOST_NO_OPERATORS_IN_NAMESPACE);
   PRINT_MACRO(BOOST_NO_POINTER_TO_MEMBER_CONST);
   PRINT_MACRO(BOOST_NO_PRIVATE_IN_AGGREGATE);
   PRINT_MACRO(BOOST_NO_SFINAE);
   PRINT_MACRO(BOOST_NO_SLIST);
   PRINT_MACRO(BOOST_NO_STD_ALLOCATOR);
   PRINT_MACRO(BOOST_NO_STD_DISTANCE);
   PRINT_MACRO(BOOST_NO_STD_ITERATOR);
   PRINT_MACRO(BOOST_NO_STD_ITERATOR_TRAITS);
   PRINT_MACRO(BOOST_NO_STD_LOCALE);
   PRINT_MACRO(BOOST_NO_STD_MESSAGES);
   PRINT_MACRO(BOOST_NO_STD_MIN_MAX);
   PRINT_MACRO(BOOST_NO_STD_OUTPUT_ITERATOR_ASSIGN);
   PRINT_MACRO(BOOST_NO_STD_USE_FACET);
   PRINT_MACRO(BOOST_NO_STD_WSTREAMBUF);
   PRINT_MACRO(BOOST_NO_STD_WSTRING);
   PRINT_MACRO(BOOST_NO_STDC_NAMESPACE);
   PRINT_MACRO(BOOST_NO_STRINGSTREAM);
   PRINT_MACRO(BOOST_NO_SWPRINTF);
   PRINT_MACRO(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION);
   PRINT_MACRO(BOOST_NO_TEMPLATE_TEMPLATES);
   PRINT_MACRO(BOOST_NO_TEMPLATED_ITERATOR_CONSTRUCTORS);
   PRINT_MACRO(BOOST_NO_UNREACHABLE_RETURN_DETECTION);
   PRINT_MACRO(BOOST_NO_USING_TEMPLATE);
   PRINT_MACRO(BOOST_NO_VOID_RETURNS);
   PRINT_MACRO(BOOST_STD_EXTENSION_NAMESPACE);
   PRINT_MACRO(BOOST_UNREACHABLE_RETURN(0));
}

void print_separator()
{
   std::cout <<
"\n\n*********************************************************************\n\n";
}

int main()
{

  // boost compiler workaround defines
  print_compiler_macros();
  print_separator();
  print_stdlib_macros();
  print_separator();
  print_platform_macros();
  print_separator();
  print_boost_macros();

  return 0;
}









