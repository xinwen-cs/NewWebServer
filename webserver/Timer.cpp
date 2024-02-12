//
// Created by henrywen on 2024/2/12.
//

#include "Timer.h"
#include "HttpData.h"

#include <sys/time.h>
#include <unistd.h>
#include "base/Logging.h"


TimerNode::TimerNode(std::shared_ptr<HttpData> requestData, int timeout)
        : deleted_(false), SPHttpData(requestData) {
    struct timeval now;
    gettimeofday(&now, NULL);
    // 以毫秒计
    expiredTime_ =
            (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

TimerNode::~TimerNode() {
    if (SPHttpData) {
        SPHttpData->handleClose();
    }
}

TimerNode::TimerNode(TimerNode &tn)
        : SPHttpData(tn.SPHttpData), expiredTime_(0) {}

bool TimerNode::isValid() {
    struct timeval now;
    gettimeofday(&now, NULL);
    size_t temp = (((now.tv_sec % 10000) * 1000) + (now.tv_usec / 1000));
    if (temp < expiredTime_)
        return true;
    else {
        this->setDeleted();
        return false;
    }
}

void TimerNode::clearReq() {
    SPHttpData.reset();
    this->setDeleted();
}

void TimerManager::addTimer(std::shared_ptr<HttpData> SPHttpData, int timeout) {
    SPTimerNode new_node = std::make_shared<TimerNode>(SPHttpData, timeout);
    timerNodeQueue.push(new_node);
    SPHttpData->linkTimer(new_node);
}

void TimerManager::handleExpiredEvent() {
    while (!timerNodeQueue.empty()) {
        SPTimerNode ptimer_now = timerNodeQueue.top();
        if (ptimer_now->isDeleted()) {
            timerNodeQueue.pop();
        } else if (ptimer_now->isValid() == false) {
            timerNodeQueue.pop();
        } else {
            break;
        }
    }
}
