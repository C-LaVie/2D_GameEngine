
#ifndef CEVENTQUEUE_H
#define CEVENTQUEUE_H



#include <SDL.h>
#include <Windows.h>
#include <deque>

class CEventQueue
{

public:

	/**
	* @brief Default Constructor
	*/
	CEventQueue(void);

	/**
	* @brief Copy Constructor
	* @param Element to copy
	*/
	CEventQueue(const CEventQueue& rRhs);

	/**
	* @brief Destructor
	*/
	~CEventQueue();

	/**
	* @brief Push the Event, received in argument, on top of the Queue
	* @param Event to copy on top of Queue
	*/
	void Push(const SDL_Event& rEvent);

	/**
	* @brief Copy First Event of the Queue on the event received in
	* reference, then remove the first event of the Queue
	* @warning this function is blocking
	* @param rEvent Event that will receive a copy of poped element
	* @return true if Queue was not empty ; otherwise false
	*/
	bool Pop(SDL_Event& rEvent);

	/**
	* @brief return the number of events in the queue
	* @return number of events in the queue
	*/
	size_t Size(void) const;

private:

	/**
	* @brief if the queue isn't empty, copy the first element of the queue
	* one the received one. Then, remove first element of the queue
	* @return true if success (if queue wasn't empty)
	*/
	bool InternalPop(SDL_Event& rEvent);

	/**
	* Critical section that protects the queue against concurrent accesses
	* this member is mutable to support const on Size() function
	*/
	mutable CRITICAL_SECTION m_dataProtector;

	/// Event handle - used to notify insertion of event on top of queue
	HANDLE m_hWinEvent;

	/// Event queue based on FIFO mode
	std::deque<SDL_Event> m_queue;

};


//CEVENTQUEUE_H end
#endif 

