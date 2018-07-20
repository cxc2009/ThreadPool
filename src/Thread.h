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
	//�����߳�
	bool Start(shared_ptr<Work> work);
	//�����߳�
	bool Block();
	//�˳��߳�
	bool Quit();
};
}
