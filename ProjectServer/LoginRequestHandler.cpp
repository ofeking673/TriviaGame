#include "LoginRequestHandler.h"

bool LoginRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
	return  (requestInfo.id == Login || requestInfo.id == SignUp);
}

RequestResult LoginRequestHandler::HandleRequest(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Check if request relevant
	isRequestRelevant(requestInfo);

	if (requestInfo.id == Login)
	{
		// Login
		requestResult = login(requestInfo);
	}
	else if (requestInfo.id == SignUp)
	{
		// Signup
		requestResult = signup(requestInfo);
	}
	else
	{
		// Error
		requestResult = error(requestInfo);
	}


	return requestResult;
}

/// <summary>
/// Login a user into the system
/// Gets Request info, parse its' data. 
/// Sends the data to loginMannager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult LoginRequestHandler::login(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Login
	// Deserialize login
	LoginRequest loginRequest = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buf);

	// Login the user through login manager who uses the Database
	m_handlerFactory.getLoginManager().login(loginRequest.username, loginRequest.password);

	// TO-DO
	// Currently I DONT KNOW how to check if the login was succesful
	// So in the future there will be a need to check that.
	// Now I will do it as it is always succeful login.


	// Create response
	LoginResponse loginResponse;
	loginResponse.status = TEMP_LOGIN_STATUS;
	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(loginResponse);

	// Add new handler to RequestResult
	// Now we say it is always succeful so it will be the menu
	// Later we will need to check if succeful
	if (true /*Succeful*/)
	{
		// Currently empty. In v2.0.0 will be needed to change to 'createMenuRequestHandler'
		MenuRequestHandler* menu = new MenuRequestHandler;
		requestResult.newHandler = menu;
	}
	else //Faied to Login
	{
		// Stay in login request handler
		LoginRequestHandler* loginRequestHandler = m_handlerFactory.createLoginRequestHandler();
		requestResult.newHandler = loginRequestHandler;
	}

	return requestResult;
}

/// <summary>
/// Signup a user into the system
/// Gets Request info, parse its' data. 
/// Sends the data to loginMannager who works on DB
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult LoginRequestHandler::signup(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Deserialize signup
	SignupRequest signupRequest = JsonRequestPacketDeserializer::deserializeSignupRequest(requestInfo.buf);

	// Signup the user through login manager who uses the Database
	m_handlerFactory.getLoginManager().signup(signupRequest.username, signupRequest.password, signupRequest.email);
	
	// TO-DO
	// Currently I DONT KNOW how to check if the signup was succesful
	// So in the future there will be a need to check that.
	// Now I will do it as it is always succeful signup.

	// Create response
	SignupResponse signupResponse;
	signupResponse.status = TEMP_SIGNUP_STATUS;
	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(signupResponse);

	// Add new handler to RequestResult
	// Now we say it is always succeful so it will be the menu
	// Later we will need to check if succeful
	if (true /*Succeful*/)
	{
		// Currently empty. In v2.0.0 will be needed to change to 'createMenuRequestHandler'
		MenuRequestHandler* menu = new MenuRequestHandler;
		requestResult.newHandler = menu;
	}
	else //Faied to Signup
	{
		// Stay in login request handler
		LoginRequestHandler* loginRequestHandler = m_handlerFactory.createLoginRequestHandler();
		requestResult.newHandler = loginRequestHandler;
	}

	return requestResult;
}

/// <summary>
/// Error in login request handler
/// Create error response to send back to client
/// </summary>
/// <param name="requestInfo">Request info contains (id, time, buffer)</param>
/// <returns>RequestResult contains(buffer [to send back], newHandler)</returns>
RequestResult LoginRequestHandler::error(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	ErrorResponse errorResponse;
	errorResponse.message = "Error in Login Request Handler.";
	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);

	// New handler is nullptr - indicates Error
	requestResult.newHandler = nullptr;
	return requestResult;
}
