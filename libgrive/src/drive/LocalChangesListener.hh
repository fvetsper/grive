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


#include <pthread.h>
#include <string>
#include <cstring>
#include <errno.h>
#include <stdio.h>

#include "http/Agent.hh"
#include "State.hh"
#include "NotifyEventsHandler.hh"

namespace gr { namespace v1 {

class LocalChangesListener
{
public:
	LocalChangesListener(State& state, http::Agent * http);
	~LocalChangesListener();
	void start ();

private:
	pthread_t thread;

	NotifyEventsHandler events;

	static void * run(void * ptr);
};

} }
