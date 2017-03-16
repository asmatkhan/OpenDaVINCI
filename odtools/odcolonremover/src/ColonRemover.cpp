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

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

#include <opendavinci/odcore/data/Container.h>
#include <opendavinci/generated/odcore/data/image/H264Frame.h>

#include "ColonRemover.h"

namespace odcolonremover {

    using namespace std;
    using namespace odcore;
    using namespace odcore::base;
    using namespace odcore::data;

    ColonRemover::ColonRemover() {}

    ColonRemover::~ColonRemover() {}

    int32_t ColonRemover::run(const int32_t &argc, char **argv) {
        (void)argv;
        if (argc == 1) {
            fstream fin;
            fin.open("/dev/stdin", ios_base::in|ios_base::binary);

            fstream fout;
            fout.open("/dev/stdout", ios_base::out|ios_base::binary);

            if (fin.good() && fout.good()) {
                while (fin.good()) {
                    Container c;
                    fin >> c;

                    if (c.getDataType() == odcore::data::image::H264Frame::ID()) {
                        odcore::data::image::H264Frame f = c.getData<odcore::data::image::H264Frame>();

                        string filename = f.getH264Filename();
                        filename.erase(std::remove(filename.begin(), filename.end(), ':'), filename.end());
                        f.setH264Filename(filename);

                        Container c2(f);
                        c2.setSentTimeStamp(c.getSentTimeStamp());
                        c2.setReceivedTimeStamp(c.getReceivedTimeStamp());
                        c2.setSampleTimeStamp(c.getSampleTimeStamp());
                        c = c2;
                    }

                    fout << c;
                    fout.flush();
                }
                fin.close();
                fout.close();
            }
        }

        return 0;
    }

} // odcolonremover

