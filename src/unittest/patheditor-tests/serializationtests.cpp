/****************************************************************************

 Copyright (c) 2014, Hans Robeers
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

#include "serializationtests.h"
#include "submodules/qtestrunner/qtestrunner.hpp"

#include "patheditor/pathpoint.h"
#include <QJsonArray>

using namespace patheditor;

//void SerializationTests::serializePathPoint()
//{
//    PathPoint p(1, 2);
//    auto json = p.serialize();
//    auto value = json.value("pp");
//    auto array = value.toArray();

//    QCOMPARE(array[0].isDouble(), true);
//    QCOMPARE(array[0].toDouble(), 1.0);

//    QCOMPARE(array[1].isDouble(), true);
//    QCOMPARE(array[1].toDouble(), 2.0);
//}

//void SerializationTests::deserializePathPoint()
//{
//    PathPoint p(3, 4.5);
//    auto json = p.serialize();

//    std::unique_ptr<PathPoint> newPP(PathPoint::deserialize(json));

//    QCOMPARE(newPP->x(), 3.0);
//    QCOMPARE(newPP->y(), 4.5);
//}

void SerializationTests::testSerialization()
{
    Testobject p(2, 3);
    p.setStr("This is a Testobject");
    p.nestedObj()->setSomeString("This is a nested object");

    QJsonObject obj = hrlib::serialization::serialize(&p);

    qDebug() << obj; // TODO QCOMPARE

    QObject *o = hrlib::serialization::deserialize(&obj);

    QCOMPARE(o->metaObject()->className(), p.metaObject()->className());

    Testobject *to = (Testobject*)o;
    QCOMPARE(to->x(), p.x());
    QCOMPARE(to->y(), p.y());
    QCOMPARE(to->str(), p.str());

    Nestedobject *no = to->nestedObj();
    QVERIFY(no != nullptr);
    QCOMPARE(no->someString(), p.nestedObj()->someString());
}

void SerializationTests::testSerializationFailures()
{
    //
    // Test deserialization failure and error message for empty JSON object
    //
    QJsonObject json;
    QString errorMsg;

    QVERIFY(errorMsg.isEmpty());

    QObject* qObj = hrlib::serialization::deserialize(&json, &errorMsg);

    QVERIFY(qObj == 0);
    QVERIFY(!errorMsg.isEmpty());

    //
    // Test deserialization failure and error message for unkown JSON object
    //
    QString errorMsg2;
    QString className("NotRegisteredClass");
    json.insert(className, QJsonValue());

    qObj = hrlib::serialization::deserialize(&json, &errorMsg2);

    QVERIFY(qObj == 0);
    QVERIFY(errorMsg != errorMsg2);
    QVERIFY(errorMsg2.contains(className));
}

QTR_ADD_TEST(SerializationTests)
