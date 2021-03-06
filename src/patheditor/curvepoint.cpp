/****************************************************************************

 Copyright (c) 2015, Hans Robeers
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

#include "patheditor/curvepoint.hpp"

#include <QGraphicsScene>
#include "patheditor/pathsettings.hpp"
#include "patheditor/pointhandle.hpp"
#include "patheditor/continuitylever.hpp"

using namespace patheditor;

CurvePoint::CurvePoint(qreal xpos, qreal ypos)
    : PathPoint(xpos, ypos), _continuous(false)
{
}

void CurvePoint::createPointHandleImpl(QGraphicsItem *parent, const PathSettings *settings)
{
    PointHandle *newPointHandle = new PointHandle(this, settings->handleSize(), settings->pointBrush(), parent);
    newPointHandle->setZValue(1);
    replaceCurrentPointHandle(newPointHandle);
}

bool CurvePoint::continuous() const
{
    return _continuous;
}

void CurvePoint::setContinuous(bool continuous)
{
    if (continuous == _continuous)
        return;

    if(continuous)
    {
        std::shared_ptr<ContinuityLever> lever(new ContinuityLever(this));

        foreach(std::weak_ptr<PathPoint> followingPoint, this->followingPoints())
        {
            std::shared_ptr<PathPoint> fPnt = followingPoint.lock();
            fPnt->setRestrictor(lever);
        }

        _continuous = true;
    }
    else
    {
        foreach(std::weak_ptr<PathPoint> followingPoint, this->followingPoints())
        {
            std::shared_ptr<PathPoint> fPnt = followingPoint.lock();
            fPnt->removeRestrictor();
        }

        _continuous = false;
    }
}
