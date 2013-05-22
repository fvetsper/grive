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

#include "NotifyEventsHandler.hh"
#include "Resource.hh"
#include "util/log/Log.hh"
#include "util/FileSystem.hh"


namespace gr { namespace v1 {

NotifyEventsHandler::NotifyEventsHandler(State state, http::Agent * http) :
		m_state (state),
		m_http (http)
{

}

NotifyEventsHandler::~NotifyEventsHandler() {
}



void NotifyEventsHandler::get_event(int fd, const std::string& target)
{
	   ssize_t len, i = 0;
	   char buff[BUFF_SIZE] = {0};

	   len = read (fd, buff, BUFF_SIZE);

	   if (len < 0)
	   {
		   handle_error(errno);
	   }

	   while (i < len) {
	      struct inotify_event *pevent = (struct inotify_event *)&buff[i];

	      if (pevent->mask & IN_CREATE)
		  {
			Log( "starting create item sync" , log::error ) ;
			m_state.AddNewResource(m_http, pevent->name);
		  }
	      if (pevent->mask & IN_DELETE)
	      {
	    	  Log( "starting delete item sync" , log::error ) ;
	    	  Resource *r = m_state.FindByName(std::string(pevent->name));
	    	  r->DeleteRemote(m_http);
	      }
	      if (pevent->mask & IN_MODIFY)
	      {
	    	  Log( "starting modify item sync" , log::error ) ;
	      }
	      i += sizeof(struct inotify_event) + pevent->len;

	   }
}

void NotifyEventsHandler::init()
{
int fd = inotify_init();

		if (fd > 0)
		{
			int wd = inotify_add_watch (fd, "/home/felix/drive", IN_MOVE | IN_CREATE | IN_DELETE);
			if (wd < 0)
			{
				handle_error (errno);
			}
			else
			{
				while (1)
				{
					get_event(fd, "/home/felix/drive");
				}
			}
		}
		else
		{
			handle_error(errno);
		}
}

void NotifyEventsHandler::handle_error (int error)
{
	Log( "error occurred on getting notification from file system: %1%." , strerror(error), log::error ) ;
}

} }
