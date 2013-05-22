/*
	grive: an GPL program to sync a local directory with Google Drive
	Copyright (C) 2012  Wan Wai Ho

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation version 2
	of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#pragma once

#include <sys/inotify.h>
#include <stdio.h>

#include "http/Agent.hh"
#include "State.hh"
#include "Entry.hh"

namespace gr { namespace v1 {

class NotifyEventsHandler {
public:
	NotifyEventsHandler(State state, http::Agent * http);

	void get_event (int fd, const std::string& target);
	void init();


	virtual ~NotifyEventsHandler();

private:
	State m_state;
	http::Agent * m_http;

	static const int BUFF_SIZE = (sizeof(struct inotify_event)+FILENAME_MAX)*1024;

	void handle_error (int error);



};

} }
