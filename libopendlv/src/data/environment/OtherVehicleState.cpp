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

#include <memory>
#include <ostream>
#include <string>

#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/odcore/serialization/Deserializer.h"
#include "opendavinci/odcore/serialization/SerializationFactory.h"
#include "opendavinci/odcore/serialization/Serializer.h"
#include "opendlv/data/environment/OtherVehicleState.h"
#include "opendlv/data/environment/Point3.h"
#include "opendlv/data/environment/PointShapedObject.h"

namespace opendlv {
    namespace data {
        namespace environment {

            using namespace std;
            using namespace odcore::base;
            using namespace opendlv::data::environment;

            OtherVehicleState::OtherVehicleState() :
                    PointShapedObject(),
                    m_identifier(0) {}

            OtherVehicleState::OtherVehicleState(const uint32_t &id,
                    const Point3 &position, const Point3 &rotation,
                    const Point3 &velocity, const Point3 &acceleration) :
                    PointShapedObject(position, rotation, velocity, acceleration),
                    m_identifier(id) {}

            OtherVehicleState::OtherVehicleState(const OtherVehicleState &obj) :
                    PointShapedObject(obj),
                    m_identifier(obj.getIdentifier()) {}

            OtherVehicleState::~OtherVehicleState() {}

            OtherVehicleState& OtherVehicleState::operator=(const OtherVehicleState &obj) {
                PointShapedObject::operator=(obj);
                setIdentifier(obj.getIdentifier());

                return (*this);
            }

            int32_t OtherVehicleState::ID() {
                return 36;
            }

            int32_t OtherVehicleState::getID() const {
                return 36;
            }

            const string OtherVehicleState::getShortName() const {
                return "OtherVehicleState";
            }

            const string OtherVehicleState::getLongName() const {
                return "hesperia.data.environment.OtherVehicleState";
            }

            const string OtherVehicleState::toString() const {
                stringstream s;
                s << "Other Vehicle State (ID: " << m_identifier << ")" << PointShapedObject::toString();
                return s.str();
            }

            uint32_t OtherVehicleState::getIdentifier() const {
                return m_identifier;
            }

            void OtherVehicleState::setIdentifier(const uint32_t &id) {
                m_identifier = id;
            }

            ostream& OtherVehicleState::operator<<(ostream &out) const {
                // Serializer super class.
                PointShapedObject::operator<<(out);

                // Serialize this class.
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Serializer> s = sf.getQueryableNetstringsSerializer(out);

                s->write(1, m_identifier);

                return out;
            }

            istream& OtherVehicleState::operator>>(istream &in) {
                // Deserializer super class.
                PointShapedObject::operator>>(in);

                // Deserialize this class.
                odcore::serialization::SerializationFactory& sf=odcore::serialization::SerializationFactory::getInstance();

                std::shared_ptr<odcore::serialization::Deserializer> d = sf.getQueryableNetstringsDeserializer(in);

                d->read(1, m_identifier);

                return in;
            }

        }
    }
} // opendlv::data::environment
