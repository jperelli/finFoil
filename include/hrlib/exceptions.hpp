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

#ifndef HRLIB_EXCEPTIONS_HPP
#define HRLIB_EXCEPTIONS_HPP

#include <QObject>
#include <QString>
#include <exception>

namespace hrlib
{
    class Exception : public std::exception
    {
    public:
        explicit Exception(QObject *thrower = 0) throw();
        explicit Exception(QString &message, QObject *thrower = 0) throw();
        explicit Exception(QString &message, std::exception &innerException, QObject *thrower = 0) throw();

        virtual const char* what() const throw() override;

        virtual const QString& message() const throw();
        virtual const std::exception& innerException() const throw();

        virtual ~Exception() throw() {}

    protected:
        void setMessage(QString &message, QObject *thrower = 0) throw();

        QString _message;
        std::exception *_innerException;
    };


    class ArgumentException : public Exception
    {
    public:
        explicit ArgumentException(QString &message, QObject *thrower = 0) throw()
            : Exception(message, thrower) { }

        virtual ~ArgumentException() throw() {}
    };

    class NotImplementedException : public Exception
    {
    public:
        explicit NotImplementedException(QString &message, QObject *thrower = 0) throw()
            : Exception(message, thrower) { }

        virtual ~NotImplementedException() throw() {}
    };

    class ImplementationException : public Exception
    {
    public:
        explicit ImplementationException(QString &message, QObject *thrower = 0) throw()
            : Exception(message, thrower) { }

        virtual ~ImplementationException() throw() {}
    };

    class InitializationException : public Exception
    {
    public:
        explicit InitializationException(QString &message, QObject *thrower = 0) throw()
            : Exception(message, thrower) { }

        virtual ~InitializationException() throw() {}
    };
}

#endif // HRLIB_EXCEPTIONS_HPP
