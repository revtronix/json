// Copyright (c) 2015-2016 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAOCPP_JSON_INCLUDE_FROM_STRING_HH
#define TAOCPP_JSON_INCLUDE_FROM_STRING_HH

#include "external/pegtl/parse.hh"

#include "internal/value_builder.hh"

#include "internal/grammar.hh"
#include "internal/action.hh"
#include "internal/control.hh"

namespace tao
{
   namespace json
   {
      template< typename Handler >
      inline void from_string( const char * data, const std::size_t size, Handler & handler, const char * source = nullptr, const std::size_t line = 1, const std::size_t column = 0 )
      {
         tao_json_pegtl::input input( line, column, data, data + size, source ? source : __PRETTY_FUNCTION__ );
         tao_json_pegtl::parse_input< internal::grammar, internal::action, internal::control >( input, handler );
      }

      template< typename Handler >
      inline void from_string( const std::string & data, Handler & handler, const char * source = nullptr, const std::size_t line = 1, const std::size_t column = 0 )
      {
         json::from_string( data.data(), data.size(), handler, source, line, column );
      }

      template< template< typename ... > class Traits >
      inline basic_value< Traits > from_string( const char * data, const std::size_t size, const char * source = nullptr, const std::size_t line = 1, const std::size_t column = 0 )
      {
         internal::value_builder< Traits > handler;
         json::from_string( data, size, handler, source, line, column );
         return std::move( handler.value_ );
      }

      template< template< typename ... > class Traits >
      inline void from_string( basic_value< Traits > & output, const char * data, const std::size_t size, const char * source = nullptr, const std::size_t line = 1, const std::size_t column = 0 )
      {
         output = from_string< Traits >( data, size, source, line, column );
      }

      inline value from_string( const char * data, const std::size_t size, const char * source = nullptr, const std::size_t line = 1, const std::size_t column = 0 )
      {
         return from_string< traits >( data, size, source, line, column );
      }

      template< template< typename ... > class Traits >
      inline void from_string( basic_value< Traits > & output, const char * data, const std::size_t size, const std::string & source, const std::size_t line = 1, const std::size_t column = 0 )
      {
         json::from_string( output, data, size, source.c_str(), line, column );
      }

      template< template< typename ... > class Traits >
      inline basic_value< Traits > from_string( const char * data, const std::size_t size, const std::string & source, const std::size_t line = 1, const std::size_t column = 0 )
      {
         return from_string< Traits >( data, size, source.c_str(), line, column );
      }

      inline value from_string( const char * data, const std::size_t size, const std::string & source, const std::size_t line = 1, const std::size_t column = 0 )
      {
         return json::from_string( data, size, source.c_str(), line, column );
      }

      template< template< typename ... > class Traits >
      inline void from_string( basic_value< Traits > & output, const std::string & data, const char * source = nullptr, const std::size_t line = 1, const std::size_t column = 0 )
      {
         json::from_string( output, data.data(), data.size(), source, line, column );
      }

      template< template< typename ... > class Traits >
      inline basic_value< Traits > from_string( const std::string & data, const char * source = nullptr, const std::size_t line = 1, const std::size_t column = 0 )
      {
         return from_string< Traits >( data.data(), data.size(), source, line, column );
      }

      inline value from_string( const std::string & data, const char * source = nullptr, const std::size_t line = 1, const std::size_t column = 0 )
      {
         return json::from_string( data.data(), data.size(), source, line, column );
      }

      template< template< typename ... > class Traits >
      inline void from_string( basic_value< Traits > & output, const std::string & data, const std::string & source, const std::size_t line = 1, const std::size_t column = 0 )
      {
         json::from_string( output, data.data(), data.size(), source.c_str(), line, column );
      }

      template< template< typename ... > class Traits >
      inline basic_value< Traits > from_string( const std::string & data, const std::string & source, const std::size_t line = 1, const std::size_t column = 0 )
      {
         return from_string< Traits >( data.data(), data.size(), source.c_str(), line, column );
      }

      inline value from_string( const std::string & data, const std::string & source, const std::size_t line = 1, const std::size_t column = 0 )
      {
         return json::from_string( data.data(), data.size(), source.c_str(), line, column );
      }

      inline namespace literals
      {
         inline value operator"" _json( const char * data, const std::size_t size )
         {
            return json::from_string( data, size, "literal" );
         }

      } // literals

   } // json

} // tao

#endif
