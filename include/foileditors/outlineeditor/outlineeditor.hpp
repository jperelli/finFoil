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

#ifndef OUTLINEEDITOR_HPP
#define OUTLINEEDITOR_HPP

#include "patheditor/fwd/patheditorfwd.hpp"
#include "foillogic/fwd/foillogicfwd.hpp"

#include <QWidget>
#include <memory>

using namespace patheditor;

namespace foileditors
{
    /**
     * Editor to edit the foil's outline.
     * This editor can display the thickness contours while editing.
     */
    class OutlineEditor : public QWidget
    {
        Q_OBJECT
    public:
        explicit OutlineEditor(QWidget *parent = 0);

        void setFoil(foillogic::Foil *foil);
        foillogic::FoilCalculator* foilCalculator();

        virtual ~OutlineEditor();

    signals:

    public slots:
        void setGridUnitSize(qreal pxPerUnit);

    private:
        std::unique_ptr<foillogic::FoilCalculator> _foilCalculator;

        PathEditorWidget* _topPathEditor;
        PathEditorWidget* _botPathEditor;
    };
}

#endif // OUTLINEEDITOR_HPP
