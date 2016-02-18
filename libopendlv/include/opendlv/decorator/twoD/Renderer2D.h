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

#ifndef HESPERIA_CORE_DECORATOR_TWOD_RENDERER2D_H_
#define HESPERIA_CORE_DECORATOR_TWOD_RENDERER2D_H_

#include <vector>

#include "opendavinci/core/opendavinci.h"

#include "opendlv/decorator/Renderer.h"

namespace opendlv {
    namespace decorator {
        namespace twoD {

            using namespace std;

            /**
             * This class decorates any primitive data structure for rendering
             * with a two-dimensional context. Thus, the concrete two-dimensional
             * context must derive from this class and implement the missing
             * methods.
             */
            class OPENDAVINCI_API Renderer2D : public opendlv::decorator::Renderer {
                public:
                    Renderer2D();

                    virtual ~Renderer2D();

                public:
                    virtual void setColor(const opendlv::data::environment::Point3 &c) = 0;

                    virtual void setPointWidth(const double &width) = 0;

                    virtual void setLineWidth(const double &width) = 0;

                    virtual void drawText(const opendlv::data::environment::Point3 &p, const string &text) = 0;

                    virtual void drawLine(const opendlv::data::environment::Point3 &A, const opendlv::data::environment::Point3 &B) = 0;

                    virtual void drawPoint(const opendlv::data::environment::Point3 &p) = 0;

                    virtual void drawImage(const core::wrapper::Image *image, const opendlv::data::environment::Point3 &originPixelXY, const opendlv::data::environment::Point3 &scalingPixelXY, const float &rotationZ) = 0;

                    virtual void beginPainting();

                    virtual void endPainting();

                    virtual void drawPolyLine(const vector<opendlv::data::environment::Point3> &listOfPoints);

                    virtual void drawPolyLine(const vector<opendlv::data::environment::Point3> &listOfPoints, const double &height);

                    virtual void drawTriangleSet(const opendlv::decorator::models::TriangleSet &ts);

                    virtual void drawListOfTriangleSets(const vector<opendlv::decorator::models::TriangleSet> &listOfTriangleSets);

                    virtual void drawTriangleSet(const opendlv::decorator::models::TriangleSet &ts, const opendlv::data::environment::Point3 &position, const opendlv::data::environment::Point3 &rotation);

                    virtual void drawListOfTriangleSets(const vector<opendlv::decorator::models::TriangleSet> &listOfTriangleSets, const opendlv::data::environment::Point3 &position, const opendlv::data::environment::Point3 &rotation);
            };

        }
    }
} // opendlv::decorator::twoD

#endif /*HESPERIA_CORE_DECORATOR_TWOD_RENDERER2D_H_*/
