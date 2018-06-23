/*
 * Copyright (C) 2018 Tommi Maekitalo
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * As a special exception, you may use this file as part of a free
 * software library without restriction. Specifically, if other files
 * instantiate templates or use macros or inline functions from this
 * file, or you compile this file and link it with other files to
 * produce an executable, this file does not by itself cause the
 * resulting executable to be covered by the GNU General Public
 * License. This exception does not however invalidate any other
 * reasons why the executable file might be covered by the GNU Library
 * General Public License.
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

#ifndef TNTDB_ODBC_STATEMENT_H
#define TNTDB_ODBC_STATEMENT_H

#include <tntdb/iface/istatement.h>
#include <tntdb/odbc/handle.h>

#include <sql.h>
#include <sqltypes.h>

#include <cxxtools/smartptr.h>

#include <map>
#include <vector>

namespace tntdb
{
    namespace odbc
    {
        class Connection;

        class Bind : public cxxtools::RefCounted
        {
            union {
                char* ptr;
                long longValue;
                unsigned long ulongValue;
                short shortValue;
                unsigned short ushortValue;
            } _u;
            size_t _allocatedSize;

            void releaseBuffer();

        public:
            std::vector<SQLSMALLINT> colnums;
            SQLSMALLINT boundType;

            Bind()
                : _allocatedSize(0),
                  boundType(SQL_UNKNOWN_TYPE)
                { }

            ~Bind()
                { releaseBuffer(); }

            char* ptr(size_t size);
            long& longValue()             { releaseBuffer(); return _u.longValue; }
            unsigned long& ulongValue()   { releaseBuffer(); return _u.ulongValue; }
            short& shortValue()           { releaseBuffer(); return _u.shortValue; }
            unsigned short& ushortValue() { releaseBuffer(); return _u.ushortValue; }
        };

        typedef std::map<std::string, cxxtools::SmartPtr<Bind> > BindMap;

        class Statement : public IStatement
        {
            Connection* _conn;
            Handle _hStmt;

            BindMap _binds;

            Bind& getBind(const std::string& col) const;

        public:
            Statement(Connection* conn, const std::string& query);
            ~Statement();
            void clear();
            void setNull(const std::string& col);
            void setBool(const std::string& col, bool data);
            void setShort(const std::string& col, short data);
            void setInt(const std::string& col, int data);
            void setLong(const std::string& col, long data);
            void setUnsignedShort(const std::string& col, unsigned short data);
            void setUnsigned(const std::string& col, unsigned data);
            void setUnsignedLong(const std::string& col, unsigned long data);
            void setInt32(const std::string& col, int32_t data);
            void setUnsigned32(const std::string& col, uint32_t data);
            void setInt64(const std::string& col, int64_t data);
            void setUnsigned64(const std::string& col, uint64_t data);
            void setDecimal(const std::string& col, const Decimal& data);
            void setFloat(const std::string& col, float data);
            void setDouble(const std::string& col, double data);
            void setChar(const std::string& col, char data);
            void setString(const std::string& col, const std::string& data);
            void setBlob(const std::string& col, const Blob& data);
            void setDate(const std::string& col, const Date& data);
            void setTime(const std::string& col, const Time& data);
            void setDatetime(const std::string& col, const Datetime& data);

            size_type execute();
            tntdb::Result select();
            tntdb::Row selectRow();
            tntdb::Value selectValue();
            ICursor* createCursor(unsigned fetchsize);
        };
    }
}

#endif
