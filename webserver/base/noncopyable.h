//
// Created by henrywen on 2024/1/23.
//

#ifndef TINYWEBSERVER_NONCOPYABLE_H
#define TINYWEBSERVER_NONCOPYABLE_H


class noncopyable {
protected:
    noncopyable() {}
    ~noncopyable() {}

private:
    noncopyable(const noncopyable&);
    const noncopyable& operator=(const noncopyable&);
};


#endif //TINYWEBSERVER_NONCOPYABLE_H
