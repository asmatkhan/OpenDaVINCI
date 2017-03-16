/**
 * odcolonremover - Tool to remove colons in H264Frame
 * Copyright (C) 2017 Christian Berger
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef COLONREMOVER_H_
#define COLONREMOVER_H_

#include <opendavinci/odcore/opendavinci.h>

namespace odcolonremover {

    /**
     * This class can be used to remove colons in H264Frames.
     */
    class ColonRemover {
        private:
            /**
             * "Forbidden" copy constructor. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the copy constructor.
             *
             * @param obj Reference to an object of this class.
             */
            ColonRemover(const ColonRemover &/*obj*/);

            /**
             * "Forbidden" assignment operator. Goal: The compiler should warn
             * already at compile time for unwanted bugs caused by any misuse
             * of the assignment operator.
             *
             * @param obj Reference to an object of this class.
             * @return Reference to this instance.
             */
            ColonRemover& operator=(const ColonRemover &/*obj*/);

        public:
            ColonRemover();

            virtual ~ColonRemover();

            /**
             * This method runs the colonremover.
             *
             * @param argc Number of command line arguments.
             * @param argv Command line arguments.
             * @return 0 if specified file is integer, 1 if the file is not integer, and 255 if the file could not be opened.
             */
            int32_t run(const int32_t &argc, char **argv);
    };

} // odcolonremover

#endif /*COLONREMOVER_H_*/
