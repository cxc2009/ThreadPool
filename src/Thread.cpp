#include "Thread.h"

namespace AThreadPool{

Thread::Thread()
{
}


Thread::~Thread()
{
}

bool Thread::Start(shared_ptr<Work> work)
{
	return true;
}

}
