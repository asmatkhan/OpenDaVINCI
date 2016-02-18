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

#ifndef HESPERIA_CORE_DATA_SCENARIO_TRAFFICSIGN_H_
#define HESPERIA_CORE_DATA_SCENARIO_TRAFFICSIGN_H_

#include <string>
#include <vector>

#include "opendavinci/core/opendavinci.h"

#include "opendavinci/core/data/SerializableData.h"
#include "opendlv/data/scenario/TrafficControl.h"

namespace opendlv {
    namespace data {
        namespace scenario {

            using namespace std;

            /**
             * This class represents a traffic sign.
             */
            class OPENDAVINCI_API TrafficSign : public TrafficControl {
                public:
                    TrafficSign();

                    virtual ~TrafficSign();

                    /**
                     * Copy constructor.
                     *
                     * @param obj Reference to an object of this class.
                     */
                    TrafficSign(const TrafficSign &obj);

                    /**
                     * Assignment operator.
                     *
                     * @param obj Reference to an object of this class.
                     * @return Reference to this instance.
                     */
                    TrafficSign& operator=(const TrafficSign &obj);

                    virtual void accept(scenario::ScenarioVisitor &visitor);

                    /**
                     * This method returns the value of this traffic sign.
                     *
                     * @return Value of this traffic sign.
                     */
                    const string& getValue() const;

                    /**
                     * This method sets the value of this traffic sign.
                     *
                     * @param v Value of this traffic sign.
                     */
                    void setValue(const string &v);

                    virtual ostream& operator<<(ostream &out) const;
                    virtual istream& operator>>(istream &in);

                    virtual const string toString() const;

                private:
                    string m_value;
            };

        }
    }
} // opendlv::data::scenario

#endif /*HESPERIA_CORE_DATA_SCENARIO_TRAFFICSIGN_H_*/
