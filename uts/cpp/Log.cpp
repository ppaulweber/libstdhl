//
//  Copyright (c) 2014-2017 Philipp Paulweber
//  All rights reserved.
//
//  Developed by: Philipp Paulweber
//                Emmanuel Pescosta
//                https://github.com/ppaulweber/libstdhl
//
//  This file is part of libstdhl.
//
//  libstdhl is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  libstdhl is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with libstdhl. If not, see <http://www.gnu.org/licenses/>.
//

#include "uts/main.h"

using namespace libstdhl;

#define TEST_NAME                                                              \
    ( std::string(::testing::UnitTest::GetInstance()                           \
                      ->current_test_info()                                    \
                      ->test_case_name() )                                     \
        + "."                                                                  \
        + std::string(::testing::UnitTest::GetInstance()                       \
                          ->current_test_info()                                \
                          ->name() ) )

TEST( libstdhl_cpp_Log, example )
{
    Log::Stream c;

    c.add( Log::Level::ID::ERROR, "seems to be an error" );
    c.add( Log::Level::ID::INFORMATIONAL, "just a little info for you" );
    c.add( Log::Level::ID::WARNING, "a possible warning detected" );
    c.add( Log::Level::ID::ALERT, "this is an alert, please react" );
    c.add( Log::Level::ID::OUTPUT, "this is an example output" );

    Log::StringFormatter sf;
    Log::ConsoleFormatter cf;
    Log::ApplicationFormatter af( TEST_NAME );

    Log::Filter ff;

    ff.setLevel( Log::Level::ID::WARNING );
    ff.setLevel( Log::Level::ID::OUTPUT );
    auto sw = ff.set< Log::Switch >();

    sw->add< Log::OutputStreamSink >( std::cerr, sf );
    sw->add< Log::OutputStreamSink >( std::cout, cf );
    sw->add< Log::OutputStreamSink >( std::cout, af );

    c.flush( ff );
    c.flush( ff );
}

TEST( libstdhl_cpp_Log, merging_two_streams_and_routing_them_to_two_sinks )
{
    /*

      a --                      -- sf (warning, error)
          \                    /
           +--> s = (a+b) --> rr
          /                    \
      b --                      -- cf (alert)

    */

    Log::Stream a;
    Log::Stream b;

    a.add( Log::Level::ID::ERROR, "A0" );
    a.add( Log::Level::ID::ERROR, "A1" );
    a.add( Log::Level::ID::ALERT, "Alert A" );
    b.add( Log::Level::ID::ERROR, "B0" );
    b.add( Log::Level::ID::ERROR, "B1" );
    a.add( Log::Level::ID::WARNING, "A2" );
    b.add( Log::Level::ID::WARNING, "B1" );
    b.add( Log::Level::ID::ALERT, "Alert B" );
    b.add( Log::Level::ID::WARNING, "B2" );

    // merge/aggregate the streams

    Log::Stream s = a + b;

    Log::StringFormatter sf;
    Log::ConsoleFormatter cf;

    Log::OutputStreamSink z( std::cerr, sf );
    z.process( s );

    std::cerr << "----\n";

    Log::Router rr;

    auto f0 = rr.add< Log::Filter >();
    f0->setLevel( Log::Level::ID::WARNING );
    f0->setLevel( Log::Level::ID::ERROR );
    f0->set< Log::OutputStreamSink >( std::cerr, sf );

    auto f1 = rr.add< Log::Filter >();
    f1->setLevel( Log::Level::ID::ALERT );
    f1->set< Log::OutputStreamSink >( std::cout, cf );

    s.flush( rr );
}

TEST( libstdhl_cpp_log, chronograph )
{
    Log::Chronograph c;

    c.start();

    Log::Stream s;
    Log::StringFormatter f;
    Log::OutputStreamSink z( std::cerr, f );

    c.stop();

    s.add( Log::Level::ID::INFORMATIONAL,
        "setup took '" + std::string( c ) + "'" );

    s.add( Log::Level::ID::INFORMATIONAL, c );

    s.flush( z );
}

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
