// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once

#include <third-party/json.hpp>
#include <string>


namespace utilities {
namespace json {


// Returns true if the json has a certain key.
// Does not check the value at all, so it could be any type or null.
inline bool has( nlohmann::json const & j, char const * key )
{
    auto it = j.find( key );
    if( it == j.end() )
        return false;
    return true;
}


// Returns true if the json has a certain key and its value is not null.
// Does not check the value type.
inline bool has_value( nlohmann::json const & j, char const * key )
{
    auto it = j.find( key );
    if( it == j.end() || it->is_null() )
        return false;
    return true;
}


// If there, gets the value at the given key and returns true; otherwise false.
// Turns json exceptions into runtime errors with additional info.
template< class T >
bool get_ex( nlohmann::json const & j, char const * key, T * pv )
{
    auto it = j.find( key );
    if( it == j.end() || it->is_null() )
        return false;
    try
    {
        // This will throw for type mismatches, etc.
        *pv = it->get< T >();
    }
    catch( nlohmann::json::exception & e )
    {
        throw std::runtime_error( "[while getting '" + std::string(key) + "']" + e.what() );
    }
    return true;
}


// If there, returns the value at the given key; otherwise returns a default value.
// Turns json exceptions into runtime errors with additional info.
template < class T >
T get( nlohmann::json const & j, char const * key, T const & default_value )
{
    T v;
    if( get_ex< T >( j, key, &v ) )
        return v;
    return default_value;
}


// If there, returns the value at the given key; otherwise throws!
// Turns json exceptions into runtime errors with additional info.
template < class T >
T get( nlohmann::json const & j, char const * key )
{
    try
    {
        // This will throw for type mismatches, etc.
        // Does not check for existence: will throw, too!
        return j.at(key).get< T >();
    }
    catch( nlohmann::json::exception & e )
    {
        throw std::runtime_error( "[while getting '" + std::string( key ) + "']" + e.what() );
    }
}


}  // namespace json
}  // namespace utilities
