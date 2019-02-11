// Copyright (c) 2018-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#include <iostream>

#include <tao/json.hpp>

#define PRINT_SIZE( ... ) \
   std::cout << #__VA_ARGS__ << " size " << sizeof( __VA_ARGS__ ) << " align " << alignof( __VA_ARGS__ ) << std::endl;

int main( int /*unused*/, char** /*unused*/ )
{
   PRINT_SIZE( std::string );
   PRINT_SIZE( tao::json::internal::value_union< tao::json::value > );
   PRINT_SIZE( tao::json::value );
   PRINT_SIZE( std::vector< tao::json::value > );
   PRINT_SIZE( std::map< std::string, tao::json::value > );
   PRINT_SIZE( tao::json::token );
   PRINT_SIZE( tao::json::pointer );
   return 0;
}
