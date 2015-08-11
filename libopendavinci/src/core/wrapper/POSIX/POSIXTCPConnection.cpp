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

#include <cerrno>
#include <cstring>

#include "core/wrapper/ConcurrencyFactory.h"
#include "core/wrapper/MutexFactory.h"
#include "core/wrapper/POSIX/POSIXTCPConnection.h"

namespace core {
    namespace wrapper {
        namespace POSIX {

            using namespace std;

            POSIXTCPConnection::POSIXTCPConnection(const int32_t &fileDescriptor) :
                m_thread(),
                m_socketMutex(),
                m_fileDescriptor(fileDescriptor),
                m_buffer(),
                m_ip(""),
                m_port(0) {
                initialize();
            }

            POSIXTCPConnection::POSIXTCPConnection(const std::string &ip, const uint32_t &port) :
                m_thread(),
                m_socketMutex(),
                m_fileDescriptor(-1),
                m_buffer(),
                m_ip(ip),
                m_port(port) {
                initialize();

                addrinfo hints;
                memset(&hints, 0, sizeof(hints));
                hints.ai_family = AF_INET;
                hints.ai_socktype = SOCK_STREAM;

                std::stringstream portString;
                portString << port;
                const std::string &sstr = portString.str();

                addrinfo* res;
                if (getaddrinfo(ip.c_str(), sstr.c_str(), &hints, &res) == -1) {
                    freeaddrinfo(res);

                    stringstream s;
                    s << "[core::wrapper::POSIXTCPConnection] Error while getting info at " << __FILE__ << ": " << __LINE__ << ": " << strerror(errno);
                    throw s.str();
                }

                m_fileDescriptor = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
                if (m_fileDescriptor < 0) {
                    freeaddrinfo(res);

                    stringstream s;
                    s << "[core::wrapper::POSIXTCPConnection] Error while creating socket at " << __FILE__ << ": " << __LINE__ << ": " << strerror(errno);
                    throw s.str();
                }

                if (connect(m_fileDescriptor, res->ai_addr, res->ai_addrlen) < 0) {
                    freeaddrinfo(res);

                    stringstream s;
                    s << "[core::wrapper::POSIXTCPConnection] Error connecting to socket at " << __FILE__ << ": " << __LINE__ << ": " << strerror(errno);
                    throw s.str();
                }

                freeaddrinfo(res);
            }

            POSIXTCPConnection::~POSIXTCPConnection() {
                stop();
                close(m_fileDescriptor);
            }

            void POSIXTCPConnection::start() {
                m_thread->start();
            }

            void POSIXTCPConnection::stop() {
                m_thread->stop();
            }

            bool POSIXTCPConnection::isRunning() {
                return m_thread->isRunning();
            }

            void POSIXTCPConnection::run() {
                fd_set rfds;
                struct timeval timeout;
                bool ready = true;

                while (isRunning() && ready) {
                    timeout.tv_sec = 1;
                    timeout.tv_usec = 0;

                    FD_ZERO(&rfds);
                    FD_SET(m_fileDescriptor, &rfds);

                    select(m_fileDescriptor + 1, &rfds, NULL, NULL, &timeout);

                    if (FD_ISSET(m_fileDescriptor, &rfds)) {
                        int32_t numBytes = recv(m_fileDescriptor, m_buffer, BUFFER_SIZE, 0);

                        if (numBytes > 0 ) {
                            // Get data.
                            string stringData(m_buffer, numBytes);

                            // Process data in higher layers.
                            receivedString(stringData);
                        }
                        else if (numBytes <= 0) {
                            // Handle error: numBytes == 0 if peer shut down, numBytes < 0 in any case of error.
                            invokeConnectionListener();
                            ready = false;
                        }
                    }
                }
            }

            void POSIXTCPConnection::sendImplementation(const std::string& data) {
                m_socketMutex->lock();
                int32_t numBytes = ::send(m_fileDescriptor, data.c_str(), data.length(), 0);

                if (numBytes == -1) {
                    // Handle error.
                    invokeConnectionListener();
                }
                m_socketMutex->unlock();
            }


            void POSIXTCPConnection::initialize() {
                m_thread = auto_ptr<Thread>(ConcurrencyFactory::createThread(*this));
                if (m_thread.get() == NULL) {
                    stringstream s;
                    s << "[core::wrapper::POSIXTCPConnection] Error creating thread at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }

                m_socketMutex = auto_ptr<Mutex>(MutexFactory::createMutex());
                if (m_socketMutex.get() == NULL) {
                    stringstream s;
                    s << "[core::wrapper::POSIXTCPConnection] Error creating mutex at " << __FILE__ << ": " << __LINE__;
                    throw s.str();
                }
            }
        }
    }
}
