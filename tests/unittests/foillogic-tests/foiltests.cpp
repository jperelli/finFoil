/****************************************************************************

 Copyright (c) 2018, Hans Robeers
 All rights reserved.

 BSD 2-Clause License

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

****************************************************************************/

#include "foiltests.hpp"

#include <boost/format.hpp>

#include "submodules/qtestrunner/qtestrunner.hpp"
#include "foillogic/foil.hpp"
#include "patheditor/ipath.hpp"

using namespace foillogic;
using namespace patheditor;

namespace {
  void assertAllPointsInQuadrant(const IPath *path, int quadrant)
  {
    for (qreal r=0; r <= 1; r+=0.01)
      {
        auto p = path->pointAtPercent(r);

        switch (quadrant)
          {
          case 1:
            if (p.x()<0 || p.y()<0)
              QFAIL((boost::format("x:%1% y:%2% is not in quadrant 1") % p.x() % p.y()).str().c_str());
            break;
          case 2:
            if (p.x()>0 || p.y()<0)
              QFAIL((boost::format("x:%1% y:%2% is not in quadrant 2") % p.x() % p.y()).str().c_str());
            break;
          case 3:
            if (p.x()>0 || p.y()>0)
              QFAIL((boost::format("x:%1% y:%2% is not in quadrant 3") % p.x() % p.y()).str().c_str());
            break;
          case 4:
            if (p.x()<0 || p.y()>0)
              QFAIL((boost::format("x:%1% y:%2% is not in quadrant 4") % p.x() % p.y()).str().c_str());
            break;
          default:
              QFAIL((boost::format("There is no quadrant %1%") % quadrant).str().c_str());
          }
      }
  }
}

void FoilTests::testSIdecoration()
{
  Foil foil;
  // The outline should be fully in the first quadrant (x>0, y>0)
  ::assertAllPointsInQuadrant(foil.outlineSI().get(), 1);
  // The profile top (fin's outside) is on the positive Y direction
  ::assertAllPointsInQuadrant(foil.topProfileSI().get(), 1);
  ::assertAllPointsInQuadrant(foil.topThicknessSI().get(), 1);
  // The profile bottom (fin's inside) is on the negative Y direction
  ::assertAllPointsInQuadrant(foil.botProfileSI().get(), 4);
  ::assertAllPointsInQuadrant(foil.botThicknessSI().get(), 4);
}

QTR_ADD_TEST(FoilTests)
