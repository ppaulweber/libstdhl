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

#ifndef _LIB_STDHL_UTS_MAIN_H_
#define _LIB_STDHL_UTS_MAIN_H_

#include "hayai.hpp"
#include "gtest/gtest.h"

#include "libstdhl.h"

#define TEST_CASE                                                              \
    std::string(::testing::UnitTest::GetInstance()                             \
                    ->current_test_info()                                      \
                    ->test_case_name() )

#define TEST_UNIT                                                              \
    std::string(                                                               \
        ::testing::UnitTest::GetInstance()->current_test_info()->name() )

#define TEST_NAME ( TEST_CASE + "." + TEST_UNIT )

#endif // _LIB_STDHL_UTS_MAIN_H_

//
//  Local variables:
//  mode: c++
//  indent-tabs-mode: nil
//  c-basic-offset: 4
//  tab-width: 4
//  End:
//  vim:noexpandtab:sw=4:ts=4:
//
