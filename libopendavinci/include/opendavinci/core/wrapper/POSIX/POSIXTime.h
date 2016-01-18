/**
 * OpenDaVINCI - Portable middleware for distributed components.
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXTIME_H_
#define OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXTIME_H_

#include "opendavinci/core/opendavinci.h"
#include "opendavinci/core/wrapper/SystemLibraryProducts.h"
#include "opendavinci/core/wrapper/Time.h"

namespace core { namespace wrapper { template <core::wrapper::SystemLibraryProducts product> class TimeFactoryWorker; } }

namespace core {
    namespace wrapper {
        namespace POSIX {

            /**
             * This class implements the time using POSIX.
             *
             * @See Time
             */
            class POSIXTime : public Time {
                private:
                    friend class TimeFactoryWorker<SystemLibraryPosix>;

                    POSIXTime();

                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    POSIXTime(const POSIXTime &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    POSIXTime& operator=(const POSIXTime &);

                public:
                    virtual ~POSIXTime();

                    virtual int32_t getSeconds() const;

                    virtual int32_t getPartialMicroseconds() const;

                private:
                    int32_t m_seconds;
                    int32_t m_partialMicroseconds;
            };

        }
    }
} // core::wrapper::POSIX

#endif /*OPENDAVINCI_CORE_WRAPPER_POSIX_POSIXTIME_H_*/
