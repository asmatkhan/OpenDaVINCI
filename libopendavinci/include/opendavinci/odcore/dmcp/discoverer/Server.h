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

#ifndef OPENDAVINCI_DMCP_DISCOVER_SERVER_H_
#define OPENDAVINCI_DMCP_DISCOVER_SERVER_H_

#include <string>
#include <vector>

#include "opendavinci/odcore/opendavinci.h"
#include <memory>
#include "opendavinci/odcore/io/StringListener.h"
#include "opendavinci/odcore/io/udp/UDPReceiver.h"
#include "opendavinci/odcore/io/udp/UDPSender.h"
#include "opendavinci/generated/odcore/data/dmcp/ServerInformation.h"

namespace odcore {
    namespace dmcp {
        namespace discoverer {

            using namespace std;

            class OPENDAVINCI_API Server : public odcore::io::StringListener {
                private:
                    /**
                     * "Forbidden" copy constructor. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the copy constructor.
                     */
                    Server(const Server &);

                    /**
                     * "Forbidden" assignment operator. Goal: The compiler should warn
                     * already at compile time for unwanted bugs caused by any misuse
                     * of the assignment operator.
                     */
                    Server& operator=(const Server &);

                public:
                    Server(const odcore::data::dmcp::ServerInformation &serverInformation,
                           const std::string &group, const uint32_t &serverPort, const uint32_t &clientPort,
                           const vector<string> &modulesToIgnore);
                    virtual ~Server();

                    void startResponding();
                    void stopResponding();

                    virtual void onRequest();

                protected:
                    virtual void nextString(const string &s);

                    void sendResponseMessage(const string &s);

                    std::shared_ptr<odcore::io::udp::UDPSender> m_sender;
                    std::shared_ptr<odcore::io::udp::UDPReceiver> m_receiver;

                    odcore::data::dmcp::ServerInformation m_serverInformation;

                    vector<string> m_modulesToIgnore;
            };
        }
    }
}
#endif // OPENDAVINCI_DMCP_DISCOVER_SERVER_H_
