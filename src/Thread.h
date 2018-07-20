#pragma once
#include "Work.h"
#include <memory>

using std::shared_ptr;

namespace AThreadPool{

class Thread
{
public:
	Thread();
	~Thread();

public:
	//唤醒线程
	bool Start(shared_ptr<Work> work);
	//阻塞线程
	bool Block();
	//退出线程
	bool Quit();
};
}
