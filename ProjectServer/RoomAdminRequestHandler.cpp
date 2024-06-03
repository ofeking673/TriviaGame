#include "RoomAdminRequestHandler.h"

bool RoomAdminRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
    return (requestInfo.id == CloseRoom ||
        requestInfo.id == StartGame ||
        requestInfo.id == GetRoomState ||
        requestInfo.id == GetPlayersInRoom &&
        m_roomManager.doesRoomExist(m_id));
}

RequestResult RoomAdminRequestHandler::HandleRequest(Requestinfo requestInfo)
{
    std::cout << requestInfo.id << std::endl;
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
        std::cout << requestInfo.id << std::endl;
        return error(requestInfo);
    }
}

RequestResult RoomAdminRequestHandler::closeRoom(Requestinfo requestInfo)
{
    CloseRoomResponse closeRoomResponse;

    closeRoomResponse.status = TEMP_ROOM_CLOSE_STATUS;
    m_room.status = 2;

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(closeRoomResponse);

    MenuRequestHandler* menu = m_handlerFactory.createMenuRequestHandler(m_user);
    requestResult.newHandler = (IRequestHandler*)menu;
    m_room.removeUser(m_user);

    if (m_roomManager.getRoom(m_id).getAllUsers().size() < 1)
    {
        m_roomManager.deleteRoom(m_id);
    }

    return requestResult;

}

RequestResult RoomAdminRequestHandler::startGame(Requestinfo requestInfo)
{
    std::cout << "Room started!\n";
    m_room.status = 1;
    m_room.startGame(m_user);
    m_handlerFactory.getGameManager().createGame(m_room);
    StartGameResponse start;
    start.status = TEMP_ROOM_START_STATUS;

    RequestResult requestResult;
    requestResult.response = JsonResponsePacketSerializer::serializeResponse(start);
    
    // Move to Game request handloer
    requestResult.newHandler = (IRequestHandler*)RequestHandlerFactory::getInstance(nullptr).createGameRequestHandler(m_user);

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