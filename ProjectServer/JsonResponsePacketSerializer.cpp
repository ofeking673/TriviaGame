#include "JsonResponsePacketSerializer.h"


/// <summary>
/// Serialize Error response from JSON format to binary
/// </summary>
/// <param name="errorResponse">Error response object</param>
/// <returns>Buffer contains binary format of JSON error response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const ErrorResponse& errorResponse)
{
    Buffer buffer;

    // Convert ErrorResponse to JSON
    json j;
    j["message"] = errorResponse.message;

    //// Serialize the JSON object to a string
    //std::string serializedString = j.dump();
    //serializedString = encodeBinary(serializedString);

    //// Convert the string to Buffer
    //for (auto& ch : serializedString)
    //{
    //    buffer.data.push_back(static_cast<unsigned char>(ch));
    //}

    //return buffer;
    return jsonObjectSerializer(j);
}

/// <summary>
/// Serialize Login response from JSON format to binary
/// </summary>
/// <param name="loginResponse">Login response object</param>
/// <returns>Buffer contains binary format of JSON login response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const LoginResponse& loginResponse)
{
    //Buffer buffer;

    //// Convert LoginResponse to JSON
    //json j;
    //j["status"] = loginResponse.status;

    //// Serialize the JSON object to a string
    //std::string serializedString = j.dump();
    //serializedString = encodeBinary(serializedString);

    //// Convert the string to Buffer
    //for (auto& ch : serializedString)
    //{
    //    buffer.data.push_back(static_cast<unsigned char>(ch));
    //}

    //return buffer;

    return statusOnlySerializeResponse(loginResponse.status);
}

/// <summary>
/// Serialize Signup response from JSON format to binary
/// </summary>
/// <param name="signupResponse">Signup response object</param>
/// <returns>Buffer contains binary format of JSON signup response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const SignupResponse& signupResponse)
{
    return statusOnlySerializeResponse(signupResponse.status);
}


std::string JsonResponsePacketSerializer::encodeBinary(std::string encodeStr)
{
    std::string encodedStr;

    for (int i = 0; i < encodeStr.size(); i++)
    {
        encodedStr.append(std::bitset<8>(encodeStr.c_str()[i]).to_string());
    }
    return encodedStr;
}

/// <summary>
/// Serialize Logout response from JSON format to binary
/// </summary>
/// <param name="signupResponse">Logout response object</param>
/// <returns>Buffer contains binary format of JSON logout response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const LogoutResponse& logoutResponse)
{
    return statusOnlySerializeResponse(logoutResponse.status);
}

/// <summary>
/// Serialize Get rooms response from JSON format to binary
/// </summary>
/// <param name="signupResponse">Get rooms response object</param>
/// <returns>Buffer contains binary format of JSON get rooms response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomsResponse& getRoomsResponse)
{

    // Convert GetRoomsResponse to JSON
    json j;
    
    std::ostringstream ss;

    // Get roomList in the format: 
    // "id|name|maxPlayers|numOfQuestionsInGame|timePerQuestion|isActive,..."
    for (const auto& room : getRoomsResponse.rooms) 
    {
        ss << room.id << "|"
            << room.name << "|"
            << room.maxPlayers << "|"
            << room.numOfQuestionsInGame << "|"
            << room.timePerQuestion << "|"
            << room.isActive << ",";
    }
    std::string roomsList = ss.str();

    // Remove the last comma
    if (!roomsList.empty())
    {
        roomsList.pop_back();
    }

    j["Rooms"] = roomsList;

    return jsonObjectSerializer(j);
}

/// <summary>
/// Serialize Get players in room response from JSON format to binary
/// </summary>
/// <param name="signupResponse">Get players in room response object</param>
/// <returns>Buffer contains binary format of JSON get players in room response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse)
{
    // Convert GetPlayersInRoomResponse to JSON
    json j;
    std::string playersList;

    // Get playersList in the format: "user1, user2, ..., userN"
    for (const auto& player : getPlayersInRoomResponse.players) 
    {
        if (!playersList.empty())
        {
            playersList += ",";
        }
        playersList += player;
    }
    j["PlayersInRoom"] = playersList;

    return jsonObjectSerializer(j);
}

