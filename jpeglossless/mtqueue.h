#ifndef MTQUEUE_H
#define MTQUEUE_H

#include <qptrqueue.h>
#include <qmutex.h>

namespace KIPIJPEGLossLessPlugin
{

template<class Type> class MTQueue
{

public:

  MTQueue()
  {
      queue_.setAutoDelete(true);
  }

  ~MTQueue()
  {
    flush();
  }

  bool isEmpty()
  {
    mutex_.lock();
    bool empty = queue_.isEmpty();
    mutex_.unlock();
    return empty;
  }

  void flush()
  {
    mutex_.lock();
    queue_.clear();
    mutex_.unlock();
  }

  void enqueue(Type * t)
  {
    mutex_.lock();
    queue_.enqueue(t);
    mutex_.unlock();
  }

  Type * dequeue()
  {
    mutex_.lock();
    Type * i = queue_.dequeue();
    mutex_.unlock();
    return i;
  }

private:

  QPtrQueue<Type> queue_;
  QMutex mutex_;

};

}  // NameSpace KIPIJPEGLossLessPlugin

#endif
