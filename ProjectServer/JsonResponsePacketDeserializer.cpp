#include "JsonResponsePacketDeserializer.h"

ErrorResponse JsonResponsePacketDeserializer::deserializeErrorResponse(const Requestinfo info)
{
    json j = getJsonFromString(info.buf.data);
    ErrorResponse err;
    std::string errormsg = "uh oh big issue!";
    err.message = errormsg;
    return err;
}

LoginResponse JsonResponsePacketDeserializer::deserializeLoginResponse(const Requestinfo info)
{
    json j = getJsonFromString(info.buf.data);
    LoginResponse login;
    //TODO: login logic here (when db comes i guess)
    int status = OK;
    login.status = status;
    return login;
}

SignupResponse JsonResponsePacketDeserializer::deserializeSignupResponse(const Requestinfo info)
{
    json j = getJsonFromString(info.buf.data);
    SignupResponse response;
    //TODO: signup logic here! (when db comes i guess)
    int status = OK; //set for now, change after logic is implemented.

    response.status = status;
    return response;
}

json JsonResponsePacketDeserializer::getJsonFromString(std::vector<unsigned char> x)
{
    json j;
    std::string data;

    for (unsigned char ch : x)
    {
        data += static_cast<char>(ch); //just transfer unsigned chars into normal chars
        //pretty sure this SHOULD work as a decoder
    }

    j = json::parse(data);
    return j;
}
