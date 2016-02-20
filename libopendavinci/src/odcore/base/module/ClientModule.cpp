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

#include <iostream>

#include "opendavinci/odcore/base/module/AbstractCIDModule.h"
#include "opendavinci/odcore/base/module/ClientModule.h"
#include "opendavinci/odcore/dmcp/connection/Client.h"
#include "opendavinci/odcore/dmcp/discoverer/Client.h"
#include "opendavinci/odcore/exceptions/Exceptions.h"
#include "opendavinci/odcore/opendavinci.h"
#include "opendavinci/generated/coredata/dmcp/Constants.h"
#include "opendavinci/generated/coredata/dmcp/ModuleDescriptor.h"
#include "opendavinci/generated/coredata/dmcp/ModuleStateMessage.h"

namespace odcore {
    namespace base {
        namespace module {

            using namespace std;

            using namespace odcore;
            using namespace odcore::base;
            using namespace odcore::data;
            using namespace odcore::dmcp;
            using namespace odcore::exceptions;
            using namespace coredata::dmcp;

            ClientModule::ClientModule(const int32_t &argc, char **argv, const string &name) throw (InvalidArgumentException) :
                AbstractCIDModule(argc, argv),
                m_name(name),
                m_keyValueConfiguration(),
                m_serverInformation(),
                m_dmcpClient() {}

            ClientModule::~ClientModule() {}

            odcore::SharedPointer<odcore::dmcp::connection::Client>& ClientModule::getDMCPClient() {
                return m_dmcpClient;
            }

            const string ClientModule::getName() const {
                return m_name;
            }

            const KeyValueConfiguration ClientModule::getKeyValueConfiguration() const {
                return m_keyValueConfiguration;
            }

            const coredata::dmcp::ServerInformation ClientModule::getServerInformation() const {
                return m_serverInformation;
            }

            coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode ClientModule::runModule() {
                // Try to discover supercomponent.
                try {
                    SharedPointer<discoverer::Client> discovererClient =
                        SharedPointer<discoverer::Client>(
                                new discoverer::Client(getMultiCastGroup(),
                                                       coredata::dmcp::Constants::BROADCAST_PORT_SERVER,
                                                       coredata::dmcp::Constants::BROADCAST_PORT_CLIENT,
                                                       getName()));

                    bool supercomponentFound = false;
                    uint32_t attempt  = 0;

                    while ( !supercomponentFound && ( attempt < coredata::dmcp::Constants::CONNECTION_RETRIES)) {
                    	CLOG1 << "(ClientModule) discovering supercomponent..." << endl;
                    	supercomponentFound = discovererClient->existsServer();
                    	attempt++;
                    }

                    if ( !supercomponentFound ) {
                        CLOG1 << "(ClientModule) no supercomponent running for " << getMultiCastGroup() << endl;
                        return coredata::dmcp::ModuleExitCodeMessage::NO_SUPERCOMPONENT;
                    }

                    m_serverInformation = discovererClient->getServerInformation();
                    CLOG1 << "(ClientModule) supercomponent found at " << m_serverInformation.toString() << endl;
                }
                catch (...) {
                    CLOG1 << "(ClientModule) error while discovering supercomponent." << endl;
                    return coredata::dmcp::ModuleExitCodeMessage::SERIOUS_ERROR;
                }

                CLOG1 << "(ClientModule) connecting to supercomponent..." << endl;
                string myVersion = "No version set.";
                ModuleDescriptor md(getName(), getIdentifier(), myVersion, getFrequency());

                try {
                    // Try to get configuration from DMCP server.
                    m_dmcpClient = SharedPointer<connection::Client>(
                            new connection::Client(md, m_serverInformation));
                    m_dmcpClient->setSupercomponentStateListener(this);
                    m_dmcpClient->initialize();

                    // Get configuration from DMCP client.
                    m_keyValueConfiguration = m_dmcpClient->getConfiguration();
                } catch (ConnectException& e) {
                    CLOG1 << "(ClientModule) connecting to supercomponent failed: " << e.getMessage() << endl;
                    return coredata::dmcp::ModuleExitCodeMessage::SERIOUS_ERROR;
                }

                CLOG1 << "(ClientModule) connecting to supercomponent...done - managed level: " << m_serverInformation.getManagedLevel() << endl;

                // Run user implementation from derived ConferenceClientModule.
                coredata::dmcp::ModuleExitCodeMessage::ModuleExitCode retVal = runModuleImplementation();

                if (m_dmcpClient.isValid()) {
                    m_dmcpClient->sendModuleExitCode(retVal);
                }

                return retVal;
            }

            void ClientModule::handleConnectionLost() {
                CLOG1 << "(ClientModule) connection to supercomponent lost. Shutting down" << endl;
                setModuleState(coredata::dmcp::ModuleStateMessage::NOT_RUNNING);
            }

        }
    }
} // odcore::base::module