/// <summary>
/// Serialize Join Room response from JSON format to binary
/// </summary>
/// <param name="signupResponse">Join Room response object</param>
/// <returns>Buffer contains binary format of JSON Join Room response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const JoinRoomResponse& joinRoomResponse)
{
    return statusOnlySerializeResponse(joinRoomResponse.status);
}


/// <summary>
/// Serialize Create Room response from JSON format to binary
/// </summary>
/// <param name="signupResponse">Create Room response object</param>
/// <returns>Buffer contains binary format of JSON Create Room response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const CreateRoomResponse& createRoomResponse)
{
    json j;
    j["status"] = createRoomResponse.status;
    j["roomId"] = createRoomResponse.id;

    return jsonObjectSerializer(j);
}

/// <summary>
/// Serialize Get high scores response from JSON format to binary
/// 
/// IMPORTANT!!
/// The format of JSON will be:
/// 
/// {HighScores: "username1 | score, username2 | score, ..., userN | score"}
/// </summary>
/// <param name="signupResponse">Get high scores response object</param>
/// <returns>Buffer contains binary format of JSON get high scores response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const GetHighScoreResponse& getHighScoreResponse)
{

    // Convert GetHighScoreResponse to JSON
    json j;
    std::string highScores;
    // Get high scores in the format of:
    // ""username1 | score, username2 | score, ..."
    for (int i = 0; i < getHighScoreResponse.statistics.size(); i++)
    {
        if (i > 0)
        {
            highScores += ",";
        }
        highScores += getHighScoreResponse.statistics[i];
    }
    std::cout << highScores << std::endl;
    highScores.pop_back();
    j["HighScores"] = highScores;

    return jsonObjectSerializer(j);
}

/// <summary>
/// Serialize Get personal stats response from JSON format to binary
/// 
/// IMPORTANT!!
/// The format of JSON will be:
/// 
/// {UserStatistics: "playerScore, numOfPlayerGames,numOfTotalAnswers,
/// numOfCorrectAnswers, playerAverageAnswerTime"}
/// </summary>
/// <param name="signupResponse">Get personal stats response object</param>
/// <returns>Buffer contains binary format of JSON get personal stats response</returns>
Buffer JsonResponsePacketSerializer::serializeResponse(const GetPersonalStatsResponse& getPersonalStatsResponse)
{
    // Check if statistics vector contains all elements
    if (getPersonalStatsResponse.statistics.size() != 5)
    {
        throw std::runtime_error("Invalid statistics data");
    }

    // Convert GetPersonalStatsResponse to JSON
    json j;
    std::string statisticsString;
    // Get statistics string in the following format.
    // "playerScore, numOfPlayerGames,numOfTotalAnswers,
    // numOfCorrectAnswers, playerAverageAnswerTime"
    for (int i = 0; i < getPersonalStatsResponse.statistics.size(); i++)
    {
        if (i > 0) 
        {
            statisticsString += ",";
        }
        statisticsString += getPersonalStatsResponse.statistics[i];
    }
    j["UserStatistics"] = statisticsString;

    return jsonObjectSerializer(j);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const CloseRoomResponse& closeRoomResponse)
{
    return statusOnlySerializeResponse(closeRoomResponse.status);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StartGameResponse& startGameResponse)
{
    return statusOnlySerializeResponse(startGameResponse.status);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetRoomStateResponse& getRoomStateResponse)
{
    json j;
    
    //unsigned int status;
    //bool hasGameBegun;
    //std::vector<std::string> players;
    //unsigned int questionCount;
    //unsigned int answerTimeOut;
    j["status"] = getRoomStateResponse.status;
    j["hasGameBegun"] = getRoomStateResponse.hasGameBegun;
    j["players"] = getRoomStateResponse.players;
    j["questionCount"] = getRoomStateResponse.questionCount;
    j["answerTimeOut"] = getRoomStateResponse.answerTimeOut;

    j["isMatchmaking"] = getRoomStateResponse.isMatchmaking;
    j["waitingForAnotherUser"] = getRoomStateResponse.waitingForAnotherUser;

    return jsonObjectSerializer(j);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveRoomResponse& leaveRoomResponse)
{
    return statusOnlySerializeResponse(leaveRoomResponse.status);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const RoomUpdateResponse& roomUpdateResponse)
{
    return statusOnlySerializeResponse(roomUpdateResponse.status);
}

