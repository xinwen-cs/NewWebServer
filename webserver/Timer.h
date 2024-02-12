//
// Created by henrywen on 2024/2/12.
//

#ifndef TINYWEBSERVER_TIMER_H
#define TINYWEBSERVER_TIMER_H

#include <memory>
#include <queue>


class HttpData;

class TimerNode {
public:
    TimerNode(std::shared_ptr<HttpData> requestData, int timeout);
    ~TimerNode();
    TimerNode(TimerNode &tn);
    bool isValid();
    void clearReq();
    void setDeleted() { deleted_ = true; }
    bool isDeleted() const { return deleted_; }
    size_t getExpTime() const { return expiredTime_; }

private:
    bool deleted_;
    size_t expiredTime_;
    std::shared_ptr<HttpData> SPHttpData;
};

struct TimerCmp {
    bool operator()(std::shared_ptr<TimerNode> &a,
                    std::shared_ptr<TimerNode> &b) const {
        return a->getExpTime() > b->getExpTime();
    }
};

class TimerManager {
public:
    TimerManager() = default;
    ~TimerManager() = default;
    void addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout);
    void handleExpiredEvent();

private:
    using SPTimerNode = std::shared_ptr<TimerNode> ;
    std::priority_queue<SPTimerNode, std::deque<SPTimerNode>, TimerCmp> timerNodeQueue;
};


#endif //TINYWEBSERVER_TIMER_H
