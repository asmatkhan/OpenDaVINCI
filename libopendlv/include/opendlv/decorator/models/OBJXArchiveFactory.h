/**
 * OpenDLV - Simulation environment
 * Copyright (C) 2008 - 2015 Christian Berger, Bernhard Rumpe
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

#ifndef HESPERIA_CORE_DECORATOR_MODELS_OBJXARCHIVEFACTORY_H_
#define HESPERIA_CORE_DECORATOR_MODELS_OBJXARCHIVEFACTORY_H_

#include <iostream>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/base/Mutex.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"

#include "opendlv/decorator/models/OBJXArchive.h"

namespace opendlv {
    namespace decorator {
        namespace models {

            using namespace std;

            /**
             * This class produces an instance for accessing the contents
             * of an OBJXArchive (.objx) from a given input stream.
             */
            class OPENDAVINCI_API OBJXArchiveFactory {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    OBJXArchiveFactory(const OBJXArchiveFactory &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    OBJXArchiveFactory& operator=(const OBJXArchiveFactory &);

                private:
                    OBJXArchiveFactory();

                public:
                    virtual ~OBJXArchiveFactory();

                    /**
                     * This method returns a static instance for this factory.
                     *
                     * @return Instance of this factory.
                     */
                    static OBJXArchiveFactory& getInstance();

                    /**
                     * This method returns the OBJXArchive data structure for a simple obj file without material and textures.
                     *
                     * @param in Input stream containing a plain obj file.
                     * @return OBJXArchive.
                     * @throws InvalidArgumentException if the URL could not be used to create the data structure.
                     */
                    OBJXArchive* getOBJXArchiveFromPlainOBJFile(istream &in) throw (odcore::exceptions::InvalidArgumentException);

                    /**
                     * This method returns the OBJXArchive data structure.
                     *
                     * @param in Input stream to be used for building the OBJX archive file.
                     * @return OBJXArchive.
                     * @throws InvalidArgumentException if the URL could not be used to create the data structure.
                     */
                    OBJXArchive* getOBJXArchive(istream &in) throw (odcore::exceptions::InvalidArgumentException);

                private:
                    static odcore::base::Mutex m_singletonMutex;
                    static OBJXArchiveFactory* m_singleton;
            };

        }
    }
} // opendlv::decorator::models

#endif /*HESPERIA_CORE_DECORATOR_MODELS_OBJXARCHIVEFACTORY_H_*/
