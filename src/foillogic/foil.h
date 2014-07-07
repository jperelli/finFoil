/****************************************************************************
  
 Copyright (c) 2013, Hans Robeers
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

#ifndef FOIL_H
#define FOIL_H

#include "foillogicfwd/foillogicfwd.h"
#include "patheditorfwd/patheditorfwd.h"

#include <QObject>
#include <memory>
#include <QUuid>
#include "path.h"

namespace foillogic
{
    class Foil : public QObject
    {
        Q_OBJECT

        // read-write properties
        Q_PROPERTY(foillogic::Outline* outline READ pOutline WRITE pSetOutline)
        Q_PROPERTY(foillogic::Profile* profile READ pProfile WRITE pSetProfile)
        Q_PROPERTY(foillogic::ThicknessProfile* thickness READ pThickness WRITE pSetThickness)
        Q_PROPERTY(QUuid uuid READ uuid WRITE setUuid)
        Q_PROPERTY(QStringList history READ history WRITE setHistory) // QStringList to omit class information (Compacter serialization)

    public:
        Q_INVOKABLE explicit Foil(QObject *parent = 0);

        std::shared_ptr<Outline> outline();
        std::shared_ptr<Profile> profile();
        std::shared_ptr<ThicknessProfile> thickness();

        // Q_PROPERTY getters
        Outline* pOutline() { return outline().get(); }
        Profile* pProfile() { return profile().get(); }
        ThicknessProfile* pThickness() { return thickness().get(); }
        QUuid uuid();
        QStringList history();

        // Q_PROPERTY setters
        void pSetOutline(Outline *outline);
        void pSetProfile(Profile *profile);
        void pSetThickness(ThicknessProfile *thickness);
        void setUuid(QUuid uuid);
        void setHistory(QStringList history);

        virtual ~Foil();

    signals:
        void foilChanged(Foil* sender);
        void foilReleased(Foil* sender);

    public slots:

    private:
        QUuid _uuid;
        QList<QUuid> _history;
        std::shared_ptr<foillogic::Outline> _outline;
        std::shared_ptr<foillogic::Profile> _profile;
        std::shared_ptr<foillogic::ThicknessProfile> _thickness;

        void initOutline();
        void initProfile();
        void initThickness();

        void connectOutline();
        void connectProfile();
        void connectThickness();

    private slots:
        void onFoilChanged();
        void onFoilReleased();

        void onProfileChanged();
    };
}
SERIALIZABLE(foillogic::Foil, foil)

#endif // FOIL_H