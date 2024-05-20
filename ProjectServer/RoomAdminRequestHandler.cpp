#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
    return (requestInfo.id == CloseRoom ||
        requestInfo.id == StartGame ||
        requestInfo.id == GetRoomState ||
        requestInfo.id == GetPlayersInRoom ||
        m_roomManager.doesRoomExist(m_id));
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
        case GetPlayersInRoom:
            return getPlayersInRoom(requestInfo);
        }
    }
    else
    {
        return error(requestInfo);
    }
}

RequestResult RoomAdminRequestHandler::closeRoom(Requestinfo requestInfo)
{
    // TO-DO
    // IMPORTANT
    // Send leave messages to other members of room
    CloseRoomResponse closeRoomResponse;

    closeRoomResponse.status = TEMP_ROOM_CLOSE_STATUS;
    m_room.status = 2;

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(closeRoomResponse);

    if (m_roomManager.getRoom(m_id).getAllUsers().size() < 2)
    {
        m_roomManager.deleteRoom(m_id);
    }

    MenuRequestHandler* menu = m_handlerFactory.createMenuRequestHandler(m_user);
    requestResult.newHandler = (IRequestHandler*)menu;
    m_room.removeUser(m_user);

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
    
    //TO-DO need to make game handler
    // For now will stay in roomAdminRequestHandler
    requestResult.newHandler = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room);

    return requestResult;
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

RequestResult RoomAdminRequestHandler::getPlayersInRoom(Requestinfo requestInfo)
{
    RequestResult requestResult;

    // Deserialize request
    GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buf);

    // Get all the players in a desired room through room manager
    auto room = m_handlerFactory.getRoomManager().getRoom(getPlayersInRoomRequest.roomId);
    std::vector<std::string> players = room.getAllUsers();


    RoomAdminRequestHandler* admin = m_handlerFactory.createRoomAdminRequestHandler(m_user, m_room);
    requestResult.newHandler = (IRequestHandler*)admin;

    // Create response
    GetPlayersInRoomResponse getPlayersInRoomResponse;
    getPlayersInRoomResponse.status = TEMP_GET_PLAYERS_IN_ROOM_RESPONSE_STATUS;
    getPlayersInRoomResponse.players = players;


    //Serialize response
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(getPlayersInRoomResponse);
    
    return requestResult;
}

RequestResult RoomAdminRequestHandler::error(Requestinfo requestInfo)
{
    RequestResult requestResult;

    // Create response
    ErrorResponse errorResponse;
    errorResponse.message = "Error in Room Admin Request Handler.";
    std::cout << "Error in roomAdminRequestHandler\n";
    //Serialize response
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);

    // New handler is nullptr - indicates Error
    requestResult.newHandler = nullptr;
    return requestResult;
}

/*
void getRoomStateResponseByRoom(Room m_room, GetRoomStateResponse& resp) {

}*/