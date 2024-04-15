#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
	return  (requestInfo.id == Login || requestInfo.id == SignUp);
}

RequestResult LoginRequestHandler::HandleRequest(Requestinfo requestInfo)
{
	/*
	get request info >>>
	 
		?check if relevant? >>>
	
	see what result you need to send base on request info >>>
	if login, serialize login response
		?if signup, serialize signup response
	else, serialize error response
	
	add size of buffer
	add code /
	to response Buffer

	assign the buffer of serialized response to RequestResult
	
	// TO-DO assign new handler to RequestResult 

	return RequestResult

	*/
	RequestResult requestResult;

	// Check if request relevant
	isRequestRelevant(requestInfo);

	if (requestInfo.id == Login)
	{
		// Login
		// Deserialize login
		LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buf);
		
		// TO_DO check things about the user - using Database in future

		// Create response
		LoginResponse loginResponse;
		loginResponse.status = TEMP_LOGIN_STATUS;
		//Serialize response
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);

		// TO_DO add new handler to RequestResult
		requestResult.newHandler = nullptr;
	}
	else if (requestInfo.id == SignUp)
	{
		// Signup
		// Deserialize signup
		SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buf);

		// TO_DO check things about the user - using Database in future

		// Create response
		SignupResponse signupResponse;
		signupResponse.status = TEMP_SIGNUP_STATUS;
		//Serialize response
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);

		// TO_DO add new handler to RequestResult
		requestResult.newHandler = nullptr;
	}
	else
	{
		// Error
		// Deserialize error
		LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buf);

		// TO_DO check things about the user - using Database in future

		// Create response
		ErrorResponse errorResponse;
		errorResponse.message = "Error in Login Request Handler";
		//Serialize response
		requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);

		// TO_DO add new handler to RequestResult
		requestResult.newHandler = nullptr;
	}


	return requestResult;
}
