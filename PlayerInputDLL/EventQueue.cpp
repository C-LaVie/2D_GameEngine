

#include "EventQueue.h"



/**
* @brief Default Constructor
*/
CEventQueue::CEventQueue(void) :
m_hWinEvent(CreateEvent(NULL, FALSE, FALSE, NULL)),
m_queue()
{
	InitializeCriticalSection(&m_dataProtector);
}

/**
* @brief Copy Constructor
* @param Element to copy
*/
CEventQueue::CEventQueue(const CEventQueue & rRhs) :
m_hWinEvent(CreateEvent(NULL, FALSE, FALSE, NULL)),
m_queue()
{
	rRhs;
	//Doesn't need to copy pending events
	InitializeCriticalSection(&m_dataProtector);
}

/**
* @brief Destructor
*/
CEventQueue::~CEventQueue()
{
	// Freeze queue
	while (!m_queue.empty())
	{
		m_queue.pop_front();
	}

	// Freeze critical section
	DeleteCriticalSection(&m_dataProtector);

	// And event handler.
	if (m_hWinEvent != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hWinEvent);
		m_hWinEvent = INVALID_HANDLE_VALUE;
	}
}

/**
* @brief Push the Event, received in argument, on top of the Queue
* @param Event to copy on top of Queue
*/
void CEventQueue::Push(const SDL_Event& rEvent)
{
	EnterCriticalSection(&m_dataProtector);

	m_queue.push_back(rEvent);

	if (m_hWinEvent != INVALID_HANDLE_VALUE)
	{
		SetEvent(m_hWinEvent);
	}

	LeaveCriticalSection(&m_dataProtector);
}

/**
* @brief return the number of events in the queue
* @return number of events in the queue
*/
size_t CEventQueue::Size(void) const
{
	EnterCriticalSection(&m_dataProtector);
	size_t l_size = m_queue.size();
	LeaveCriticalSection(&m_dataProtector);
	return l_size;
}

/**
* @brief Copy First Event of the Queue on the event received in
* reference, then remove the first event of the Queue
* @warning this function is blocking
* @param rEvent Event that will receive a copy of poped element
* @return true if Queue was not empty ; otherwise false
*/
bool CEventQueue::Pop(SDL_Event& rEvent)
{
	bool result;
	bool loop = true;

	// Try to get message first. If no message present on queue, suspend
	// thread since queue internal event set to signal incoming message
	if ((result = InternalPop(rEvent)) == false)
	{
		while (loop)
		{
			loop = false;
			switch (WaitForSingleObjectEx(m_hWinEvent, INFINITE, TRUE))
			{
			case WAIT_OBJECT_0:	// Event Set : get received message
			{
				result = InternalPop(rEvent);
			}
			break;
			case WAIT_IO_COMPLETION: // APC Routine executed, continue event waiting
			{
				loop = true;
			}
			break;

			default: // Error on WaitForSingleObject
			{
				; // Prevent for empty block warning.
			}
			break;
			}
		}
	}

	return result;
}

/**
* @brief if the queue isn't empty, copy the first element of the queue
* one the received one. Then, remove first element of the queue
* @return true if success (if queue wasn't empty)
*/
bool CEventQueue::InternalPop(SDL_Event& rEvent)
{
	bool result = false;
	EnterCriticalSection(&m_dataProtector);

	// IF Queue is not Empty copy the last message and reset queue internal
	// event.
	if (m_queue.size())
	{
		rEvent = m_queue.front();
		m_queue.pop_front();

		ResetEvent(m_hWinEvent);

		result = true;
	}

	LeaveCriticalSection(&m_dataProtector);

	return result;
}


