/*
 * This file is part of the TrinityCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ServiceDispatcher.h"
#include "AccountService.h"
#include "AuthenticationService.h"
#include "ConnectionService.h"
#include "GameUtilitiesService.h"
#include "Log.h"
#include "Session.h"
#include "api/client/v1/block_list_listener.pb.h"
#include "api/client/v1/block_list_service.pb.h"
#include "api/client/v1/club_membership_service.pb.h"
#include "api/client/v1/club_service.pb.h"
#include "api/client/v2/notification_service.pb.h"
#include "api/client/v2/report_service.pb.h"
#include "api/client/v2/whisper_service.pb.h"
#include "friends_service.pb.h"
#include "notification_service.pb.h"
#include "presence_service.pb.h"
#include "report_service.pb.h"
#include "resource_service.pb.h"

Battlenet::ServiceDispatcher::ServiceDispatcher()
{
    AddService<Services::Account>();
    AddService<Services::Authentication>();
    AddService<Service<block_list::v1::client::BlockListService>>();
    AddService<Service<club_membership::v1::client::ClubMembershipService>>();
    AddService<Service<club::v1::client::ClubService>>();
    AddService<Services::Connection>();
    AddService<Service<friends::v1::FriendsService>>();
    AddService<Services::GameUtilities>();
    AddService<Service<notification::v1::NotificationService>>();
    AddService<Service<notification::v2::client::NotificationService>>();
    AddService<Service<presence::v1::PresenceService>>();
    AddService<Service<report::v1::ReportService>>();
    AddService<Service<report::v2::ReportService>>();
    AddService<Service<resources::v1::ResourcesService>>();
    AddService<Service<whisper::v2::client::WhisperService>>();
}

void Battlenet::ServiceDispatcher::Dispatch(Session* session, uint32 serviceHash, uint32 token, uint32 methodId, MessageBuffer buffer)
{
    auto itr = _dispatchers.find(serviceHash);
    if (itr != _dispatchers.end())
        itr->second(session, token, methodId, std::move(buffer));
    else
        TC_LOG_DEBUG("session.rpc", "{} tried to call invalid service 0x{:X}", session->GetClientInfo(), serviceHash);
}

Battlenet::ServiceDispatcher& Battlenet::ServiceDispatcher::Instance()
{
    static ServiceDispatcher instance;
    return instance;
}
