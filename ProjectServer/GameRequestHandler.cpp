#include "GameRequestHandler.h"

bool GameRequestHandler::isRequestRelevant(Requestinfo requestInfo)
{
	return (requestInfo.id == LeaveGame || requestInfo.id == GetQuestion ||
		requestInfo.id == SubmitAnswer || requestInfo.id == GetGameResult);
}

RequestResult GameRequestHandler::HandleRequest(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Check if request relevant
	if (isRequestRelevant(requestInfo))
	{

		if (requestInfo.id == LeaveGame)
		{
			// LeaveGame
			requestResult = leaveGame(requestInfo);
		}
		else if (requestInfo.id == GetQuestion)
		{
			// GetQuestion
			requestResult = getQuestion(requestInfo);
		}
		else if (requestInfo.id == SubmitAnswer)
		{
			// SubmitAnswer
			requestResult = submitAnswer(requestInfo);
		}
		else if (requestInfo.id == GetGameResult)
		{
			// GetGameResult
			requestResult = getGameResults(requestInfo);
		}
	}
	else
	{
		// Error
		requestResult = error(requestInfo);
	}


	return requestResult;
}

RequestResult GameRequestHandler::getQuestion(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	GetQuestionResponse getQuestionResponse;

	// Get the whole Question
	Question wholeQuestion = m_game.getQuestionForUser(m_user);
	if (wholeQuestion.getCorrectAnswerId() == NO_MORE_QUESTIONS_LEFT)
	{
		// No more questions left - indicated by status
		getQuestionResponse.status = TEMP_NO_MORE_QUESTIONS_LEFT_GET_QUESTION_RESPONSE_STATUS;
		getQuestionResponse.question = "";
		std::map<unsigned int, std::string> answers;
		getQuestionResponse.answers = answers;
	}
	else
	{
		getQuestionResponse.question = wholeQuestion.getQuestion();

		// Get the answers
		std::map<unsigned int, std::string> answers;
		std::vector<std::string> answerList = wholeQuestion.getPossibleAnswers();
		unsigned int answerId = 1;
		for (auto it = answerList.begin(); it != answerList.end(); it++)
		{
			answers[answerId] = *it;
			answerId++;
		}

		getQuestionResponse.answers = answers;

		getQuestionResponse.status = TEMP_GET_QUESTION_RESPONSE_STATUS;
	}

	// New handler is Game request handler
	requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_user);

	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(getQuestionResponse);

	return requestResult;
}

RequestResult GameRequestHandler::submitAnswer(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	SubmitAnswerResponse submitAnswerResponse;

	// Get correct answer ID, before submiting answer and moving to next question
	submitAnswerResponse.correctAnswerId = m_game.getQuestionForUser(m_user).getCorrectAnswerId();

	// Deserialize request
	SubmitAnswerRequest submitAnswerRequest = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buf);

	// Update scores in DB
	m_game.submitAnswer(m_user, submitAnswerRequest.answerId, submitAnswerRequest.answerTime);

	// TO-DO: maybe submitAnswer() will return the current score of user.
	//		  This, in order to show score on front during the game.

	// Status of submit answer response
	submitAnswerResponse.status = TEMP_SUBMIT_ANSWER_RESPONSE_STATUS;

	requestResult.response = JsonResponsePacketSerializer::serializeResponse(submitAnswerResponse);
	requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_user);

	return requestResult;
}

RequestResult GameRequestHandler::getGameResults(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	GetGameResultsResponse getGameResultsResponse;

	std::vector<PlayerResults> results;

	// TO-DO: think of a way to get results from game. maybe add a function


	return requestResult;
}

RequestResult GameRequestHandler::leaveGame(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	LeaveGameResponse leaveGameResponse;

	// TO-DO: manage a function to know what room is the user in, 
	//		  to be able to log him out from the room

	// Status of leave game response
	leaveGameResponse.status = TEMP_LEAVE_GAME_RESPONSE_STATUS;

	requestResult.response = JsonResponsePacketSerializer::serializeResponse(leaveGameResponse);

	// After leaving the game, will return to menu
	requestResult.newHandler = (IRequestHandler*)m_handlerFactory.createMenuRequestHandler(m_user);

	return requestResult;
}

RequestResult GameRequestHandler::error(Requestinfo requestInfo)
{
	RequestResult requestResult;

	// Create response
	ErrorResponse errorResponse;
	errorResponse.message = "Error in Game Request Handler.";
	//Serialize response
	requestResult.response = JsonResponsePacketSerializer::serializeResponse(errorResponse);

	// New handler is nullptr - indicates Error
	requestResult.newHandler = nullptr;
	return requestResult;
}
