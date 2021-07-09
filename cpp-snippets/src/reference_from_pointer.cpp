
#include <memory>
#include <vector>
#include <string>
#include <iostream>


struct Message {
    uint32_t id;
    std::string what;
};

class Queue {
public:
    Message * _msg;
    static uint8_t  _id;
    explicit Queue(uint32_t msg_id, std::string what) {
        _msg = new Message{msg_id, what};
        ++_id;
    }
    ~Queue() {
        std::cout << "~Queue(id = " << _id << ", message =  (" << _msg->id << ", " << _msg->what << ") )" << std::endl;
        delete _msg;
    }
    auto operator=(Queue const &queue) -> Queue & {
        _msg = queue._msg;
        return *this;
    }

    auto msg() -> Message& {
        return *_msg;
    }
};

uint8_t Queue::_id = 0;

int main()
{
    auto queue = Queue(0, "hello");
    Message & message = queue.msg();
    std::cout << message.what << std::endl;
    {

        auto queue2 = Queue(1, "world");
        message = queue2.msg();
    }

    std::cout << message.what << std::endl;


    return 0;
}
