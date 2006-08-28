/* 
 * Copyright (C) 2005 Tommi Maekitalo
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

#include <tntdb/mysql/row.h>
#include <tntdb/mysql/bits/resultrow.h>
#include <tntdb/mysql/value.h>
#include <cxxtools/log.h>

log_define("tntdb.mysql.row");

namespace tntdb
{
  namespace mysql
  {
    Row::Row(const Result result_, MYSQL_RES* res, MYSQL_ROW row_)
      : row(new ResultRow(result_, res, row_))
    {
    }

    Row::const_iterator Row::begin() const
    {
      return const_iterator(*this, 0);
    }

    Row::const_iterator Row::end() const
    {
      return const_iterator(*this, size());
    }
  }
}
