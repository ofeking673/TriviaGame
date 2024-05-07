#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
    return (requestInfo.id == CloseRoom ||
        requestInfo.id == StartGame ||
        requestInfo.id == GetRoomState);
}

RequestResult RoomAdminRequestHandler::HandleRequest(Requestinfo requestInfo)
{
    if (isRequestRelevant(requestInfo))
    {
        switch (requestInfo.id) {
        case CloseRoom:
            return closeRoom(requestInfo);
        case StartGame:
            return startGame(requestInfo);
        case GetRoomState:
            return getRoomState(requestInfo);
        }
    }
    else
    {
        return error(requestInfo);
    }
}

RequestResult RoomAdminRequestHandler::closeRoom(Requestinfo requestInfo)
{
    m_room.removeUser(m_user);
    CloseRoomResponse resp;
    resp.status = TEMP_ROOM_CLOSE_STATUS;
    m_room.status = 2;
    RequestResult requestResult = JsonResponsePacketSerializer::serializeResponse(resp);
    requestResult.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
    return requestResult;

}

RequestResult RoomAdminRequestHandler::startGame(Requestinfo requestInfo)
{
    m_room.status = 1;
    m_room.startGame(m_user);
    StartGameResponse start;
    start.status = TEMP_ROOM_START_STATUS;

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(start);
    //need to make game handler
}

RequestResult RoomAdminRequestHandler::getRoomState(Requestinfo requestInfo)
{
    RequestResult rr;    
    /*
    status (unsigned int)
hasGameBegun (bool)
players (list<string>)
AnswerCount (unsigned int)
answerTimeOut
*/
    GetRoomStateResponse resp;
    getRoomStateResponseByRoom(m_room, resp);
    rr.response = JsonResponsePacketSerializer::serializeResponse(resp);
    rr.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room);
    return rr;
}

RequestResult RoomAdminRequestHandler::error(Requestinfo requestInfo)
{
    RequestResult rr;
}

/*
void getRoomStateResponseByRoom(Room m_room, GetRoomStateResponse& resp) {

}*/