// Game related
Buffer JsonResponsePacketSerializer::serializeResponse(const GetGameResultsResponse& getGameResultsResponse)
{
    json j;
    j["status"] = getGameResultsResponse.status;

    //// Serializing the vector of PlayerResults
    //for (const auto& result : getGameResultsResponse.results)
    //{
    //    json playerResult;
    //    playerResult["username"] = result.username;
    //    playerResult["correctAnswerCount"] = result.correctAnswerCount;
    //    playerResult["wrongAnswerCount"] = result.wrongAnswerCount;
    //    playerResult["averageAnswerTime"] = result.averageAnswerTime;
    //    playerResult["score"] = result.score;
    //    j["results"].push_back(playerResult);
    //}

    std::ostringstream ss;

    // Serialize the vector of PlayerResults
    for (const auto& result : getGameResultsResponse.results)
    {
        ss << result.username << "|"
            << result.correctAnswerCount << "|"
            << result.wrongAnswerCount << "|"
            << result.averageAnswerTime << "|"
            << result.score << ",";
    }

    // Convert to string
    std::string resultsStr = ss.str();

    // Remove the last comma
    if (!resultsStr.empty())
    {
        resultsStr.pop_back();
    }
    
    j["results"] = resultsStr;

    return jsonObjectSerializer(j);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const SubmitAnswerResponse& submitAnswerResponse)
{
    json j;
    j["status"] = submitAnswerResponse.status;
    j["correctAnswerId"] = submitAnswerResponse.correctAnswerId;
    j["score"] = submitAnswerResponse.score;

    return jsonObjectSerializer(j);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const GetQuestionResponse& getQuestionResponse)
{
    // Convert GetQuestionResponse to JSON
    json j;
    j["status"] = getQuestionResponse.status;
    j["question"] = getQuestionResponse.question;

    // Serializing the map of answers into JSON
    j["answers"] = getQuestionResponse.answers;

    return jsonObjectSerializer(j);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const LeaveGameResponse& leaveGameResponse)
{
    return statusOnlySerializeResponse(leaveGameResponse.status);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const AddQuestionResponse& addQuestionResponse)
{
    return statusOnlySerializeResponse(addQuestionResponse.status);
}

Buffer JsonResponsePacketSerializer::serializeResponse(const StartMatchmakingResponse& startMatchmakingResponse)
{
    json j;
    j["status"] = startMatchmakingResponse.status;
    j["roomId"] = startMatchmakingResponse.roomId;

    return jsonObjectSerializer(j);
}

/// <summary>
/// Serialize response that contains status only from JSON to binary buffer
/// </summary>
/// <param name="status">Status of response</param>
/// <returns>Buffer contains binary format of JSON logout response</returns>
Buffer JsonResponsePacketSerializer::statusOnlySerializeResponse(const unsigned int status)
{

    json j;
    j["status"] = status;

    return jsonObjectSerializer(j);
}

/// <summary>
/// Serialize a JSON object to Buffer (binary)
/// </summary>
/// <param name="j">JSON object</param>
/// <returns>Buffer contains binary encoded JSON</returns>
Buffer JsonResponsePacketSerializer::jsonObjectSerializer(nlohmann::json j)
{
    Buffer buffer;

    // Serialize the JSON object to a string
    std::string serializedString = j.dump();
    serializedString = encodeBinary(serializedString);

    // Convert the string to Buffer
    for (auto& ch : serializedString)
    {
        buffer.data.push_back(static_cast<unsigned char>(ch));
    }

    return buffer;
}