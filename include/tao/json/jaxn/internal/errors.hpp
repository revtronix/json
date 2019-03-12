// Copyright (c) 2017-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#ifndef TAO_JSON_JAXN_INTERNAL_ERRORS_HPP
#define TAO_JSON_JAXN_INTERNAL_ERRORS_HPP

#include <string>

#include "../../external/pegtl/normal.hpp"
#include "../../external/pegtl/parse_error.hpp"

#include "grammar.hpp"

namespace tao
{
   namespace json
   {
      namespace jaxn
      {
         namespace internal
         {
            template< typename Rule >
            struct errors
               : pegtl::normal< Rule >
            {
               static const std::string error_message;

               template< typename Input, typename... States >
               static void raise( const Input& in, States&&... /*unused*/ )
               {
                  throw pegtl::parse_error( error_message, in );
               }

               template< template< typename... > class Action, typename Iterator, typename Input, typename... States >
               static auto apply( const Iterator& begin, const Input& in, States&&... st )
                  -> decltype( Action< Rule >::apply( std::declval< const typename Input::action_t& >(), st... ) )
               {
                  try {
                     using action_t = typename Input::action_t;
                     const action_t action_input( begin, in );
                     return Action< Rule >::apply( action_input, st... );
                  }
                  catch( const pegtl::parse_error& ) {
                     throw;
                  }
                  catch( const std::exception& e ) {
                     throw pegtl::parse_error( e.what(), in );
                  }
               }

               template< template< typename... > class Action, typename Input, typename... States >
               static auto apply0( const Input& in, States&&... st )
                  -> decltype( Action< Rule >::apply0( st... ) )
               {
                  try {
                     return Action< Rule >::apply0( st... );
                  }
                  catch( const pegtl::parse_error& ) {
                     throw;
                  }
                  catch( const std::exception& e ) {
                     throw pegtl::parse_error( e.what(), in );
                  }
               }
            };

            // clang-format off
            template<> inline const std::string errors< rules::text >::error_message = "no valid JAXN";  // NOLINT

            template<> inline const std::string errors< rules::comment >::error_message = "expected '*' or '/'";  // NOLINT
            template<> inline const std::string errors< rules::line_comment_char >::error_message = "invalid character in line comment";  // NOLINT
            template<> inline const std::string errors< rules::block_comment_char >::error_message = "invalid character in block comment";  // NOLINT
            template<> inline const std::string errors< rules::end_block_comment >::error_message = "unterminated multi-line comment";  // NOLINT

            template<> inline const std::string errors< rules::end_array >::error_message = "incomplete array, expected value or ']'";  // NOLINT
            template<> inline const std::string errors< rules::end_object >::error_message = "incomplete object, expected key or '}'";  // NOLINT
            template<> inline const std::string errors< rules::name_separator >::error_message = "expected ':'";  // NOLINT
            template<> inline const std::string errors< rules::value >::error_message = "expected value";  // NOLINT

            template<> inline const std::string errors< rules::edigits >::error_message = "expected at least one exponent digit";  // NOLINT
            template<> inline const std::string errors< rules::fdigits >::error_message = "expected at least one fraction digit";  // NOLINT
            template<> inline const std::string errors< rules::nan >::error_message = "invalid numeric literal";  // NOLINT
            template<> inline const std::string errors< rules::infinity< false > >::error_message = "invalid numeric literal";  // NOLINT
            template<> inline const std::string errors< rules::infinity< true > >::error_message = "invalid numeric literal";  // NOLINT
            template<> inline const std::string errors< rules::hexnum< false > >::error_message = "expected at least one hexadecimal digit";  // NOLINT
            template<> inline const std::string errors< rules::hexnum< true > >::error_message = "expected at least one hexadecimal digit";  // NOLINT

            template<> inline const std::string errors< rules::xdigit >::error_message = "incomplete universal character name";  // NOLINT
            template<> inline const std::string errors< rules::escaped >::error_message = "unknown escape sequence in string";  // NOLINT
            template<> inline const std::string errors< rules::chars< '"' > >::error_message = "invalid character in string";  // NOLINT
            template<> inline const std::string errors< rules::chars< '\'' > >::error_message = "invalid character in string";  // NOLINT
            template<> inline const std::string errors< rules::qstring_content< '"' > >::error_message = "unterminated string";  // NOLINT
            template<> inline const std::string errors< rules::qstring_content< '\'' > >::error_message = "unterminated string";  // NOLINT
            template<> inline const std::string errors< rules::mchars< '"' > >::error_message = "invalid character in multiline string";  // NOLINT
            template<> inline const std::string errors< rules::mchars< '\'' > >::error_message = "invalid character in multiline string";  // NOLINT
            template<> inline const std::string errors< rules::mqstring_content< '"' > >::error_message = "unterminated multiline string";  // NOLINT
            template<> inline const std::string errors< rules::mqstring_content< '\'' > >::error_message = "unterminated multiline string";  // NOLINT
            template<> inline const std::string errors< rules::string_fragment >::error_message = "expected string";  // NOLINT

            template<> inline const std::string errors< rules::bescaped >::error_message = "unknown escape sequence in binary string";  // NOLINT
            template<> inline const std::string errors< rules::bchars< '"' > >::error_message = "invalid character in binary string";  // NOLINT
            template<> inline const std::string errors< rules::bchars< '\'' > >::error_message = "invalid character in binary string";  // NOLINT
            template<> inline const std::string errors< rules::bqstring_content< '"' > >::error_message = "unterminated binary string";  // NOLINT
            template<> inline const std::string errors< rules::bqstring_content< '\'' > >::error_message = "unterminated binary string";  // NOLINT
            template<> inline const std::string errors< rules::bvalue >::error_message = "expected binary";  // NOLINT
            template<> inline const std::string errors< rules::bpart >::error_message = "expected a pair of hexadecimal digits";  // NOLINT

            template<> inline const std::string errors< pegtl::eof >::error_message = "unexpected character after JAXN value";  // NOLINT
            // clang-format on

         }  // namespace internal

      }  // namespace jaxn

   }  // namespace json

}  // namespace tao

#endif
